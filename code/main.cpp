#include "Controller/header/Controller.h"

int main(int argc, char *argv[]) {
    if (argc == 6) { // run simulator
        //                    obj3D    json     midi     jsonNote wavout
        Controller controller(argv[1], argv[2], argv[3], argv[4], argv[5]);
        controller.run();
    }
    else if (argc == 4) { // write jsonMidiFile or preRender
        //                    obj3D    midi/json jsonWrite
        Controller  controller(argv[1], argv[2],  argv[3]);
        std::string info = std::string(argv[2]);
        if (info[info.size() - 1] == 'd') {
            controller.writeJsonMidi();
        }
        else {
            controller.calcPrerender();
        }
    }
}
