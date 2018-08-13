#include "../header/Instrument.h"

Instrument::Instrument() {
    euler = std::exp(1.0);
}

Instrument::Instrument(Model3D& model3d) : Instrument() {
    this->model3d = model3d;
}

Instrument::Instrument(std::vector<Material>& material, Model3D& model3d, Resonance& resonance, Pickup& pickup)
    : Instrument(model3d) {
    this->resonance = resonance;
    this->pickup    = pickup;

    this->material = std::vector<Material>(material.size());

    for (unsigned int i = 0; i < material.size(); ++i) {
        this->material[i] = material[i];
    }
}

Instrument::Instrument(Instrument& inst) : Instrument(inst.material, inst.model3d, inst.resonance, inst.pickup) {
    this->precalModel    = inst.precalModel;
    this->resonanceRatio = inst.resonanceRatio;
}

bool Instrument::isNumerical(double num) {
    return not std::isnan(num) and not std::isinf(num);
}
