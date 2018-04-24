#include "../header/String.h"

String::String() {
    precalModel = nullptr;
}

String::String(Model3D& model3D) {
    this->model3D = &model3D;
    precalModel   = nullptr;
}

String::String(PrecalModel& precalModel) {
    this->precalModel = &precalModel;
}

bool String::existsPrecalModel() const {
    return precalModel == nullptr;
}

void String::setName(std::string name) {
    this->name = name;
}

std::string String::getName() const {
    return name;
}

void String::setModel3D(Model3D& model3D) {
    this->model3D = &model3D;
}

void String::getModel3D(Model3D& model3D) {
    model3D = *this->model3D;
}

void String::setPrecalModel(PrecalModel& precalModel) {
    this->precalModel = &precalModel;
}

void String::getPrecalModel(PrecalModel& precalModel) {
    precalModel = *this->precalModel;
}
