#include <fstream>
#include "headers/GraphLoader.h"

using namespace std;

void GraphLoader::loadVertices(const string& filename, Graph<int>* graph) {
    ifstream file(filename);
    if (!file.is_open()) return;

    int nrNodes, id;
    double x, y;
    char c;

    file >> nrNodes;
    for (int i = 0; i < nrNodes; i++) {
        file >> c >> id >> c >> x >> c >> y >> c;

        graph->addVertex(id, x, y);
    }

    file.close();
}

void GraphLoader::loadEdges(const string& filename, Graph<int>* graph, bool isUnidiretional) {
    ifstream file(filename);
    if (!file.is_open()) return;

    int nrEdges, idSource, idTarget;
    char c;

    file >> nrEdges;
    for (int i = 0; i < nrEdges; i++) {
        file >> c >> idSource >> c >> idTarget >> c;

        graph->addEdge(idSource, idTarget);
        if (!isUnidiretional)
            graph->addEdge(idTarget, idSource);

    }

    file.close();
}
