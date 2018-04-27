#include "../header/Instrument.h"

Instrument::Instrument() {
    euler = std::exp(1.0);
}

Instrument::Instrument(Model3D& model3d) : Instrument() {
    this->model3d = model3d;
}

Instrument::Instrument(double k, double t, double y, double d,
                       double v, double n, Model3D& model3d)
    : Instrument(model3d) {
    elasticityK    = k; thicknessT           = t;
    youngsModulusY = y; densityD             = d;
    fluidDampingV  = v; viscoelasticDampingN = n;
}

void Instrument::setModel3D(Model3D& model3d) {
    this->model3d = model3d;
}

void Instrument::getModel3D(Model3D& model3d) {
    model3d = this->model3d;
}

void Instrument::setPrecalModel(PrecalModel& precalModel) {
    this->precalModel = precalModel;
}

void Instrument::getPrecalModel(PrecalModel& precalModel) {
    precalModel = this->precalModel;
}
