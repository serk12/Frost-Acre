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

void ObjManager::getVectorsAndEdgesFromObj(std::ifstream& infile,
                                           EdgeQueue& edgesQueue,
                                           VertexQueue& vertexQueue) {
    std::string line;
    while (std::getline(infile, line)) {
        // v -1.000000 -1.000000 -1.000000
        if (line[0] == 'v' and line[1] == ' ') {
            std::vector<std::string> vertex = ObjManager::splitString(line, ' ');
            vertexQueue.push(vertex);
        }
        else if (line[0] == 'f') { // f 1/1/1 2/2/1 3/3/1  v/t/vn
            std::vector<std::string> faces = ObjManager::splitString(line, ' ');
            std::vector<std::pair<std::string, std::string> > faceAndText(3);

            for (int i = 1; i < 4; ++i) {
                std::vector<std::string> triangle = ObjManager::splitString(faces[i], '/');
                if (triangle[1] == "") triangle[1] = "1";
                faceAndText[i - 1] = std::make_pair(triangle[0], triangle[1]);
            }
            edgesQueue.push(faceAndText);
        }
    }
}

Model3D ObjManager::createMoldel(EdgeQueue& edgesQueue, VertexQueue& vertexQueue) {
    Model3D model3d;
    model3d.vertex = Eigen::MatrixXd(3, vertexQueue.size());
    model3d.edge   = Eigen::MatrixXi::Zero(vertexQueue.size(), vertexQueue.size());
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
        int el1 = std::stod(edgesQueue.front()[0].first) - 1;
        int el2 = std::stod(edgesQueue.front()[1].first) - 1;
        int el3 = std::stod(edgesQueue.front()[2].first) - 1;

        int te1 = std::stod(edgesQueue.front()[0].second);
        int te2 = std::stod(edgesQueue.front()[1].second);
        int te3 = std::stod(edgesQueue.front()[2].second);

        model3d.edge(el1, el3) = te1;
        model3d.edge(el3, el1) = te3;

        model3d.edge(el1, el2) = te1;
        model3d.edge(el2, el1) = te2;

        model3d.edge(el2, el3) = te2;
        model3d.edge(el3, el2) = te3;


        model3d.edge(el1, el1) = te1;
        model3d.edge(el2, el2) = te2;
        model3d.edge(el3, el3) = te3;

        edgesQueue.pop();
        ++i;
    }

    return model3d;
}

Model3D ObjManager::readObj(std::string filepath) {
    std::ifstream infile(filepath);

    EdgeQueue   edgesQueue;
    VertexQueue vertexQueue;

    ObjManager::getVectorsAndEdgesFromObj(infile, edgesQueue, vertexQueue);
    return ObjManager::createMoldel(edgesQueue, vertexQueue);
}
