#include "../header/MidiManager.h"

std::vector<Pluck> MidiManager::parseMidiFile(std::string midiPath, std::string jsonFile) {
    std::map<std::string, Eigen::VectorXd> notes = MidiManager::getMapForces(jsonFile);

    smf::MidiFile midiFile;
    midiFile.read(midiPath);
    midiFile.doTimeAnalysis();

    int size = 0;

    for (int track = 0; track < midiFile.getTrackCount(); ++track)  {
        size += midiFile[track].size();
    }

    std::vector<Pluck> v(size);
    int i = 0;

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        Pluck pluck;

        for (int event = 0; event < midiFile[track].size(); ++event) {
            pluck.timeStart = midiFile[track][event].seconds;
            pluck.timeDur   = midiFile[track][event].getDurationInSeconds();
            pluck.timeForce = 0.1;
            std::string message = "";

            for (unsigned int i = 0; i < midiFile[track][event].size(); ++i) {
                message += std::to_string(midiFile[track][event][i]);
            }

            pluck.force = notes[message];
            v[i++]      = pluck;
        }
    }
    return v;
}

std::map<std::string, Eigen::VectorXd> MidiManager::getMapForces(std::string jsonFile) {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    std::map<std::string, Eigen::VectorXd> plucking;

    for (rapidjson::Value::ConstMemberIterator it = doc.MemberBegin(); it != doc.MemberEnd(); ++it) {
        const rapidjson::Value& force = it->value;
        Eigen::VectorXd f(force.Size());

        for (unsigned int i = 0; i < force.Size(); ++i) {
            f(i) = force[i].GetDouble();
        }
        plucking[it->name.GetString()] = f;
    }

    return plucking;
}
