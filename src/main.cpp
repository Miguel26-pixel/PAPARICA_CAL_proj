#include "Utils/headers/Graph.h"
#include "Utils/headers/GraphLoader.h"
#include "Utils/headers/GraphDrawer.h"
#include "PapaRica/headers/PapaRica.h"
#include "Utils/headers/Menu.h"

#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {

    srand (time(NULL));

    Graph<int> graph;
    std::cout << "Loading map...\n";
    GraphLoader::loadVertices("../maps/Porto_maps/porto_full_nodes_xy.txt", &graph);
    GraphLoader::loadEdges("../maps/Porto_maps/porto_full_edges.txt", &graph, true);
    /*GraphLoader::loadVertices("../maps/GridGraphs/8x8/nodes.txt", &graph);
    GraphLoader::loadEdges("../maps/GridGraphs/8x8/edges.txt", &graph, false);*/

    Menu menu = Menu(&graph);
    menu.mainMenu();

    return 0;
}