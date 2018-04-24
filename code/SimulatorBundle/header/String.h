#ifndef STRING_HH
#define STRING_HH

#include "../../Utils.h"

typedef Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> MatrixXB;

struct Model3D {
    Eigen::Matrix3Xd vertex; // rows indicate vertex 0,1,2 = x, y, z
    MatrixXB         edge;   // matriz de adyacencia 1 o 0 si hay o
    // no hay
};

struct PrecalModel {
    Eigen::VectorXd massM;              // calculateMassSpringSystem
    Eigen::MatrixXd springK;

    Eigen::VectorXcd possitiveW;        // calcuateDoformationModeling
    Eigen::VectorXcd negativeW;

    Eigen::VectorXd  modesOfVibrationZ; // calculateImpulsForces
    Eigen::VectorXcd gainOfModeC;
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
