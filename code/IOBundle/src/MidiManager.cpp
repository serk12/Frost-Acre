#include "../header/MidiManager.h"

std::vector<Pluck> MidiManager::parseMidiFile(std::string midiPath, std::string jsonFile) {
    std::map<smf::MidiMessage, Eigen::VectorXd> notes = this->getMapForces(jsonFile);

    std::vector<Pluck> v;

    smf::MidiFile midiFile;
    midiFile.read(midiPath);
    midiFile.doTimeAnalysis();

    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        Pluck pluck;

        for (int event = 0; event < midiFile[track].size(); ++event) {
            float init = midifile[track][event].seconds;
            float dur  = midifile[track][event].getDurationInSeconds();

            // for (int i = 0; i < midifile[track][event].size(); ++i) {
            //     cout << midifile[track][event][i];
            // }
        }
    }
    return v;
}

std::map<smf::MidiMessage, Eigen::VectorXd> MidiManager::getMapForces(std::string jsonFile) {
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
