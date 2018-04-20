#ifndef STRING_HH
#define STRING_HH

#include "Utils.h"

struct Model3D {
    Eigen::Matrix4Xd vertex; // rows indicate vertex 0,1,2,3 = x, y, z, ¿w?
    Eigen::MatrixXd  edge;   // matriz de adyacencia 1 o 0 si hay o no hay
};

struct PrecalModel {
    Eigen::VectorXd massM;                    // calculateMassSpringSystem
    Eigen::MatrixXd springK;

    Eigen::VectorXd dampingCoefficientModeWR; // calcuateDoformationModeling
    Eigen::VectorXd angularFrequencyModeWI;

    Eigen::VectorXd modesOfVibrationZ;        // calculateImpulsForces
    Eigen::VectorXd gainOfModeC;
};

class String {
public:
    String();
    String(Model3D& model3D);
    String(PrecalModel& precalModel);

    bool existsPrecalModel() const;

    void setName(std::string name);
    std::string getName() const;

    void setModel3D(Model3D& model3D);
    void getModel3D(Model3D& model3D);

    void setPrecalModel(PrecalModel& precalModel);
    void getPrecalModel(PrecalModel& precalModel);
private:
    std::string name;
    Model3D *model3D;
    PrecalModel *precalModel;
};

#endif // ifndef STRING_HH
