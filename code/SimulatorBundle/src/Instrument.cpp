#include "../header/Instrument.h"

Instrument::Instrument() {
    euler = std::exp(1.0);
}

Instrument::Instrument(Model3D& model3d) : Instrument() {
    this->model3d = model3d;
}

Instrument::Instrument(std::vector<Material>& material, Model3D& model3d)
    : Instrument(model3d) {
    this->material = std::vector<Material>(material.size());

    for (int i = 0; i < material.size(); ++i) {
        this->material[i] = material[i];
    }
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
