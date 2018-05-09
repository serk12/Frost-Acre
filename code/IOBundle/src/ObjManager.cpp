#include "../header/ObjManager.h"

std::vector<std::string> ObjManager::splitString(const std::string& s, const char token) {
    std::stringstream ss(s);
    std::vector<std::string> result;

    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, token);

        if (substr.size() != 0) {
            result.push_back(substr);
        }
    }
    return result;
}

Model3D ObjManager::readObj(std::string filepath) {
    std::ifstream infile(filepath);
    std::string   line;
    std::queue<std::vector<std::string> > edgesQueue;
    std::queue<std::vector<std::string> > vertexQueue;

    while (std::getline(infile, line)) {
        if (line[0] == 'v' and line[1] == ' ') {
            std::vector<std::string> vertex = ObjManager::splitString(line, ' ');
            vertexQueue.push(vertex);
        }
        else if (line[0] == 'f') {
            std::vector<std::string> faces = ObjManager::splitString(line, ' ');
            std::vector<std::string> face(3);

            for (int i = 1; i < 4; ++i) {
                std::vector<std::string> triangle = ObjManager::splitString(faces[i], '/');
                face[i - 1] = triangle[0];
            }
            edgesQueue.push(face);
        }
    }

    Model3D model3d;
    model3d.vertex = Eigen::MatrixXd(3, vertexQueue.size());
    model3d.edge   = MatrixXB::Zero(vertexQueue.size(), vertexQueue.size());
    int i = 0;

    while (!vertexQueue.empty()) {
        model3d.vertex(0, i) = std::stod(vertexQueue.front()[1]);
        model3d.vertex(1, i) = std::stod(vertexQueue.front()[2]);
        model3d.vertex(2, i) = std::stod(vertexQueue.front()[3]);
        vertexQueue.pop();
        ++i;
    }

    i = 0;

    while (!edgesQueue.empty()) {
        int el1 = std::stod(edgesQueue.front()[0]) - 1;
        int el2 = std::stod(edgesQueue.front()[1]) - 1;
        int el3 = std::stod(edgesQueue.front()[2]) - 1;

        model3d.edge(el1, el3) = true;
        model3d.edge(el3, el1) = true;

        model3d.edge(el1, el2) = true;
        model3d.edge(el2, el1) = true;

        model3d.edge(el2, el3) = true;
        model3d.edge(el3, el2) = true;

        edgesQueue.pop();
        ++i;
    }

    return model3d;
}
