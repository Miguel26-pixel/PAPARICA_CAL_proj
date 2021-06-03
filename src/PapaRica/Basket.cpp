#include "headers/Basket.h"

using namespace std;

Basket::Basket(string nameClient, int nrPackages, Vertex<int>* destiny, long billNumber) {
    this->nameClient = nameClient;
    this->nrPackages = nrPackages;
    this->destiny = destiny;
    this->billNumber = billNumber;
    this->delivered = false;
}

bool Basket::isDelivered() const {
    return delivered;
}

string Basket::getNameClient() const {
    return nameClient;
}

int Basket::getNrPackages() const {
    return nrPackages;
}

Vertex<int>* Basket::getDestiny() const {
    return destiny;
}

void Basket::setDelivered(bool delivered) {
    this->delivered = delivered;
}



