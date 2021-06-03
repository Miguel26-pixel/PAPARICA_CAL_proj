#ifndef CAL_PROJ_ASTAR_H
#define CAL_PROJ_ASTAR_H

#include <vector>
#include "../../Utils/headers/Graph.h"

class AStar {
private:
    const Graph<int>* graph;        // Graph
    std::unordered_map<int, int> sccs;
    int companyId;
public:
    /**
     * Constructor of AStar.
     * @param graph Graph.
     */
    explicit AStar(const Graph<int> *graph, int companyId);
    /**
     * A-Star's algorithm.
     * Calculates the shortest path from s to dest using the euclidean distance.
     *
     * @param s Starting vertex
     * @param dest Destiny vertex.
     */
    void run(Vertex<int> *s, Vertex<int> *dest);
};


#endif //CAL_PROJ_ASTAR_H
