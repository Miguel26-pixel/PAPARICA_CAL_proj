#include "headers/Vehicle.h"

using namespace std;

Vehicle::Vehicle(string type, int cap) {
    this->type = type;
    this->cap = cap;
    this->freeSpace = cap;

    this->deliveries.clear();
    this->path.clear();
}

int Vehicle::getCapacity() const {
    return cap;
}

int Vehicle::getFreeSpace() const {
    return freeSpace;
}

vector<Edge<int>*> Vehicle::getPath() const {
    return path;
}

vector<Basket*> Vehicle::getDeliveries() const {
    return deliveries;
}

void Vehicle::setFreeSpace(int newFreeSpace) {
    this->freeSpace = newFreeSpace;
}

void Vehicle::setPath(std::vector<Edge<int>*> path) {
    this->path = path;
}

void Vehicle::setDeliveries(std::vector<Basket*> deliveries) {
    this->deliveries = deliveries;
}

void Vehicle::addDelivery(Basket* basket) {
    deliveries.push_back(basket);
}

bool Vehicle::operator<(Vehicle* vehicle) const {
    return cap < vehicle->cap;
}
