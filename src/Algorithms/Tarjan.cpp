#include "headers/Tarjan.h"

using namespace std;

Tarjan::Tarjan(const Graph<int>* graph) {
    this->graph = graph;
    this->sccs.clear();
    this->nrIndex = 1;
}

unordered_map<int, int> Tarjan::run() {
    auto vertexSet = graph->getVertexSet();
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if (index.find(*it) == index.end())
            DFS_TARJAN(*it);
    }

    return sccs;
}

void Tarjan::DFS_TARJAN(Vertex<int>* v) {
    index[v] = nrIndex;
    lowlink[v] = index[v];
    nrIndex++;

    l.push(v);

    for (Edge<int>* e: v->getAdj()) {
        if (index.find(e->getDest()) == index.end()) {
            DFS_TARJAN(e->getDest());
            lowlink[v] = min(lowlink[v], lowlink[e->getDest()]);
        }
        else if (isInStack(e->getDest())) {
            lowlink[v] = min(lowlink[v], index[e->getDest()]);
        }
    }

    if (lowlink[v] == index[v]){
        Vertex<int>* u = l.top();
        l.pop();

        while (u != v){

            sccs[u->getId()] = v->getId();
            u = l.top();
            l.pop();

        }
        sccs[v->getId()] = v->getId();
    }
}

bool Tarjan::isInStack(Vertex<int>* v) {
    stack<Vertex<int>*> temp = l;

    while (!temp.empty()) {
        if (temp.top()->getId() == v->getId())
            return true;
        temp.pop();
    }
    return false;
}
