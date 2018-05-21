#include "../header/MidiManager.h"

std::vector<Pluck> MidiManager::parseMidiFile(std::string midiPath, std::string jsonFile) {
    smf::MidiFile midiFile;
    midiFile.read(midiPath);  midiFile.joinTracks(); midiFile.doTimeAnalysis();

    std::map<std::string, Eigen::VectorXd> notes = MidiManager::getMapForces(jsonFile);
    std::vector<Pluck> v;

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        Pluck pluck;

        for (int event = 0; event < midiFile[track].size(); ++event) {
            if (midiFile[track][event].isNoteOn()) {
                pluck.timeStart = midiFile[track][event].seconds;
                pluck.timeDur   = midiFile[track][event].getDurationInSeconds();
                pluck.timeForce = 0.1;
                pluck.note      = midiFile[track][event].getKeyNumber();
                pluck.force     = notes[std::to_string(pluck.note)];
                v.push_back(pluck);
            }
        }
    }
    return v;
}

std::vector<double> explode(const std::string& s, const char delim)
{
    std::vector<double> result;
    std::istringstream  iss(s);

    for (std::string token; std::getline(iss, token, delim);)
    {
        result.push_back(std::stod(std::move(token)));
    }
    return result;
}

std::map<std::string, Eigen::VectorXd> MidiManager::getMapForces(std::string jsonFile) {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    std::map<std::string, Eigen::VectorXd> notes;

    for (auto& val : doc[JsonManager::MAPNOTES.c_str()].GetObject()) {
        std::vector<double> forces = explode(val.value.GetString(), '\n');
        Eigen::VectorXd     f      = Eigen::VectorXd::Map(forces.data(), forces.size());
        notes[val.name.GetString()] = f;
    }

    return notes;
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
