#include "../header/ResonanceSimulator.h"

void ResonanceSimulator::setScalarForceLost(double scalar) {
    scalarForceLost = scalar;
}

void ResonanceSimulator::setConstantForceLost(double constant) {
    constanForceLost = constant;
}

bool isDivisible(double num) {
    return num != 0 and Instrument::isNumerical(num);
}

void ResonanceSimulator::precalcResonanceQuotient(Instrument& instrument) {
    PrecalModel& precalModel = instrument.precalModel;
    int size                 = precalModel.possitiveW.size();
    instrument.resonanceRatio = Eigen::VectorXd::Zero(size);
    for (int i = 0; i < size; ++i) {
        double possWI = precalModel.possitiveW[i].real();
        double negWI  = precalModel.negativeW[i].real();
        if (isDivisible(possWI) and isDivisible(negWI)) {
            for (int j = 0; j < size; ++j) {
                double possWJ = precalModel.possitiveW[j].real();
                double negWJ  = precalModel.negativeW[j].real();
                if (isDivisible(possWJ) and isDivisible(negWJ)) {
                    instrument.resonanceRatio[i] += (possWI / possWJ) + (negWI / negWJ);
                }
            }
        }
    }
}

Eigen::VectorXd ResonanceSimulator::calculateResonanceForce(const Instrument& instrument, const Eigen::VectorXd& force) {
    const Eigen::VectorXd& resonance = instrument.resonanceRatio;

    Eigen::VectorXd result(force);
    for (int i = 0; i < result.size(); ++i) {
        double f = result[i] * constanForceLost - scalarForceLost;
        result[i] = resonance[i] * ((f > 0.0) ? f : 0.0);
    }
    return result;
}
