#include "Controller/header/Controller.h"

int main() {
    Controller controller("./test/cube/cube.obj", "./test/E4/E4.json");
    controller.run();
}
