#include "../header/ResonanceSimulator.h"

void ResonanceSimulator::setScalarForceLost(double scalar) {
    scalarForceLost = scalar;
}

void ResonanceSimulator::setLinewidthResonance(double linewidth) {
    linewidthResonance = linewidth;
}

void ResonanceSimulator::setConstantForceLost(double constant) {
    constanForceLost = constant;
}

bool isDivisible(double num) {
    return num != 0 && Instrument::isNumerical(num);
}


inline double calculateResonance(double w, double O, double r) {
    double diff    = w - O;
    double cocient = r / 2;
    return 1.0f / (diff * diff + cocient * cocient);
}

void ResonanceSimulator::precalcResonanceQuotient(Instrument& instrument) {
    PrecalModel& precalModel = instrument.precalModel;
    int size                 = precalModel.possitiveW.size();
    instrument.resonanceRatio = Eigen::VectorXd::Zero(size);
    for (int i = 0; i < size; ++i) {
        double possWI = precalModel.possitiveW[i].real();
        double negWI  = precalModel.negativeW[i].real();
        if (isDivisible(possWI) && isDivisible(negWI)) {
            for (int j = 0; j < size; ++j) {
                double possWJ = precalModel.possitiveW[j].real();
                double negWJ  = precalModel.negativeW[j].real();
                if (isDivisible(possWJ) && isDivisible(negWJ)) {
                    instrument.resonanceRatio[i] += calculateResonance(possWI, possWJ, linewidthResonance) +
                                                    calculateResonance(negWI,   negWJ, linewidthResonance);
                }
            }
        }
    }
}

Eigen::VectorXd ResonanceSimulator::calculateResonanceForce(const Instrument& instrument, const Eigen::VectorXd& force) {
    const Eigen::VectorXd& resonance = instrument.resonanceRatio;

    Eigen::VectorXd result(force);
    for (int i = 0; i < result.size(); ++i) {
        double f = result[i] - (result[i] * scalarForceLost) - constanForceLost;
        result[i] = resonance[i] * ((f > 0.0) ? f : 0.0);
    }
    return result;
}
