#include "headers/NearestNeighbour.h"
#include "headers/AStar.h"

NearestNeighbour::NearestNeighbour(const Graph<int> *graph, const std::vector<Basket*>& baskets) {
    this->graph = graph;
    this->baskets = baskets;

    for (auto* basket: baskets) {
        nodes.push_back(basket->getDestiny());
        vertices[basket->getDestiny()] = false;
    }
}

std::vector<Edge<int> *> NearestNeighbour::run(Vertex<int> *s, Vehicle* vehicle) {
    this->lastDeliveries.clear();
    std::vector<Edge<int> *> pathEdges;
    pathEdges.clear();
    vertices[s] = true;

    Vertex<int>* current = s;
    for (int i = 0; i < nodes.size(); i++) {

        Vertex<int>* closest = findClosest(current, nodes, vertices);

        if (closest == NULL) break;

        if (vehicle->getFreeSpace() != INT_MAX) {
            if (getDeliveryNrPackages(closest) > vehicle->getFreeSpace()) {
                break; // If vehicle runs out of space
            }
        }

        vertices[closest] = true;

        // Find path from 'current' to 'closest' with A* algorithm
        AStar(graph, s->getId()).run(current, closest);
        std::vector<Edge<int>*> edges = graph->getPathEdges(current->getId(), closest->getId());
        pathEdges.insert(pathEdges.end(), edges.begin(), edges.end());

        completeDelivery(closest, vehicle);

        if (vehicle->getFreeSpace() != INT_MAX) {
            vehicle->setFreeSpace(vehicle->getFreeSpace() - getDeliveryNrPackages(closest));
        }

        current = closest;
    }

    AStar(graph, s->getId()).run(current, s);
    std::vector<Edge<int>*> edges = graph->getPathEdges(current->getId(), s->getId());
    pathEdges.insert(pathEdges.end(), edges.begin(), edges.end());

    lastDeliveries = vehicle->getDeliveries();
    return pathEdges;
}

int NearestNeighbour::getDeliveryNrPackages(Vertex<int> *v) const {
    for (Basket *basket : baskets) {
        if (basket->getDestiny()->getId() == v->getId()) {
            return basket->getNrPackages();
        }
    }
    return 0;
}

void NearestNeighbour::completeDelivery(const Vertex<int>* vertex, Vehicle* vehicle) {
    for (auto & basket : baskets) {
        if (basket->getDestiny() == vertex) {
            basket->setDelivered(true);
            vehicle->addDelivery(basket);

            return;
        }
    }
}

std::vector<Basket*> NearestNeighbour::getLastDeliveries() const {
    return lastDeliveries;
}

Vertex<int>* NearestNeighbour::findClosest(Vertex<int>* s, const std::vector<Vertex<int>*> &nodes,
                                           std::unordered_map<Vertex<int>*, bool> vertices) {

    double minDist = INF;
    Vertex<int> *nearest = NULL;

    for (auto vertex : nodes) {

        if (!vertices[vertex]) {

            double distance = s->euclidianDistance(vertex->getX(), vertex->getY());

            if (distance < minDist) {
                minDist = distance;
                nearest = vertex;
            }
        }
    }

    return nearest;
}
