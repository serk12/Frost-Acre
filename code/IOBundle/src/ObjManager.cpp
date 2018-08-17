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

    int material = 0;
    while (std::getline(infile, line)) {
        // v -1.000000 -1.000000 -1.000000 x y z
        if (line[0] == 'v' and line[1] == ' ') {
            std::vector<std::string> vertex = ObjManager::splitString(line, ' ');
            vertexQueue.push(vertex);
        }
        else if (line[0] == 'f') { // f 1/1/1 2/2/1 3/3/1  v/t/vn
            if (material == 0) material = 1;
            std::vector<std::string> faces = ObjManager::splitString(line, ' ');
            std::vector<Edge> faceAndText(3);

            for (int i = 1; i < 4; ++i) {
                std::vector<std::string> edgeV = ObjManager::splitString(faces[i], '/');
                Edge edge;
                edge.vertex        = edgeV[0]; edge.material = material; edge.texture = edgeV[1];
                faceAndText[i - 1] = edge;
            }
            edgesQueue.push(faceAndText);
        }
        else if (line[0] == 'u') {
            ++material;
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
        int el1 = std::stod(edgesQueue.front()[0].vertex) - 1;
        int el2 = std::stod(edgesQueue.front()[1].vertex) - 1;
        int el3 = std::stod(edgesQueue.front()[2].vertex) - 1;

        int ma1 = edgesQueue.front()[0].material;
        int ma2 = edgesQueue.front()[1].material;
        int ma3 = edgesQueue.front()[2].material;

        model3d.edge(el1, el3) = ma1;
        model3d.edge(el3, el1) = ma3;

        model3d.edge(el1, el2) = ma1;
        model3d.edge(el2, el1) = ma2;

        model3d.edge(el2, el3) = ma2;
        model3d.edge(el3, el2) = ma3;


        model3d.edge(el1, el1) = ma1;
        model3d.edge(el2, el2) = ma2;
        model3d.edge(el3, el3) = ma3;

        edgesQueue.pop();
        ++i;
    }

    return model3d;
}

void ObjManager::getTextures(std::ifstream& infile, TextureVector& texturesVanilla) {
    std::string line;
    while (std::getline(infile, line)) {
        // vt 1.00000 1.00000 x y
        if (line[0] == 'v' and line[1] == 't') {
            std::vector<std::string> texture = ObjManager::splitString(line, ' ');
            texturesVanilla.push_back(std::make_pair(std::stod(texture[1]), std::stod(texture[2])));
        }
    }
}

Model3D ObjManager::readObj(std::string filepath) {
    std::ifstream infile(filepath);

    EdgeQueue   edgesQueue;
    VertexQueue vertexQueue;

    ObjManager::getVectorsAndEdgesFromObj(infile, edgesQueue, vertexQueue);
    return ObjManager::createMoldel(edgesQueue, vertexQueue);
}

TextureVector ObjManager::readTexture(std::string filepath) {
    std::ifstream infile(filepath);

    TextureVector texturesVanilla;
    ObjManager::getTextures(infile, texturesVanilla);

    std::ifstream infile2(filepath);
    EdgeQueue     edgesQueue;
    VertexQueue   vertexQueue;
    ObjManager::getVectorsAndEdgesFromObj(infile2, edgesQueue, vertexQueue);

    TextureVector vertexTexture(vertexQueue.size());

    while (!edgesQueue.empty()) {
        int el1 = std::stod(edgesQueue.front()[0].vertex) - 1;
        int el2 = std::stod(edgesQueue.front()[1].vertex) - 1;
        int el3 = std::stod(edgesQueue.front()[2].vertex) - 1;

        int te1 = std::stod(edgesQueue.front()[0].texture);
        int te2 = std::stod(edgesQueue.front()[1].texture);
        int te3 = std::stod(edgesQueue.front()[2].texture);

        vertexTexture[el1] = std::make_pair(texturesVanilla[te1].first, texturesVanilla[te1].second);
        vertexTexture[el2] = std::make_pair(texturesVanilla[te2].first, texturesVanilla[te2].second);
        vertexTexture[el3] = std::make_pair(texturesVanilla[te3].first, texturesVanilla[te3].second);

        edgesQueue.pop();
    }

    return vertexTexture;
}
