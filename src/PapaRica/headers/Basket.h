#ifndef CAL_PROJ_BASKET_H
#define CAL_PROJ_BASKET_H

#include "../../Utils/headers/Graph.h"

class Basket {
private:
    std::string nameClient;     // Name of the client
    int nrPackages;             // Number of packages asked for the delivery
    Vertex<int>* destiny;       // Place to deliver to
    long billNumber;            // Bill number
    bool delivered;             // If the basket was delivered

public:
    /**
     * Constructor of Basket.
     * @param nameClient Name of the client.
     * @param nrPackages Number of packages asked for the delivery.
     * @param destiny Place to deliver to.
     * @param billNumber Bill number.
     */
    Basket(std::string nameClient, int nrPackages, Vertex<int>* destiny, long billNumber);
    /**
     * Checks if the basket was delivered.
     * @return True if the basket was delivered, false otherwise.
     */
    bool isDelivered() const;
    /**
     * Gets the name of client who requested the basket.
     * @return Name of client who requested the basket.
     */
    std::string getNameClient() const;
    /**
     * Gets the number of packages of the basket.
     * @return Number of packages of the basket.
     */
    int getNrPackages() const;
    /**
     * Gets the destiny of the delivery.
     * @return Destiny of the delivery.
     */
    Vertex<int>* getDestiny() const;
    /**
     * Changes the value of delivered.
     * @param delivered If the basket was delivered.
     */
    void setDelivered(bool delivered);
};


#endif //CAL_PROJ_BASKET_H
