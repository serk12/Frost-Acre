#include "Controller/header/Controller.h"

int main() {
    Controller controller("./test/simpleForm/simpleForm.obj", "./test/cube/cube.json", "./test/midis/moonlight_sonata.mid", "nande?");
    controller.run();
}
