#ifndef CAL_PROJ_GRAPHDRAWER_H
#define CAL_PROJ_GRAPHDRAWER_H

#include "Graph.h"
#include "graphviewer.h"

class GraphDrawer {
private:
    int width;          // Window width
    int height;         // Window height
    GraphViewer* gv;    // GraphViewer
public:
    /**
     * Constructor of GraphDrawer.
     * @param width Window width.
     * @param height Window height.
     */
    GraphDrawer(int width, int height);
    /**
     * Resets data from GraphViewer.
     * Removes nodes and edges.
     */
    void reset();
    /**
     * GraphViewer join.
     */
    void join();
    /**
     * Draws graph.
     * @param graph Graph.
     */
    void drawGraph(Graph<int>* graph) const;
    /**
     * Colors edges with given id.
     * @param id Id of edge to color.
     * @param color Color.
     */
    void colorEdge(int id, sf::Color color) const;
    /**
     * Colors node with given id.
     * @param id Id of node to color.
     * @param isCompany True if is it to color company node, false otherwise.
     */
    void colorNode(int id, bool isCompany) const;
    /**
     * Adds tag to node with given id.
     * @param id Id of node to color.
     * @param tag Tag to add to the node.
     */
    void addTagNode(int id, const std::string& tag) const;
    /**
     * Removes node with given id.
     * @param id Id of node to remove.
     */
    void removeNode(int id) const;
};


#endif //CAL_PROJ_GRAPHDRAWER_H
