#include "../header/Instrument.h"

Instrument::Instrument() {
    euler = std::exp(1.0);
}

Instrument::Instrument(Model3D& model3d) : Instrument() {
    this->model3d = model3d;
}

Instrument::Instrument(Model3D& model3d, double e, double t,
                       double y, double d, double f, double v, double n)
    : Instrument(model3d) {
    elasticityK   = e;
    thicknessT    = t;   youngsModulusY = y;  densityD    = d;
    fluidDampingV = v;   viscoelasticDampingN = n;
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
