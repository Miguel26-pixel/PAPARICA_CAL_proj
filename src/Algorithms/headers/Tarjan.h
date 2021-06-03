#ifndef CAL_PROJ_TARJAN_H
#define CAL_PROJ_TARJAN_H

#include "../../Utils/headers/Graph.h"
#include <unordered_map>
#include <stack>


class Tarjan {

private:
    const Graph<int>* graph;                                    // Graph
    int nrIndex;                                                // Auxiliary structures
    std::unordered_map<int, int> sccs;                          // Strong connected components (SCCs)
    std::unordered_map<Vertex<int>*, int> index;                // Auxiliary structures
    std::unordered_map<Vertex<int>*, int> lowlink;              // Auxiliary structures
    std::stack<Vertex<int>*> l;                                 // Auxiliary structures - visited

    /**
     * Depth-first search of the algorithm.
     * @param v Vertex to start from.
     */
    void DFS_TARJAN(Vertex<int>* v);
    /**
     * Checks if vertex is in the stack.
     * @param v Vertex.
     */
    bool isInStack(Vertex<int>* v);
public:
    /**
     * Constructor of Tarjan.
     * @param graph Graph.
     */
    explicit Tarjan(const Graph<int>* graph);
    /**
     * Tarjan's algorithm.
     * @return All strong connected components (SCCs) of the graph.
     */
    std::unordered_map<int, int> run();
};


#endif //CAL_PROJ_TARJAN_H
