#include "../header/ControllerCLI.h"

void ControllerCLI::run(int argc, char *argv[]) {
    if (argc == 5) { // run simulator
        //                    obj3D    midi     jsonNote wavout
        Controller controller(argv[1], argv[2], argv[3], argv[4]);
        controller.run();
    }
    else if (argc == 4) { // write jsonMidiFile or preRender
        //                    obj3D    midi/json jsonWrite
        Controller controller(argv[1], argv[2],  argv[3]);
        controller.calcPrerender();
    }
    else if (argc == 3) {
        Controller controller(argv[1], argv[2]);
        controller.writeJsonMidi();
    }
}
