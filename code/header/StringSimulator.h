#ifndef STRINGSIMULATOR_HH
#define STRINGSIMULATOR_HH

#include "Utils.h"
#include "String.h"

class StringSimulator {
public:
    StringSimulator();
    StringSimulator(String& string, bool calculateNow);

    void setInstrument(String& string);
    void updatePrecalModelToString(String& string);

protected:
    void calculatePrecal();
    void calculateMassSpringSystem();
    void calcuateDoformationModeling();
    // void calculateImpulsForces(Eigen::VectorXf forcesF);

private:
    // posible mejora, tenerlos por referencia
    String& string;
};

#endif // ifndef STRINGSIMULATOR_HH
