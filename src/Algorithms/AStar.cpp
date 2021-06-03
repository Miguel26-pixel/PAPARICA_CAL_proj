#include "headers/AStar.h"
#include <queue>

AStar::AStar(const Graph<int> *graph, int companyId) {
    this->graph = graph;
    this->sccs = graph->getSccs();
    this->companyId = companyId;
}

void AStar::run(Vertex<int> *s, Vertex<int> *dest) {
    auto vertexSet = graph->getVertexSet();
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->setVisited(false);
        (*it)->setDist(INF);
        (*it)->setHDist(INF);
        (*it)->setPath(NULL);
        (*it)->setEdgePath(NULL);
    }

    s->setDist(0.0);
    s->setHDist(s->euclidianDistance(dest->getX(), dest->getY()));

    MutablePriorityQueue<Vertex<int>> q;
    q.insert(s);

    while (!q.empty()) {
        auto current = q.extractMin();
        //if (sccs[current->getId()] != companyId) continue;

        if (current == dest) {
            break;
        }
        current->setVisited(true);

        for (auto& w : current->getAdj()) {
            if (w->getDest()->getVisited()) continue;

            if (w->getDest()->getHDist() == INF) {
                q.insert(w->getDest());
            }
            else {
                if (w->getDest()->getDist() <= current-> getDist() + w->getWeight()) {
                    continue;
                }
            }

            w->getDest()->setPath(current);
            w->getDest()->setEdgePath(w);

            w->getDest()->setDist(current->getDist() + w->getWeight());
            w->getDest()->setHDist(w->getDest()->getDist() + w->getDest()->euclidianDistance(dest->getX(), dest->getY()));

            q.decreaseKey(w->getDest());
        }
    }
}
