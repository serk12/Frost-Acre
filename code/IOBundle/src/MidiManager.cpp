#include "../header/MidiManager.h"

std::vector<Pluck> MidiManager::parseMidiFile(std::string midiPath) {
    smf::MidiFile midiFile;
    midiFile.read(midiPath);  midiFile.joinTracks(); midiFile.doTimeAnalysis();
    std::vector<Pluck> v;

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        Pluck pluck;

        for (int event = 0; event < midiFile[track].size(); ++event) {
            if (midiFile[track][event].isNoteOn()) {
                pluck.timeStart = midiFile[track][event].seconds;
                // ToDo no es la mejor solucion el "+1" pero funciona
                pluck.timeDur   = midiFile[track][event + 1].seconds - midiFile[track][event].seconds;
                pluck.timeForce = 0.001;
                pluck.note      = midiFile[track][event].getKeyNumber();
                v.push_back(pluck);
            }
        }
    }
    return v;
}

std::map<std::string, Eigen::VectorXd> MidiManager::buildMapForces(std::string midiPath) {
    smf::MidiFile midiFile;
    midiFile.read(midiPath); midiFile.joinTracks(); midiFile.doTimeAnalysis();
    std::map<std::string, Eigen::VectorXd> notes;

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        for (int event = 0; event < midiFile[track].size(); ++event) {
            if (midiFile[track][event].isNoteOn()) {
                notes[std::to_string(midiFile[track][event].getKeyNumber())] = Eigen::VectorXd();
            }
        }
    }
    return notes;
}




//
