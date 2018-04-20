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

void StringSimulator::calculateMassSpringSystem() {
    Model3D model3d;
    string->getModel3D(model3d);
    PrecalModel precalModel;
    string->setPrecalModel(precalModel);
    precalModel.springK = Eigen::MatrixXd(model3d.vertex.rows(),
                                          model3d.vertex.cols());

    for (int i = 0; i < model3d.edge.cols(); ++i) {
        for (int j = 0; j < model3d.edge.rows(); ++j) {
            precalModel.springK(j, i) =
                model3d.edge(j, i) * instrument->thicknessT * instrument->elasticityK;
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
    precalModel.angularFrequencyModeWI   = Eigen::VectorXd(eigenvaluesD.size());
    precalModel.dampingCoefficientModeWR = Eigen::VectorXd(eigenvaluesD.size());

    for (int i = 0; i < eigenvaluesD.size(); ++i) {
        double auxI =
            instrument->fluidDampingV *eigenvaluesD(i).imag() +
            instrument->viscoelasticDampingN;
        precalModel.angularFrequencyModeWI(i) =
            (-auxI + std::sqrt(auxI * auxI - 4.0f * eigenvaluesD(i).imag())) / 2.0f;

        double auxR =
            instrument->fluidDampingV *eigenvaluesD(i).real() +
            instrument->viscoelasticDampingN;
        precalModel.dampingCoefficientModeWR(i) =
            (-auxR + std::sqrt(auxR * auxR - 4.0f * eigenvaluesD(i).real())) / 2.0f;
    }

    precalModel.gainOfModeC = Eigen::VectorXd(eigenvaluesD.size());
    precalModel.gainOfModeC.fill(0.0f);
}

void  StringSimulator::calculateImpulsForces(Eigen::VectorXd forcesF, double time) {
    PrecalModel precalModel;
    string->getPrecalModel(precalModel);
    Eigen::EigenSolver<Eigen::MatrixXd> es(precalModel.springK, false);
    auto eigenvectorsG = es.eigenvectors().inverse() * forcesF;

    for (int i = 0; i < precalModel.gainOfModeC.size(); ++i) {
        double diff = precalModel.dampingCoefficientModeWR(i) - precalModel.angularFrequencyModeWI(i);
        // precalModel.gainOfModeC(i) =
        //     precalModel.gainOfModeC(i) +
        //     ((eigenvectorsG(i)) /
        //      (precalModel.massM(i) * diff *
        //       std::pow(instrument->euler,
        // precalModel.dampingCoefficientModeWR(i) * time)));
    }
}
