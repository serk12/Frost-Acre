#include "Controller/header/Controller.h"
#include "DebugUtils.h"

int main() {
    Controller controller("./test/cube/cube.obj", "./test/cube/cube.json");

    controller.run();
}
