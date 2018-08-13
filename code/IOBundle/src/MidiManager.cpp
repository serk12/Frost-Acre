#include "../header/MidiManager.h"

std::vector<Pluck> MidiManager::readMidiFile(std::string midiPath) {
    smf::MidiFile midiFile;
    midiFile.read(midiPath); midiFile.sortTracks(); midiFile.doTimeAnalysis();
    std::vector<Pluck> v;

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        Pluck pluck;
        for (int event = 0; event < midiFile[track].size(); ++event) {
            smf::MidiEvent midiEvent = midiFile.getEvent(track, event);
            if (midiEvent.isNoteOn()) {
                pluck.timeStart = midiEvent.seconds;
                pluck.timeDur   = -1;
                pluck.timeForce = 0.001;
                pluck.note      = midiEvent.getKeyNumber();
                v.push_back(pluck);
            }
            if (midiEvent.isNoteOff()) {
                for (unsigned int i = 0; i < v.size(); ++i) {
                    if (v[i].note == midiEvent.getKeyNumber() and v[i].timeDur == -1) {
                        v[i].timeDur = midiEvent.seconds - v[i].timeStart;
                    }
                }
            }
        }
    }
    return v;
}

std::map<std::string, Eigen::VectorXd> MidiManager::buildMapForces(std::string midiPath) {
    smf::MidiFile midiFile;
    midiFile.read(midiPath); midiFile.sortTracks(); midiFile.doTimeAnalysis();
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
