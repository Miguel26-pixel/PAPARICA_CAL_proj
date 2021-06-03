#ifndef CAL_PROJ_VEHICLE_H
#define CAL_PROJ_VEHICLE_H

#include <string>
#include "../../Utils/headers/Graph.h"
#include "Basket.h"

class Vehicle {
private:
    std::string type;                   // Type of the vehicle
    int cap;                            // Capacity of the vehicle. Maximum number of packages
    int freeSpace;                      // Current free space available in the vehicle
    std::vector<Edge<int>*> path;       // Path of the vehicle
    std::vector<Basket*> deliveries;    // Deliveries that the vehicle is responsible for

public:
    /**
     * Constructor of Vehicle.
     * @param type Type of the vehicle.
     * @param cap Capacity of the vehicle.
     */
    Vehicle(std::string type, int cap);
    /**
     * Gets the capacity of the vehicle.
     * @return Capacity of the vehicle.
     */
    int getCapacity() const;
    /**
     * Gets the space available of the vehicle.
     * @return Current free space available in the vehicle.
     */
    int getFreeSpace() const;
    /**
     * Gets the path of the vehicle.
     * @return Sequence of edges of the path of the vehicle.
     */
    std::vector<Edge<int>*> getPath() const;
    /**
     * Gets the baskets delivered by the vehicle.
     * @return Baskets delivered by the vehicle.
     */
    std::vector<Basket*> getDeliveries() const;
    /**
     * Changes the free space of the vehicle.
     * @param newFreeSpace New free space.
     */
    void setFreeSpace(int newFreeSpace);
    /**
     * Changes the path of the vehicle.
     * @param path New path.
     */
    void setPath(std::vector<Edge<int>*> path);
    /**
     * Changes the deliveries of the vehicle.
     * @param deliveries New deliveries.
     */
    void setDeliveries(std::vector<Basket*> deliveries);
    /**
     * Adds a new delivery to the vehicle's responsibility.
     * @param basket New basket to deliver.
     */
    void addDelivery(Basket* basket);
    /**
     * Checks if a vehicle has more capacity than the other.
     * @param vehicle Vehicle to compare.
     * @return True if the object (this) has more space than the 'vehicle'.
     */
    bool operator<(Vehicle* vehicle) const;
};


#endif //CAL_PROJ_VEHICLE_H
