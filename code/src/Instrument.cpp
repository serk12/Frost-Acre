#include "../header/Instrument.h"

Instrument::Instrument() {
    euler = std::exp(1.0);
}

Instrument::Instrument(Eigen::Matrix3Xd ver, Eigen::MatrixXd ed, float e,
                       float t, float y, float d, float v, float n)
    : Instrument() {
    model3D.vertex = ver; model3D.edge   = ed; elasticityK = e;
    thicknessT     = t;   youngsModulusY = y;  densityD    = d;
    fluidDampingV  = v;   viscoelasticDampingN = n;
}
