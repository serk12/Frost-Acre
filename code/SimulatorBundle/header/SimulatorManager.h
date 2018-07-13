#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

#include "../../Controller/header/DebugController.h"
#include "InstrumentSimulator.h"
#include "PickupSimulator.h"

#include <vector>
#include <math.h>

class SimulatorManager : public InstrumentSimulator, public PickupSimulator {
public:
    static const double SampleRate;

    SimulatorManager();
    void precallSimulator(Instrument& instrument);
    void calculateFrame(const Eigen::VectorXd& forcesF, double timeF, double timeV, std::vector<double>& waves);
};

#endif // ifndef SIMULATORMANAGER_HH
