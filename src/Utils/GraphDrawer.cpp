#include "headers/GraphDrawer.h"

using namespace std;

GraphDrawer::GraphDrawer(int width, int height) {
    this->width = width;
    this->height = height;
    this->gv = new GraphViewer();
}

void GraphDrawer::reset() {

    for (auto v: gv->getNodes()) {
        gv->removeNode(v->getId());
    }
    for (auto e: gv->getEdges()) {
        gv->removeEdge(e->getId());
    }
}

void GraphDrawer::drawGraph(Graph<int>* graph) const {

    for (Vertex<int>* v : graph->getVertexSet()) {
        GraphViewer::Node &node = gv->addNode(v->getId(), sf::Vector2f(v->getX(), v->getY()));
        node.setColor(GraphViewer::LIGHT_GRAY);
        node.setLabelSize(8);
    }

    for (Vertex<int>* v : graph->getVertexSet()) {
        for (Edge<int>* e: v->getAdj()) {
                gv->addEdge(e->getId(), gv->getNode(v->getId()), gv->getNode(e->getDest()->getId()),
                            GraphViewer::Edge::DIRECTED);
        }
    }
    gv->createWindow(width, height);
}

void GraphDrawer::colorEdge(int id, sf::Color color) const {
    GraphViewer::Edge &edge = gv->getEdge(id);
    gv->lock();
    edge.setColor(sf::Color(color));
    gv->unlock();
}

void GraphDrawer::colorNode(int id, bool isCompany) const {
    GraphViewer::Node &node = gv->getNode(id);
    gv->lock();

    if (isCompany) {
        node.setSize(45.0);
        node.setColor(GraphViewer::RED);
        node.setLabel("PapaRica");
    }
    else {
        if (node.getColor() == GraphViewer::BLUE) {
            node.setColor(GraphViewer::GREEN);
        }
        else {  // If node is not reachable
            node.setSize(40.0);
            node.setColor(GraphViewer::BLUE);
        }
    }
    gv->unlock();
}

void GraphDrawer::addTagNode(int id, const std::string& tag) const {
    GraphViewer::Node &node = gv->getNode(id);
    gv->lock();
    node.setLabel(tag);
    gv->getNode(id).setLabelColor(GraphViewer::BLUE);
    gv->unlock();
}

void GraphDrawer::removeNode(int id) const {
    gv->removeNode(id);
}

void GraphDrawer::join() {
    gv->join();
}