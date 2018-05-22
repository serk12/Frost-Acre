#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

#include "../../Controller/header/DebugController.h"
#include "InstrumentSimulator.h"
#include <vector>
#include <math.h>

class SimulatorManager : protected InstrumentSimulator {
public:
    static const double SampleRate;

    SimulatorManager();
    void precallSimulator(Instrument& instrument);
    void calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV, std::vector<double>& notes);
};

#endif // ifndef SIMULATORMANAGER_HH
