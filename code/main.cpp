#include "Controller/header/Controller.h"

int main(int argc, char *argv[]) {
    if (argc == 6) { // run simulator
        Controller controller(argv[1], argv[2], argv[3], argv[4], argv[5]);
        controller.run();
    }
    else if (argc == 3) { // write jsonMidiFile
        Controller controller(argv[1], argv[2]);
        controller.writeJsonMidi();
    }
}
