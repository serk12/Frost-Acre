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

void StringSimulator::calculatePrecal() {
    this->calculateMassSpringSystem();
    this->calcuateDoformationModeling();
}

void StringSimulator::calculateMassSpringSystem() {
    std::cout << "NANI" << std::endl;
}

void StringSimulator::calcuateDoformationModeling() {}
