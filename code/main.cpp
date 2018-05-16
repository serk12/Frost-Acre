#include "Controller/header/Controller.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {}
    else if (argc == 5) {
        Controller controller(argv[1], argv[2], argv[3], argv[4]);
        controller.run();
    }
}
