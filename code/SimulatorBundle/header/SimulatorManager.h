#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

#include "../../Controller/header/DebugController.h"
#include "InstrumentSimulator.h"
#include <list>

class SimulatorManager : protected InstrumentSimulator {
public:
    static const double SampleRate;

    SimulatorManager();
    void precallSimulator(Instrument& instrument);
    std::list<double> calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV);
private:

private:
};

#endif // ifndef SIMULATORMANAGER_HH
