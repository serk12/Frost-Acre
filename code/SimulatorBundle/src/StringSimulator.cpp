#include "../header/StringSimulator.h"

StringSimulator::StringSimulator() {
    string = new String();
}

StringSimulator::StringSimulator(String& string, bool calculateNow) {
    this->setString(string);

    if (calculateNow) {
        this->calculateMassSpringSystem();
        this->calcuateDoformationModeling();
    }
}

void StringSimulator::setString(String& string) {
    this->string = &string;
}

void StringSimulator::setInstrument(Instrument& instrument) {
    this->instrument = &instrument;
}

void StringSimulator::calculatePrecal() {
    this->calculateMassSpringSystem();
    this->calcuateDoformationModeling();
}

void StringSimulator::makeDiagonalSpring(int x, int y, int negative, double Cx, double Cy, double Cz) {
    PrecalModel precalModel;
    string->getPrecalModel(precalModel);

    precalModel.springK(x,     y) += negative * Cx * Cx;
    precalModel.springK(x + 1, y) += negative * Cx * Cy;
    precalModel.springK(x + 2, y) += negative * Cx * Cz;

    precalModel.springK(x,     y + 1) += negative * Cy * Cx;
    precalModel.springK(x + 1, y + 1) += negative * Cy * Cy;
    precalModel.springK(x + 2, y + 1) += negative * Cz * Cy;

    precalModel.springK(x,     y + 2) += negative * Cz * Cx;
    precalModel.springK(x + 1, y + 2) += negative * Cz * Cy;
    precalModel.springK(x + 2, y + 2) += negative * Cz * Cz;
}

void StringSimulator::calculateMassSpringSystem() {
    Model3D model3d;
    string->getModel3D(model3d);
    PrecalModel precalModel;
    string->setPrecalModel(precalModel);
    precalModel.springK = Eigen::MatrixXd::Zero(model3d.vertex.rows() * 3,
                                                model3d.vertex.cols() * 3);

    for (int j = 0; j < model3d.vertex.cols(); ++j) {
        for (int i = 0; i < model3d.vertex.rows(); ++i) {
            if (model3d.vertex(i, j) != 0) {
                double Cx = model3d.edge(j, 0) - model3d.edge(i, 0);
                double Cy = model3d.edge(j, 1) - model3d.edge(i, 1);
                double Cz = model3d.edge(j, 2) - model3d.edge(i, 2);
                double L  = std::sqrt(Cx * Cx + Cy * Cy + Cz * Cz);
                Cx /= L; Cy /= L; Cz /= L;
                this->makeDiagonalSpring(i,     j,      1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i,     j + 3, -1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i + 3, j,     -1, Cx, Cy, Cz);
                this->makeDiagonalSpring(i + 3, j + 3,  1, Cx, Cy, Cz);
            }
        }
    }

    precalModel.massM = Eigen::VectorXd(model3d.vertex.rows());

    for (int i = 0; i < model3d.edge.cols(); ++i) {
        int a = 0;

        for (int j = 0; j < model3d.edge.rows(); ++j) {
            a += model3d.edge(j, i);
        }

        precalModel.massM(i) =
            float(a) * instrument->densityD * instrument->thicknessT;
    }
}

void StringSimulator::calcuateDoformationModeling() {
    PrecalModel precalModel;
    string->getPrecalModel(precalModel);
    Eigen::EigenSolver<Eigen::MatrixXd> es(precalModel.springK, false);
    Eigen::MatrixXcd eigenvaluesD = es.eigenvalues();
    precalModel.possitiveW = Eigen::VectorXcd(eigenvaluesD.size());
    precalModel.negativeW  = Eigen::VectorXcd(eigenvaluesD.size());
    std::complex<double> fluidDampingV        =  instrument->fluidDampingV;
    std::complex<double> viscoelasticDampingN =  instrument->viscoelasticDampingN;

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

void  StringSimulator::calculateImpulsForces(Eigen::VectorXd forcesF, double time) {
    PrecalModel precalModel;
    string->getPrecalModel(precalModel);
    // G es real unicament
    Eigen::EigenSolver<Eigen::MatrixXd> es(precalModel.springK, false);
    auto forcesG = es.eigenvectors().inverse() * forcesF;

    for (int i = 0; i < precalModel.gainOfModeC.size(); ++i) {
        std::complex<double> diff =
            precalModel.possitiveW(i) - precalModel.possitiveW(i);
        std::complex<double> poweredEuler =
            std::pow(instrument->euler, precalModel.possitiveW(i).real()) *
            (cos(precalModel.possitiveW(i).imag() * time) +
             sin(precalModel.possitiveW(i).imag() * time) * 1.i);
        precalModel.gainOfModeC(i) =
            precalModel.gainOfModeC(i) +
            (forcesG(i) / (precalModel.massM(i) * diff * poweredEuler));
    }
}
