#include "headers/Kosaraju.h"
using namespace std;

Kosaraju::Kosaraju(const Graph<int> *graph) {
    this->graph = graph;
    this->sccs.clear();
    this->s.clear();
    this->g_transposed = graph->getTransposed();
}

unordered_map<int, int> Kosaraju::run() {
    auto vertexSet = graph->getVertexSet();
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        DFS_KOSARAJU(*it);
    }

    while (!l.empty()) {
        Vertex<int> *v = l.top();
        assign(v, v);
        l.pop();
    }

    return sccs;
}

void Kosaraju::DFS_KOSARAJU(Vertex<int>* v) {
    if (s.find(v) != s.end()) return;
    s.insert(v);

    for (Edge<int>* e: v->getAdj()) {
        DFS_KOSARAJU(e->getDest());
    }
    l.push(v);
}

void Kosaraju::assign(Vertex<int>* u, Vertex<int>* root) {
    if (sccs.find(u->getId()) != sccs.end()) return;

    sccs[u->getId()] = root->getId();

    Vertex<int>* u_in_transposed = g_transposed.findVertex(u->getId());

    for (Edge<int>* e: u_in_transposed->getAdj()) {
        assign(graph->findVertex(e->getDest()->getId()), root);
    }
}
