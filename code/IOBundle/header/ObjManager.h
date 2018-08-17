#ifndef OBJMANAGER_HH
#define OBJMANAGER_HH

#include <sstream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <queue>

#include "../../Controller/header/DebugController.h"
#include "../../SimulatorBundle/header/EigenUtils.h"

struct Edge {
    std::string vertex;
    int         material;
    std::string texture;
};

typedef std::queue<std::vector<Edge> >          EdgeQueue;
typedef std::queue<std::vector<std::string> >   VertexQueue;
typedef std::vector<std::pair<double, double> > TextureVector;

class ObjManager {
public:
    static Model3D readObj(std::string filepath);
    static TextureVector readTexture(std::string filepath);
private:
    static std::vector<std::string> splitString(const std::string& s, const char token);
    static void getVectorsAndEdgesFromObj(std::ifstream& infile,
                                          EdgeQueue& edgesQueue,
                                          VertexQueue& vertexQueue);
    static Model3D createMoldel(EdgeQueue& edgesQueue, VertexQueue& vertexQueue);
    static void getTextures(std::ifstream& infile, TextureVector& texturesVanilla);
};

#endif // ifndef OBJMANAGER_HH
