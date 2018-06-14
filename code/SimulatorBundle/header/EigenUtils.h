#ifndef EIGENUTILS_HH
#define EIGENUTILS_HH

#include <Eigen/Dense>

// typedef Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> MatrixXB;

struct Model3D {
    Eigen::Matrix3Xd vertex; // rows indicate vertex 0,1,2 = x, y, z
    Eigen::MatrixXi  edge;   // matriz de adyacencia 0 si no hay
                             // texturaID en caso que aya
};

struct PrecalModel {
    Eigen::VectorXd massM;              // calculateMassSpringSystem
    Eigen::MatrixXd springK;

    Eigen::VectorXcd possitiveW;        // calcuateDoformationModeling
    Eigen::VectorXcd negativeW;

    Eigen::VectorXcd gainOfModeC;  // calculateImpulsForces

    Eigen::EigenSolver<Eigen::MatrixXd> solver;
};

#endif // ifndef EIGENUTILS_HH
