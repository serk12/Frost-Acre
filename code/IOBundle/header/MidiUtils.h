#ifndef MIDIUTILS_HH
#define MIDIUTILS_HH

#include <Eigen/Dense>

struct Pluck {
    Eigen::VectorXd force;
    float           timeForce;
    float           timeDur;
    float           timeStart;
    int             note;
};

#endif // ifndef MIDIUTILS_HH
