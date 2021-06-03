#ifndef CAL_PROJ_GRAPHLOADER_H
#define CAL_PROJ_GRAPHLOADER_H

#include "Graph.h"

class GraphLoader {
public:
    /**
     * Loads vertices from given file into a graph.
     * @param filename File to load vertices from. (With specific format)
     * @param graph Graph to fill with information given by the file.
     */
    static void loadVertices(const std::string& filename, Graph<int>* graph);
    /**
     * Loads edges from given file into a graph.
     * @param filename File to load edges from. (With specific format)
     * @param graph Graph to fill with information given by the file.
     * @param isUnidiretional If the edges are directed ot undirected.
     */
    static void loadEdges(const std::string& filename, Graph<int>* graph, bool isUnidiretional);
};


#endif //CAL_PROJ_GRAPHLOADER_H
