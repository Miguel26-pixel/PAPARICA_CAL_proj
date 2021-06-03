#include "headers/Menu.h"

Menu::Menu(Graph<int>* graph) : drawer(GraphDrawer(1644, 921)),
papaRica(PapaRica(graph, graph->findVertex(1))) {

    std::cout << "Drawing map...\n";
    drawer.drawGraph(graph);
}

bool Menu::check_number(const std::string& str) {
    for (char i : str)
        if (isdigit(i) == false)
            return false;
    return true;
}

void Menu::closeMenu() {
    char input;
    std::cout << " Select the option you want to access: \n";
    std::cout << " [0] Return to main menu\n";
    std::cout << " [1] Exit\n";
    std::cout << " Input: ";
    std::cin >> input;
    std::cout << " \n";
    switch (input - '0') {
        case 0:
            mainMenu();
            break;
        case 1: {
            std::cout << "Close the window of the viewer.\n";
            drawer.join();
            break;
        }
        default: {
            std::cout << " Insert a number in 0-1!!\n";
            closeMenu();
        }
    }
}

void Menu::mainMenu() {
    char input;
    std::cout << " Select the option you want to access: \n";
    std::cout << " [0] Insert basket\n";
    std::cout << " [1] Generate baskets\n";
    std::cout << " [2] Start\n";
    std::cout << " [3] Exit\n";
    std::cout << " Input: ";
    std::cin >> input;
    std::cout << " \n";
    switch (input - '0') {
        case 0:
            addBasket();
            closeMenu();
            break;
        case 1:
            std::cout << "Number of baskets: ";
            int nrBaskets;
            std::cin >> nrBaskets;
            papaRica.generateBaskets(nrBaskets);

            // Color deliveries vertices
            for (auto basket: papaRica.getBaskets()) {
                std::cout << " Added basket with " << basket->getNrPackages() << " packages! \n";
                drawer.colorNode(basket->getDestiny()->getId(), false);
                drawer.addTagNode(basket->getDestiny()->getId(), "NR: " + std::to_string(basket->getNrPackages()));
            }
            closeMenu();
            break;
        case 2:
            start();
            std::cout << "Close the window of the viewer.\n";
            drawer.join();
            break;
        case 3:
            break;
        default: {
            std::cout << " Insert a number in 0-3!!\n";
        }
    }
}

void Menu::start() {
    std::cout << "Preprocessing map...\n\n";
    std::unordered_set<int> removedIds = papaRica.preProcessing();

    // Remove from window viewer all the vertices removed
    // in the preProcessing
    for (int id: removedIds) {
        drawer.removeNode(id);
    }

    // TODO: REMOVE
    for (std::pair<std::string, long> p: papaRica.getStats()) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    // Color company vertex
    drawer.colorNode(papaRica.getCompanyVertexId(), true);
    // Color deliveries vertices
    std::cout << "To deliver(nr packages): ";
    for (auto basket: papaRica.getBaskets()) {
        std::cout << basket->getNrPackages() << "-";
        drawer.colorNode(basket->getDestiny()->getId(), false);
    }
    std::cout << "END\n\n";

    char input;
    std::cout << " Select the option you want to access: \n";
    std::cout << " [1] Vehicle with unlimited capacity\n";
    std::cout << " [2] Set of vehicles with limited capacity\n";
    std::cout << " Input: ";
    std::cin >> input;
    std::cout << " \n";
    switch (input - '0') {
        case 1:
            singleVehicleDistribution();
            break;
        case 2:
            multipleVehicleDistribution();
            break;
        default: {
            std::cout << " Insert a number in 1-2!!\n";
            start();
        }
    }
}

void Menu::singleVehicleDistribution() {
    papaRica.addVehicle(new Vehicle("", INT_MAX));
    std::cout << " Starting distribution \n";
    papaRica.planSingleVehicleDistribution();

    // TODO: REMOVE
    for (std::pair<std::string, long> p: papaRica.getStats()) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
    printPath();
    colorGraph();
}

void Menu::multipleVehicleDistribution() {
    char input;
    std::cout << " Select the option you want to access: \n";
    std::cout << " [1] Add vehicle\n";
    std::cout << " [2] Start distribution\n";
    std::cout << " Input: ";
    std::cin >> input;
    std::cout << " \n";
    switch (input - '0') {
        case 1:
            addVehicle();
            multipleVehicleDistribution();
            break;
        case 2: {
            if (papaRica.planMultipleVehicleDistribution()) {
                printPath();
                std::cout << "Completed every delivery.\n";
            }
            else if (papaRica.getBaskets().empty()){
                std::cout << "No deliveries.\n";
            }
            else if (papaRica.getVehicles().empty()) {
                std::cout << "No vehicles to deliver.\n";
            }
            else {
                printPath();
                std::cout << "Could not complete every delivery.\n";
            }
            colorGraph();
            break;
        }
        default: {
            std::cout << " Insert a number in 1-2!!\n";
            multipleVehicleDistribution();
        }
    }
}

void Menu::addBasket() {
    std::string name, nrPackagesStr, idStr, billNumberStr;
    int nrPackages, id, billNumber;

    std::cout << " Name: ";
    std::cin >> name;
    std::cout << " \n";

    do {
        std::cout << " Number of packages: ";
        std::cin >> nrPackagesStr;
        std::cout << " \n";

        if (!check_number(nrPackagesStr)) std::cout << " Invalid number of packages. Try again! \n";
        else break;

    } while (true);

    nrPackages = std::stoi(nrPackagesStr);

    do {
        std::cout << " Destiny ID: ";
        std::cin >> idStr;
        std::cout << " \n";

        if (!check_number(idStr)) std::cout << " Invalid ID number. Try again! \n"; //Check if destiny exists
        else break;

    } while(true);

    id = std::stoi(idStr);

    do {
        std::cout << " Bill Number: ";
        std::cin >> billNumberStr;
        std::cout << " \n";

        if (!check_number(billNumberStr)) std::cout << " Invalid bill number. Try again! \n";
        else break;

    } while (true);

    billNumber = std::stoi(billNumberStr);

    papaRica.addBasket(new Basket(name, nrPackages, papaRica.getGraph()->findVertex(id), billNumber));
    std::cout << " Added basket for " << name << "! \n";
    drawer.colorNode(id, false);
    drawer.addTagNode(id, "NR: " + std::to_string(nrPackages));
}

void Menu::addVehicle() {

    int capacity;
    std::string type, capacityStr;

    do {
        std::cout << " Type: ";
        std::cin >> type;
        std::cout << " \n";

        if ((type != "car") && (type != "van")) std::cout << " Invalid vehicle type. Try again! \n";
        else break;

    } while (true);

    do {
        std::cout << " Capacity: ";
        std::cin >> capacityStr;
        std::cout << " \n";

        if (!check_number(capacityStr)) std::cout << " Invalid capacity. Try again! \n";
        else break;

    } while(true);

    capacity = std::stoi(capacityStr);

    papaRica.addVehicle(new Vehicle(type, capacity));
    std::cout << " Added vehicle with " << capacity << " capacity! \n";
}

void Menu::colorGraph() {
    std::vector<Vehicle*> vehicles = papaRica.getVehicles();
    std::cout << "\nAbout to color...\n";

    for (int i = 0; i < vehicles.size(); i++) {
        for (auto *e: vehicles[i]->getPath()) {

            if (COLORS.size() >= i) {
                drawer.colorEdge(e->getId(), COLORS[i]);
            }
            else {
                // Generate random colors
                int maxColor = 16776000;    // Not too white
                int minColor = 200;         // Not too dark
                drawer.colorEdge(e->getId(), sf::Color(rand() % (maxColor - minColor + 1 ) + minColor));
            }
        }
    }
    std::cout << "Done\n";
}

void Menu::printPath() {

    for (int i = 0; i < papaRica.getVehicles().size(); i++) {

        if (papaRica.getVehicles().size() == 1) std::cout << " Vehicle1 (capacity: unlimited): ";
        else std::cout << " Vehicle" << i+1 << " (capacity: " << papaRica.getVehicles()[i]->getCapacity() << "): ";

        if (papaRica.getVehicles()[i]->getDeliveries().empty()) {
            std::cout << "No deliveries\n";
            continue;
        }
        else
            std::cout << papaRica.getCompanyVertexId();

        for (auto edge : papaRica.getVehicles()[i]->getPath())
            std::cout << "-" << edge->getDest()->getId();

        std::cout << "-END\n";
        std::cout << "Delivered to: (not in order)\n";
        for (auto delivery : papaRica.getVehicles()[i]->getDeliveries())
            std::cout << "- " << delivery->getNameClient() << " (" << delivery->getNrPackages() << " packages)" << std::endl;
    }
}
