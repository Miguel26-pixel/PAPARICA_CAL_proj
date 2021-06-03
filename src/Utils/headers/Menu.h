#ifndef CAL_PROJ_MENU_H
#define CAL_PROJ_MENU_H

#include "../../PapaRica/headers/PapaRica.h"
#include "GraphDrawer.h"
#include <unistd.h>

class Menu {

private:
    PapaRica papaRica;      // Company
    GraphDrawer drawer;     // Graph drawer
    std::vector<sf::Color> COLORS = {GraphViewer::CYAN, GraphViewer::ORANGE, GraphViewer::GREEN, GraphViewer::YELLOW,
                                     GraphViewer::MAGENTA, GraphViewer::PINK, GraphViewer::BLUE, GraphViewer::RED};
    /**
     * Checks if the string is an integer
     * @param str String to be analysed
     * @return True if str is an integer, false otherwise
     */
    static bool check_number(const std::string& str);

    /**
     * Pre-processes the graph and redraws it. Displays a menu on the console,
     * executes starts the distribution according to the users choice (vehicle
     * with unlimited capacity or set of vehicles with limited capacity)
     */
    void start();
    /**
     * Executes the single vehicle distribution
     */
    void singleVehicleDistribution();
    /**
     * Displays a menu on the console and executes tasks according to the
     * users input (add a vehicle or executes the multiple vehicle distribution)
     */
    void multipleVehicleDistribution();
    /**
     * Colors the graph according to the distribution made
     */
    void colorGraph();
    /**
     * Adds a basket to the company according to users input (name, nr packages,
     * destiny and bill number)
     */
    void addBasket();
    /**
     * Displays a menu on the console and executes tasks according to the
     * users input (return to mainMenu or terminate program)
     */
    void closeMenu();
    /**
     * Adds a vehicle to the company according to users input (type and capacity)
     */
    void addVehicle();
    /**
    * Prints the path of each vehicle
    */
    void printPath();
public:
    /**
     * Creates a Menu, initializing papaRica with graph and creating a graphDrawer
     * @param graph Graph to be used by the company
     */
    explicit Menu(Graph<int>* graph);
    /**
     * Displays the main menu on the console, executes tasks according to the
     * users input (add a basket or start distribution) and draws the graph
     */
    void mainMenu();
};


#endif //CAL_PROJ_MENU_H
