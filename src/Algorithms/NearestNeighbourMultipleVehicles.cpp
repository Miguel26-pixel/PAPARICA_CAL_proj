#include "headers/NearestNeighbourMultipleVehicles.h"
#include "headers/NearestNeighbour.h"
#include "headers/AStar.h"

using namespace std;

NearestNeighbourMultipleVehicles:: NearestNeighbourMultipleVehicles(Graph<int> *graph, vector<Vehicle*> vehicles,
                                                                    const vector<Basket*>& baskets) {
    this->graph = graph;
    this->vehicles = vehicles;
    this->baskets = baskets;

    for (auto* basket: baskets) {
        nodes.push_back(basket->getDestiny());
        vertices[basket->getDestiny()] = false;
    }
}

bool NearestNeighbourMultipleVehicles::run(Vertex<int> *s) {
    // Sorts vehicles on descending capacity order
    // Vehicle with highest capacity will deliver first
    // More delivers will occur (first) and this will reduce the number of vehicles needed
    sort(vehicles.begin(), vehicles.end(), [] (Vehicle* v1, Vehicle* v2){
        return v1->getCapacity() > v2->getCapacity();
    });
    bool complete;

    NearestNeighbour NN = NearestNeighbour(graph, baskets);

    for (Vehicle* vehicle: vehicles) {
        std::vector<Edge<int> *> edgesPath = NN.run(s, vehicle);
        vehicle->setDeliveries(NN.getLastDeliveries());

        vehicle->setPath(edgesPath);

        complete = true;
        for (Basket* basket: baskets) {
            if (!basket->isDelivered())
                complete = false;
        }

        if (complete) break;
    }

    return complete;
}
