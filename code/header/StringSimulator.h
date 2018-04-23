#ifndef STRINGSIMULATOR_HH
#define STRINGSIMULATOR_HH

#include "Utils.h"
#include "String.h"
#include "Sound.h"
#include "Instrument.h"

// posible mejora, hacer la clase unica y estatica
class StringSimulator {
public:
    StringSimulator();
    StringSimulator(String& string, bool calculateNow);
    void setString(String& string);
    void setInstrument(Instrument& instrument);
    // Sound runSimulator(String& string);
    // Sound runSimulator();

protected:

    void calculatePrecal();
    void calculateMassSpringSystem();
    void calcuateDoformationModeling();
    void calculateImpulsForces(Eigen::MatrixXd forcesF, double time);

private:
    // posible mejora, tenerlos por referencia
    String *string;
    Instrument *instrument;
};

#endif // ifndef STRINGSIMULATOR_HH
