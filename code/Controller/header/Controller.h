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
    Controller(std::string objFile, std::string midiJsonFile);
    Controller(std::string objFile, std::string infoFile, std::string writeFile);
    Controller(std::string prerenderFile, std::string midiFile,
               std::string midiJsonFile, std::string wavFile);
    void run();
    void calcPrerender();

private:
    inline std::vector<double> runSimulator(const std::vector<Pluck>& plucks,
                                            const std::map<int, Eigen::VectorXd>& notes,
                                            SimulatorManager& simMan);
};

#endif // ifndef CONTROLLER_HH
