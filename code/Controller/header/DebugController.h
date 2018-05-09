#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>

#include "../../SimulatorBundle/header/Instrument.h"
#include "../../SimulatorBundle/header/EigenUtils.h"
#include "../../IOBundle/header/MidiUtils.h"

class DebugController {
public:
    static std::chrono::high_resolution_clock::time_point CLOCK;

    static void print(const Model3D& model3d);
    static void print(const PrecalModel& precalModel);
    static void print(const Material& material);
    static void print(const std::vector<Material>& material);
    static void print(const Instrument& instrument);
    static void print(const Pluck& pluck);
    static void print(std::string text);

    static void startClock();
};

#endif // ifndef UTILS_HH
