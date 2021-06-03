#ifndef CAL_PROJ_NEARESTNEIGHBOUR_H
#define CAL_PROJ_NEARESTNEIGHBOUR_H


#include <vector>
#include <unordered_map>
#include "../../Utils/headers/Graph.h"
#include "../../PapaRica/headers/Basket.h"
#include "../../PapaRica/headers/Vehicle.h"

class NearestNeighbour {
private:
    const Graph<int>* graph;                         // Graph to be analysed
    std::vector<Basket*> baskets;                    // Baskets to be delivered
    std::vector<Basket*> lastDeliveries;             // Last deliveries
    std::vector<Vertex<int>*> nodes;                 // Nodes to be visited
    std::unordered_map<Vertex<int>*, bool> vertices; // Stores information on whether each vertex was visited or not

    /**
     * Gets the number of packages to be delivered in v
     * @param v Vertex to be analysed
     * @return Number of packages to be delivered in v
     */
    int getDeliveryNrPackages(Vertex<int> *v) const;
    /**
     * Completes the delivery in vertex by vehicle
     * @param vertex Vertex that will have its delivery completed
     * @param vehicle Vehicle that is going to deliver the package in vertex
     */
    void completeDelivery(const Vertex<int>* vertex, Vehicle* vehicle);
public:
    /**
     * Constructor of NearestNeighbour
     * @param graph
     * @param baskets Baskets to be delivered
     */
    NearestNeighbour(const Graph<int> *graph, const std::vector<Basket*>& baskets);
    /**
     * Executes Nearest Neighbour algorithm
     * @param s Source
     * @param vehicle Vehicle
     * @return Path in edges
     */
    std::vector<Edge<int>*> run(Vertex<int> *s, Vehicle* vehicle);
    /**
     * Gets last deliveries from the last vehicle. Last execution of the algorithm.
     * @return Last deliveries from the last vehicle.
     */
    std::vector<Basket*> getLastDeliveries() const;
    /**
     * Finds the nearest vertex of s in nodes
     * @param s Source
     * @param nodes Nodes to be analysed
     * @param vertices Stores information on whether each vertex was visited
     * or not
     * @return Nearest vertex of s in nodes
     */
    static Vertex<int>* findClosest(Vertex<int>* s, const std::vector<Vertex<int>*> &nodes, std::unordered_map<Vertex<int>*, bool> vertices);
};


#endif //CAL_PROJ_NEARESTNEIGHBOUR_H
