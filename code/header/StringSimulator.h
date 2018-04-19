#ifndef STRINGSIMULATOR_HH
#define STRINGSIMULATOR_HH

#include "Utils.h"
#include "String.h"
#include "Sound.h"

// posible mejora, hacer la clase unica y estatica
class StringSimulator {
public:
    StringSimulator();
    StringSimulator(String& string, bool calculateNow);
    void setString(String& string);
    // Sound runSimulator();

protected:
    // Sound simulateString();

    void calculatePrecal();
    void calculateMassSpringSystem();
    void calcuateDoformationModeling();
    // void calculateImpulsForces(Eigen::VectorXf forcesF);

private:
    // posible mejora, tenerlos por referencia
    String *string;
};

#endif // ifndef STRINGSIMULATOR_HH
