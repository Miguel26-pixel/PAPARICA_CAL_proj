#ifndef CAL_PROJ_KOSARAJU_H
#define CAL_PROJ_KOSARAJU_H

#include <unordered_set>
#include <stack>
#include "../../Utils/headers/Graph.h"
#include <unordered_map>

class Kosaraju {
private:
    const Graph<int>* graph;                                // Graph
    std::unordered_map<int, int> sccs;    // Strong connected components (SCCs)
    std::unordered_set<Vertex<int>*> s;                     // Auxiliary structures
    std::stack<Vertex<int>*> l;                             // Auxiliary structures
    Graph<int> g_transposed;                                // Transposed graph

    /**
     * Depth-first search of the algorithm.
     * @param v Vertex to start from.
     */
    void DFS_KOSARAJU(Vertex<int>* v);

    /**
     * Assigns the scc to the vertex.
     * @param v Vertex that is going to be assigned a scc.
     * @param root Root of the scc of the vertex.
     */
    void assign(Vertex<int>* v, Vertex<int>* root);
public:
    /**
     * Constructor of Kosaraju.
     * @param graph Graph.
     */
    explicit Kosaraju(const Graph<int> *graph);
    /**
     * Kosaraju's algorithm.
     * @return All strong connected components (SCCs) of the graph.
     */
    std::unordered_map<int, int> run();

};


#endif //CAL_PROJ_KOSARAJU_H
