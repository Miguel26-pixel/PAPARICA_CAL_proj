#include "headers/PapaRica.h"
#include "../Algorithms/headers/Tarjan.h"
#include "../Algorithms/headers/Kosaraju.h"
#include "../Algorithms/headers/AStar.h"
#include "../Algorithms/headers/NearestNeighbour.h"
#include "../Algorithms/headers/NearestNeighbourMultipleVehicles.h"
#include "../Utils/headers/Timing.h"

#include <cstdlib>

using namespace std;

PapaRica::PapaRica(Graph<int>* graph, Vertex<int>* company) {
    this->graph = graph;
    this->company = company;
}

Graph<int>* PapaRica::getGraph() const {
    return graph;
}

std::vector<Vehicle*> PapaRica::getVehicles() const {
    return vehicles;
}

std::vector<Basket*> PapaRica::getBaskets() const {
    return baskets;
}

int PapaRica::getCompanyVertexId() const {
    return company->getId();
}

std::unordered_map<std::string, long> PapaRica::getStats() const {
    return stats;
}

void PapaRica::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void PapaRica::addBasket(Basket* basket) {
    baskets.push_back(basket);
}

bool PapaRica::deliverInSameSpot(int id) const {
    for (Basket* basket: baskets) {
        if (basket->getDestiny()->getId() == id)
            return true;
    }
    return false;
}

void PapaRica::generateBaskets(int numberBaskets) {
    auto vertexSet = graph->getVertexSet();
    auto it = vertexSet.begin();

    for (int i = 0; i < numberBaskets; i++) {
        long randomBillNumber = rand() % 1000;
        int randomVertex;

        do {
            randomVertex = rand() % (vertexSet.size()-1);
        } while (deliverInSameSpot(randomVertex));

        std::advance(it, randomVertex);
        Basket *basket = new Basket("Client" + std::to_string(i), rand() % 7 + 3,
                                    *(it), randomBillNumber);
        addBasket(basket);
        it = vertexSet.begin();
    }
}

std::unordered_set<int> PapaRica::preProcessing() {
    initTime();
    unordered_map<int, int> sccs = Tarjan(graph).run();
    stats["scc"] = calculatePerformance();

    std::unordered_set<int> removedIds;

    // Select vertex which gives the largest scc
    int companyId = findBestVertexForCompany(sccs);
    company = graph->findVertex(companyId);
    graph->setSccs(sccs);

    for (int i = 0; i < baskets.size(); i++) {
        // Discard all deliveries that the destiny do not belong to the graph
        if (sccs[baskets[i]->getDestiny()->getId()] != companyId) {
            baskets.erase(baskets.begin() + i);
            i--;
        }
    }

    graph->dijkstraShortestPath(company->getId());
    return removedIds;
}

int PapaRica::findBestVertexForCompany(const unordered_map<int, int>& sccs) {
    unordered_map<int, int> counter;

    for (pair<int, int> element : sccs) {
        if (counter.find(element.second) == counter.end())
            counter[element.second] = 1;
        else
            counter[element.second]++;

    }

    return PapaRica::findMaxValuePair(counter).first;
}

std::pair<int, int> PapaRica::findMaxValuePair(unordered_map<int, int> const &x) {
    return *std::max_element(x.begin(), x.end(),
                             [](const std::pair<int, int> &p1,
                                const std::pair<int, int> &p2) { return p1.second < p2.second; });
}

void PapaRica::planSingleVehicleDistribution() {
    initTime();
    NearestNeighbour NN = NearestNeighbour(graph, baskets);
    vector<Edge<int>*> path = NN.run(company, vehicles[0]);
    stats["NN"] = calculatePerformance();

    vehicles[0]->setDeliveries(NN.getLastDeliveries());
    vehicles[0]->setPath(path);
}

bool PapaRica::planMultipleVehicleDistribution() {
    return NearestNeighbourMultipleVehicles(graph, vehicles, baskets).run(company);
}
