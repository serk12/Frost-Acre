#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

#include "../../Controller/header/DebugController.h"
#include "InstrumentSimulator.h"
#include "ResonanceSimulator.h"
#include "PickupSimulator.h"
#include "Instrument.h"

#include <vector>
#include <math.h>

class SimulatorManager : public InstrumentSimulator, public PickupSimulator, public ResonanceSimulator {
public:
    static const double SampleRate;

    SimulatorManager();
    void setPrerender(Instrument& instrument);
    void precallSimulator(Instrument& instrument);
    void calculateFrame(const Eigen::VectorXd& forcesF, double timeF, double timeV, std::vector<double>& waves);

private:
    Eigen::VectorXd resonanceForce;
};

#endif // ifndef SIMULATORMANAGER_HH
