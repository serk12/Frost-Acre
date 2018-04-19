#include "../header/StringSimulator.h"

StringSimulator::StringSimulator() {
    string = new String();
}

StringSimulator::StringSimulator(String& string, bool calculateNow)
    : StringSimulator() {
    this->setString(string);

    if (calculateNow) {
        this->calculateMassSpringSystem();
        this->calcuateDoformationModeling();
    }
}

void StringSimulator::setString(String& string) {
    this->string = string;
}

void StringSimulator::updatePrecalModelToString(String& string) {
    this->string = string;
    calculatePrecal();
}

void StringSimulator::calculatePrecal() {
    this->calculateMassSpringSystem();
    this->calcuateDoformationModeling();
}

void StringSimulator::calculateMassSpringSystem() {}

void StringSimulator::calcuateDoformationModeling() {}
