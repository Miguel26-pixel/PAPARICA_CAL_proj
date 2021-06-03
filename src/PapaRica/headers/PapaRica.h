#ifndef CAL_PROJ_PAPARICA_H
#define CAL_PROJ_PAPARICA_H

#include "../../Utils/headers/Graph.h"
#include "Basket.h"
#include "Vehicle.h"

#include <unordered_map>

class PapaRica {
private:
    Graph<int>* graph;                              // Graph
    std::vector<Basket*> baskets;                   // Baskets: deliveries
    std::vector<Vehicle*> vehicles;                 // Vehicles of the company
    Vertex<int>* company;                           // Vertex of the company
    std::unordered_map<std::string, long> stats;    // Statistic: Execution time of algorithms

public:
    /**
     * Constructor of company PapaRica.
     * @param graph Graph.
     * @param company Company vertex.
     */
    PapaRica(Graph<int>* graph, Vertex<int>* company);
    /**
     * Checks if already exists a delivery in vertex with certain id.
     * @param id Id of the vertex.
     * @return True if exists a delivery in vertex with certain id, false otherwise.
     */
    bool deliverInSameSpot(int id) const;
    /**
     * Gets graph.
     * @return Graph.
     */
    Graph<int>* getGraph() const;
    /**
     * Gets the companies' vehicles.
     * @return Companies' vehicles.
     */
    std::vector<Vehicle*> getVehicles() const;
    /**
     * Gets the companies' baskets.
     * @return Companies' baskets.
     */
    std::vector<Basket*> getBaskets() const;
    /**
     * Gets the companies' vertex id.
     * @return Companies' vertex id.
     */
    int getCompanyVertexId() const;
    /**
     * Gets the companies' statistic.
     * @return Companies' statistic.
     */
    std::unordered_map<std::string, long> getStats() const;
    /**
     * Adds vehicle to the company.
     * @param vehicle New vehicle to add to the company.
     */
    void addVehicle(Vehicle* vehicle);
    /**
     * Adds basket(delivery) to the company.
     * @param basket New basket to deliver.
     */
    void addBasket(Basket* basket);
    /**
     * Generates and adds random deliveries.
     * @param numberBaskets Number of baskets to generate.
     */
    void generateBaskets(int numberBaskets);
    /**
     * Pre-processes the graph.
     * Runs an algorithm to calculate the strong connected components (SCCs) of the vertices, finds out the largest one and
     * puts there the company.
     *
     * Removes all the unapproachable vertices (which do not belong to the SCC of the companies vertex)
     * and the deliveries that cannot be delivered.
     *
     * @return Returns vector of removed vertices' ids.
     */
    std::unordered_set<int> preProcessing();
    /**
     * Finds which vertex has the largest strong connected component (SCC).
     * @param sccs Alls strong connected components.
     * @return Vertex id that has the largest strong connected component (SCC).
     */
    int findBestVertexForCompany(const std::unordered_map<int, int>& sccs);
    /**
     * Gets the pair that has maximum second value of the unordered_map.
     * @param x Unordered_map.
     * @return Pair that has maximum second value of the unordered_map.
     */
    std::pair<int, int> findMaxValuePair(std::unordered_map<int, int> const &x);
    /**
     * Does the distribution of the basket only with a vehicle with unlimited capacity.
     * First Iteration of the problem.
     */
    void planSingleVehicleDistribution();
    /**
     * Does the distribution of the basket with vehicles with limited capacity.
     * Second Iteration of the problem.
     * @return True if the deliveries were all delivered, false otherwise.
     */
    bool planMultipleVehicleDistribution();
};


#endif //CAL_PROJ_PAPARICA_H
