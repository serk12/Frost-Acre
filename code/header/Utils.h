#ifndef UTILS_HH
#define UTILS_HH

#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <cmath>

struct Model3D {
    Eigen::MatrixXd vertex;
    Eigen::MatrixXd edge;
};

struct PrecalModel {
    Eigen::MatrixXf massM;
    Eigen::MatrixXf springK;

    Eigen::VectorXf modesOfVibrationZ;
    Eigen::MatrixXf dampingCoefficientModeWR;
    Eigen::MatrixXf angularFrequencyModeWI;
    Eigen::VectorXf gainOfModeC;
};

#endif // ifndef UTILS_HH
