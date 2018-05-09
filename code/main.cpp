#include "Controller/header/Controller.h"

int main() {
    Controller controller("./test/cube/cube.obj", "./test/cube/cube.json", "./test/midis/moonlight_sonata.mid", "nande?");
    controller.run();
}
