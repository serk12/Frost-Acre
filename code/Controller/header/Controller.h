#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <omp.h>
#include <vector>

#include "ControllerIO.h"
#include "DebugController.h"

#include "../../SimulatorBundle/header/Instrument.h"
#include "../../SimulatorBundle/header/SimulatorManager.h"

class Controller : public ControllerIO {
public:
    Controller();
    Controller(std::string objFile, std::string midiFile,
               std::string midiJsonFile);
    Controller(std::string objFile, std::string jsonFile,
               std::string midiFile, std::string midiJsonFile,
               std::string wavFile);
    void run();
    std::vector<double> runSimulator(const std::vector<Pluck>& plucks,
                                     const std::map<int, Eigen::VectorXd>& notes,
                                     SimulatorManager& simMan);
};

#endif // ifndef CONTROLLER_HH
