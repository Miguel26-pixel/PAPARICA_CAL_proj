#ifndef CAL_PROJ_NEARESTNEIGHBOURMULTIPLEVEHICLES_H
#define CAL_PROJ_NEARESTNEIGHBOURMULTIPLEVEHICLES_H

#include <vector>
#include <unordered_map>
#include "../../Utils/headers/Graph.h"
#include "../../PapaRica/headers/Vehicle.h"
#include "../../PapaRica/headers/Basket.h"

class NearestNeighbourMultipleVehicles {
private:
    Graph<int> *graph;                                  // Graph to be analysed
    std::vector<Vehicle*> vehicles;                     // Vehicles to be used on the distribution
    std::vector<Basket*> baskets;                       // Baskets to be delivered
    std::vector<Vertex<int>*> nodes;                    // Nodes to be analysed
    std::unordered_map<Vertex<int>*, bool> vertices;    // Stores information on whether each vertex was visited or not

public:
    /**
     * Constructor of NearestNeighbourMultipleVehicles
     * @param graph Graph that is going to be analysed
     * @param vehicles Vehicles that are eligible to make the distribution
     * @param baskets Baskets to be delivered
     */
    NearestNeighbourMultipleVehicles(Graph<int> *graph, std::vector<Vehicle*> vehicles, const std::vector<Basket*>& baskets);
    /**
     * Assigns the path to multiple vehicles according to the Nearest Neighbour technique
     * @param s Source
     * @return True if the deliveries were all completed, false otherwise
     */
    bool run(Vertex<int> *s);
};

#endif //CAL_PROJ_NEARESTNEIGHBOURMULTIPLEVEHICLES_H
