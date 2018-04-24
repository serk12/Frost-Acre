#ifndef STRING_HH
#define STRING_HH

#include "../../Utils.h"
#include "../../EigenUtils.h"


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
