#include "Controller/header/Controller.h"
#include "DebugUtils.h"

int main() {
    Controller controller("./test/E4/E4_30.obj", "./test/E4/E4.json");
    controller.run();
}
