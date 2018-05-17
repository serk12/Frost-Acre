#ifndef STRINGSIMULATOR_HH
#define STRINGSIMULATOR_HH
#define M_PI 3.14159265358979323846

#include "../../Controller/header/DebugController.h"

#include "Instrument.h"

// posible mejora, hacer la clase unica y estatica
class InstrumentSimulator {
public:
    InstrumentSimulator();
    InstrumentSimulator(Instrument& instrument, bool calculateNow);
    void setInstrument(Instrument& instrument);

protected:
    void calculatePrecal();
    void calculateMassSpringSystem();
    void calcuateDoformationModeling();

    void calculateImpulsForces(Eigen::VectorXd forcesF, double time);

    void calculateVibrations(double time);

private:
    void calculateMass();
    void calculateSpring();
    void makeDiagonalSpring(int x, int y, int negative, double Cx, double Cy, double Cz);
    Instrument *instrument;
};

#endif // ifndef STRINGSIMULATOR_HH
