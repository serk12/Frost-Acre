#include "../header/InstrumentSimulator.h"

InstrumentSimulator::InstrumentSimulator() {
    instrument = nullptr;
}

InstrumentSimulator::InstrumentSimulator(Instrument& instrument, bool calculateNow) {
    this->setInstrument(instrument);

    if (calculateNow) {
        this->calculateMassSpringSystem();
        this->calcuateDoformationModeling();
    }
}

void InstrumentSimulator::setInstrument(Instrument& instrument) {
    this->instrument = &instrument;
}

void InstrumentSimulator::calculatePrecal() {
    this->calculateMassSpringSystem();
    this->calcuateDoformationModeling();
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

    for (int j = 0; j < model3d.edge.cols(); ++j) {
        for (int i = 0; i < model3d.edge.rows(); ++i) {
            if (model3d.edge(i, j) != 0) {
                double Cx = model3d.vertex(0, j) - model3d.vertex(0, i);
                double Cy = model3d.vertex(1, j) - model3d.vertex(1, i);
                double Cz = model3d.vertex(2, j) - model3d.vertex(2, i);
                double L = instrument->material[model3d.edge(i,j)].youngsModulusY/std::sqrt(Cx * Cx + Cy * Cy + Cz * Cz);
                Cx *= L; Cy *= L; Cz *= L;

                this->makeDiagonalSpring(i*3,     j*3,      1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i*3,     j*3 + 3, -1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i*3 + 3, j*3,     -1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i*3 + 3, j*3 + 3,  1, Cx, Cy, Cz);
            }
        }
    }
}

void InstrumentSimulator::calculateMass() {
    Model3D& model3d         = instrument->model3d;
    PrecalModel& precalModel = instrument->precalModel;
    precalModel.massM = Eigen::VectorXd(model3d.vertex.cols());

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

void InstrumentSimulator::calculateMassSpringSystem() {
    this->calculateSpring();
    this->calculateMass();
}


void InstrumentSimulator::calcuateDoformationModeling() {
    PrecalModel& precalModel = instrument->precalModel;

    precalModel.solver = Eigen::EigenSolver<Eigen::MatrixXd>(precalModel.springK, true);
    Eigen::MatrixXcd eigenvaluesD =  precalModel.solver.eigenvalues();
    precalModel.possitiveW = Eigen::VectorXcd(eigenvaluesD.size());
    precalModel.negativeW  = Eigen::VectorXcd(eigenvaluesD.size());
    std::complex<double> fluidDampingV        =  instrument->material[1].fluidDampingV;
    std::complex<double> viscoelasticDampingN =  instrument->material[1].viscoelasticDampingN;

    for (int i = 0; i < eigenvaluesD.size(); ++i) {
        std::complex<double> aux =
            fluidDampingV * eigenvaluesD(i) + viscoelasticDampingN;

        precalModel.possitiveW(i) =
            (-aux + std::sqrt(aux * aux - 4. * eigenvaluesD(i))) / 2.;

        precalModel.negativeW(i) =
            (-aux - std::sqrt(aux * aux - 4. * eigenvaluesD(i))) / 2.;
    }

    precalModel.gainOfModeC = Eigen::VectorXcd(eigenvaluesD.size());
    precalModel.gainOfModeC.fill(0.0f);
}

void InstrumentSimulator::calculateImpulsForces(Eigen::VectorXd forcesF, double time) {
    PrecalModel& precalModel = instrument->precalModel;
    // G es real unicament
    Eigen::MatrixXcd forcesG =  precalModel.solver.eigenvectors().inverse() * forcesF;

    for (int i = 0; i < precalModel.gainOfModeC.size(); ++i) {
        std::complex<double> diff         = precalModel.possitiveW(i) - precalModel.negativeW(i);
        std::complex<double> poweredEuler =
            std::pow(instrument->euler, precalModel.possitiveW(i).real()) *
            (cos(precalModel.possitiveW(i).imag() * time) + (sin(precalModel.possitiveW(i).imag() * time) * 1.i));
        precalModel.gainOfModeC(i) =
            precalModel.gainOfModeC(i) + (forcesG(i) / (precalModel.massM(i / 3) * diff * poweredEuler));
    }
}

void InstrumentSimulator::calculateVibrations(double time) {
    PrecalModel& precalModel = instrument->precalModel;

    precalModel.modesOfVibrationZ = Eigen::VectorXcd(precalModel.gainOfModeC);

    for (int i = 0; i < precalModel.modesOfVibrationZ.size(); ++i) {
        std::complex<double> Ci          = precalModel.gainOfModeC(i);
        std::complex<double> CiConj      = std::conj(precalModel.gainOfModeC(i));
        std::complex<double> eulerPowPos =
            std::pow(instrument->euler, precalModel.possitiveW(i).real()) *
            (cos(precalModel.possitiveW(i).imag() * time) + (sin(precalModel.possitiveW(i).imag() * time) * 1.i));
        std::complex<double> eulerPowNeg =
            std::pow(instrument->euler, precalModel.negativeW(i).real()) *
            (cos(precalModel.negativeW(i).imag() * time)  + (sin(precalModel.negativeW(i).imag()  * time) * 1.i));

        precalModel.modesOfVibrationZ(i) = (Ci * eulerPowPos) + (CiConj * eulerPowNeg);
    }
}
