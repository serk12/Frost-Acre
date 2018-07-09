#include "../header/InstrumentSimulator.h"

InstrumentSimulator::InstrumentSimulator() {
    instrument = nullptr;
}

void InstrumentSimulator::setInstrument(Instrument& instrument) {
    this->instrument = &instrument;
}

void InstrumentSimulator::calculatePrecal() {
    this->calculateMassSpringSystem();
    this->calcuateDeformationModeling();
}

void InstrumentSimulator::makeDiagonalSpring(int x, int y, int negative, double Cx, double Cy, double Cz) {
    PrecalModel& precalModel = instrument->precalModel;

    precalModel.springK(x,     y) += negative * Cx * Cx;
    precalModel.springK(x + 1, y) += negative * Cx * Cy;
    precalModel.springK(x + 2, y) += negative * Cx * Cz;

    precalModel.springK(x,     y + 1) += negative * Cy * Cx;
    precalModel.springK(x + 1, y + 1) += negative * Cy * Cy;
    precalModel.springK(x + 2, y + 1) += negative * Cy * Cz;

    precalModel.springK(x,     y + 2) += negative * Cz * Cx;
    precalModel.springK(x + 1, y + 2) += negative * Cz * Cy;
    precalModel.springK(x + 2, y + 2) += negative * Cz * Cz;
}

void InstrumentSimulator::calculateSpring() {
    Model3D& model3d         = instrument->model3d;
    PrecalModel& precalModel = instrument->precalModel;
    precalModel.springK = Eigen::MatrixXd::Zero(model3d.edge.rows() * 3,
                                                model3d.edge.cols() * 3);
    #pragma omp parallel shared(precalModel)
    {
        #pragma omp for
        for (int j = 0; j < model3d.edge.cols(); ++j) {
            for (int i = j + 1; i < model3d.edge.rows(); ++i) {
                int id = model3d.edge(i, j);

                if (id != 0) {
                    double Cx = fabs(model3d.vertex(0, j) - model3d.vertex(0, i));
                    double Cy = fabs(model3d.vertex(1, j) - model3d.vertex(1, i));
                    double Cz = fabs(model3d.vertex(2, j) - model3d.vertex(2, i));
                    double L  = std::sqrt(Cx * Cx + Cy * Cy + Cz * Cz);
                    Cx /= L; Cy /= L; Cz /= L; // Cx = Cy = Cz = 1;
                    double youngThick = instrument->material[id].youngsModulusY *
                                        instrument->material[id].thicknessT;

                    this->makeDiagonalSpring(i * 3, i * 3,  youngThick, Cx, Cy, Cz);
                    this->makeDiagonalSpring(j * 3, i * 3, -youngThick, Cx, Cy, Cz);
                    this->makeDiagonalSpring(i * 3, j * 3, -youngThick, Cx, Cy, Cz);
                    this->makeDiagonalSpring(j * 3, j * 3,  youngThick, Cx, Cy, Cz);
                }
            }
        }
    }
}

void InstrumentSimulator::calculateMass() {
    Model3D& model3d         = instrument->model3d;
    PrecalModel& precalModel = instrument->precalModel;
    precalModel.massM = Eigen::VectorXd(model3d.vertex.cols());
    #pragma omp parallel shared(precalModel)
    {
        #pragma omp for
        for (int i = 0; i < model3d.edge.cols(); ++i) {
            double volum = 0;

            for (int j = 0; j < model3d.edge.rows(); ++j) {
                int id = model3d.edge(j, i);

                if (id != 0) {
                    double Cx = model3d.vertex(0, j) - model3d.vertex(0, i);
                    double Cy = model3d.vertex(1, j) - model3d.vertex(1, i);
                    double Cz = model3d.vertex(2, j) - model3d.vertex(2, i);
                    double L  = std::sqrt(Cx * Cx + Cy * Cy + Cz * Cz);
                    volum += L * M_PI *
                             instrument->material[id].thicknessT *
                             instrument->material[id].thicknessT *
                             instrument->material[id].densityD;
                }
            }
            precalModel.massM(i) = volum;
        }
    }
}

void InstrumentSimulator::calculateMassSpringSystem() {
    this->calculateSpring();
    this->calculateMass();
}


void InstrumentSimulator::calcuateDeformationModeling() {
    PrecalModel& precalModel = instrument->precalModel;
    Model3D    & model3d     = instrument->model3d;

    Eigen::initParallel(); // Dont work....
    precalModel.solver = Eigen::EigenSolver<Eigen::MatrixXd>(precalModel.springK, true);
    const Eigen::MatrixXcd& eigenvaluesD = precalModel.solver.eigenvalues();

    precalModel.possitiveW = Eigen::VectorXcd(eigenvaluesD.size());
    precalModel.negativeW  = Eigen::VectorXcd(eigenvaluesD.size());

    #pragma omp parallel shared(precalModel)
    {
        #pragma omp for
        for (int i = 0; i < eigenvaluesD.size(); ++i) {
            int id                      = model3d.edge(i / 3, i / 3);
            double fluidDampingV        = instrument->material[id].fluidDampingV;
            double viscoelasticDampingN = instrument->material[id].viscoelasticDampingN;

            double aux                = fluidDampingV * eigenvaluesD(i).real() + viscoelasticDampingN;
            std::complex<double> root = std::sqrt(std::complex<double>(aux * aux - 4. * eigenvaluesD(i).real(), 0));

            precalModel.possitiveW(i) = (-aux + root) / 2.;
            precalModel.negativeW(i)  = (-aux - root) / 2.;
        }
    }

    cleanMatrix(precalModel.possitiveW);
    cleanMatrix(precalModel.negativeW);

    precalModel.gainOfModeC = Eigen::VectorXcd::Zero(eigenvaluesD.size());
}

void InstrumentSimulator::calculateImpulsForces(Eigen::VectorXd forcesF, double time) {
    PrecalModel& precalModel      = instrument->precalModel;
    const Eigen::MatrixXd forcesG = precalModel.solver.eigenvectors().inverse().real() * forcesF;

    #pragma omp parallel shared(precalModel)
    {
        #pragma omp for
        for (int i = 0; i < precalModel.gainOfModeC.size(); ++i) {
            std::complex<double> diff         = precalModel.possitiveW(i) - precalModel.negativeW(i);
            std::complex<double> poweredEuler =
                std::pow(instrument->euler, precalModel.possitiveW(i).real()) *
                (cos(precalModel.possitiveW(i).imag() * time) +
                 (sin(precalModel.possitiveW(i).imag() * time) * 1.i));
            precalModel.gainOfModeC(i) =
                precalModel.gainOfModeC(i) + (forcesG(i) / (precalModel.massM(i / 3) * diff * poweredEuler));
        }
    }
    cleanMatrix(precalModel.gainOfModeC);
}

void InstrumentSimulator::calculateVibrations(double time, Eigen::VectorXd& modesOfVibrationZ) {
    const PrecalModel& precalModel = instrument->precalModel;
    modesOfVibrationZ = Eigen::VectorXd(precalModel.gainOfModeC.size());

    for (int i = 0; i < precalModel.gainOfModeC.size(); ++i) {
        std::complex<double> Ci          = precalModel.gainOfModeC(i);
        std::complex<double> CiConj      = std::conj(precalModel.gainOfModeC(i));
        std::complex<double> eulerPowPos =
            std::pow(instrument->euler, precalModel.possitiveW(i).real()) *
            (cos(precalModel.possitiveW(i).imag() * time) + (sin(precalModel.possitiveW(i).imag() * time) * 1.i));
        std::complex<double> eulerPowNeg =
            std::pow(instrument->euler, precalModel.negativeW(i).real()) *
            (cos(precalModel.negativeW(i).imag() * time)  + (sin(precalModel.negativeW(i).imag()  * time) * 1.i));

        modesOfVibrationZ[i] = ((Ci     * precalModel.possitiveW(i) * eulerPowPos) +
                                (CiConj * precalModel.negativeW(i)  * eulerPowNeg)).real();
    }
}

void InstrumentSimulator::cleanMatrix(Eigen::VectorXcd& mat, const double precision) {
    #pragma omp parallel shared(mat)
    {
        #pragma omp for
        for (int j = 0; j < mat.cols(); ++j) {
            for (int i = 0; i < mat.rows(); ++i) {
                if (fabs(mat(i, j).real()) < precision) {
                    mat(i, j).real(0);
                }

                if (fabs(mat(i, j).imag()) < precision) {
                    mat(i, j).imag(0);
                }
            }
        }
    }
}
