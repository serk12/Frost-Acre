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

typedef std::queue<std::vector<std::pair<std::string, std::string> > > EdgeQueue;
typedef std::queue<std::vector<std::string> >                          VertexQueue;

class ObjManager {
public:
    static Model3D readObj(std::string filepath);

private:
    static std::vector<std::string> splitString(const std::string& s, const char token);
    static void getVectorsAndEdgesFromObj(std::ifstream& infile,
                                          EdgeQueue& edgesQueue,
                                          VertexQueue& vertexQueue);
    static Model3D createMoldel(EdgeQueue& edgesQueue, VertexQueue& vertexQueue);
};

#endif // ifndef OBJMANAGER_HH
