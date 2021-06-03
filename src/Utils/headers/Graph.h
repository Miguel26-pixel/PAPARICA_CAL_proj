/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T id;						    // Content of the vertex
    double x, y;
    std::vector<Edge<T>*> adj;		// Outgoing edges

    double dist = 0;
    double hdist = 0;
    Vertex<T> *path = NULL;
    Edge<T> *edgePath = NULL;
    int queueIndex = 0; 		    // Required by MutablePriorityQueue

    bool visited = false;		    // Auxiliary field
    bool processing = false;	    // Auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    Vertex(T in, double x, double y);
    T getId() const;
    double getDist() const;
    void setDist(double dist);
    double getHDist() const;
    void setHDist(double hdist);
    Vertex *getPath() const;
    void setPath(Vertex<T> *v);
    void setEdgePath(Edge<T>* e);
    std::vector<Edge<T>*> getAdj() const;
    bool getVisited() const;
    void setVisited(bool value);

    bool operator==(const Vertex* v);

    bool removeEdgeTo(Vertex<T> *d);

    int getX() const;
    int getY() const;

    double euclidianDistance(const double x, const double y);

    bool operator<(Vertex<T> & vertex) const; // Required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): id(in) {}

template <class T>
Vertex<T>::Vertex(T in, double x, double y): id(in), x(x), y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(new Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getId() const {
    return this->id;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
void Vertex<T>::setDist(double dist){
    this->dist = dist;
}

template <class T>
double Vertex<T>::getHDist() const {
    return this->hdist;
}

template <class T>
void Vertex<T>::setHDist(double hdist){
    this->hdist = hdist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
void Vertex<T>::setPath(Vertex<T> *v) {
    this->path = v;
}

template <class T>
void Vertex<T>::setEdgePath(Edge<T>* e) {
    this->edgePath = e;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
};

template <class T>
bool Vertex<T>::getVisited() const{
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool value) {
    this->visited  = value;
}
template <class T>
bool Vertex<T>::operator==(const Vertex* v) {
    return id == v->getId();
}

template <class T>
int Vertex<T>::getX() const {
    return this->x;
}

template <class T>
int Vertex<T>::getY() const {
    return this->y;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {

    for (auto it = adj.begin(); it != adj.end(); it++) {
        if ((*it)->dest == d) {
            adj.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
double Vertex<T>::euclidianDistance(const double x, const double y) {
    return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    static int idCounter;
    int id;
    Vertex<T>* dest;      // Destination vertex
    double weight;        // Edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
    int getId() const;
    double getWeight() const;
    Vertex<T>* getDest() const;
};

template <class T>
int Edge<T>::idCounter = 0;
template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {
    this->id = idCounter;
    idCounter++;
}

template <class T>
int Edge<T>::getId() const {
    return this->id;
}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
    return this->dest;
}

/*************************** Graph  **************************/
template <class T>
struct vertexHash {
    bool operator()(const Vertex<T> *v1, const Vertex<T> *v2) const {
        return v1->getId() == v2->getId();
    }
    int operator()(const Vertex<T> *v) const {
        return v->getId();
    }
};

template <class T>
class Graph {
    std::unordered_set<Vertex<T> *, vertexHash<T>, vertexHash<T>> vertexSet;    // Vertex set
    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
    std::unordered_map<int, int> sccs;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addVertex(const T &in, double x, double y);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool addEdge(const T &sourc, const T &dest);
    void setSccs(std::unordered_map<int, int> sccs);
    std::unordered_map<int, int> getSccs() const ;
    bool removeVertex(const T &in);
    int getNumVertex() const;
    std::unordered_set<Vertex<T>*, vertexHash<T>, vertexHash<T>> getVertexSet() const;

    std::vector<T> dfs() const;

    void dijkstraShortestPath(const T &s);
    std::vector<T> getPath(const T &origin, const T &dest) const;
    std::vector<Edge<T>*> getPathEdges(const T &origin, const T &dest) const;

    Graph<T> getTransposed() const;
};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::unordered_set<Vertex<T> *, vertexHash<T>, vertexHash<T>> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    auto it = vertexSet.find(new Vertex<int>(in, 0, 0));
    if (it != vertexSet.end()) {
        return *(it);
    }
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.insert(new Vertex<T>(in));
    return true;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this) and its location (x and y).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, double x, double y) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.insert(new Vertex<T>(in, x, y));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;

    v1->addEdge(v2, v1->euclidianDistance(v2->getX(), v2->getY()));
    return true;
}

template <class T>
void Graph<T>::setSccs(std::unordered_map<int, int> sccs) {
    this->sccs = sccs;
}

template <class T>
std::unordered_map<int, int> Graph<T>::getSccs() const {
    return sccs;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T>* v = findVertex(in);
    if (v == NULL)
        return false;

    for (auto vert: vertexSet) {
        vert->removeEdgeTo(v);
    }
    vertexSet.erase(v);

    return true;
}
/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->visited = false;
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if (!(*it)->visited) {
            dfsVisit(*it, res);
        }
    }

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto it = v->adj.begin(); it != v->adj.end(); it++) {
        if (!(*it).dest->visited)
            dfsVisit(it->dest, res);
    }
}

/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = INF;
        (*it)->path = NULL;
    }

    Vertex<T> *orig = findVertex(origin);

    if (orig == NULL)
        return;

    orig->dist = 0;
    orig->queueIndex = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(orig);

    while(!q.empty()) {
        Vertex<T>* v = q.extractMin();

        if (sccs[v->getId()] != origin) continue;
        for (auto e: v->adj) {
            if (e->dest->dist > v->dist + e->weight) {
                double old_dist = e->dest->dist;

                e->dest->dist = v->dist + e->weight;
                e->dest->path = v;

                if (old_dist == INF) {
                    q.insert(e->dest);
                }
                else {
                    q.decreaseKey(e->dest);
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    Vertex<T> * s = findVertex(origin);
    Vertex<T> * v = findVertex(dest);

    if (v == NULL || s == NULL || v->dist == INF)
        return res;

    while (v != NULL) {
        res.push_back(v->id);
        v = v->path;
    }

    std::reverse(res.begin(), res.end());

    return res;
}


template<class T>
std::vector<Edge<T>*> Graph<T>::getPathEdges(const T &origin, const T &dest) const {

    std::vector<Edge<T>*> res;
    Vertex<T> * s = findVertex(origin);
    Vertex<T> * v = findVertex(dest);

    if (v == NULL || s == NULL || v->dist == INF)
        return res;

    while (v != s) {
        res.push_back(v->edgePath);
        v = v->path;
    }

    std::reverse(res.begin(), res.end());

    return res;
}

/**
 * Gets the transposed graph.
 * @return Transposed graph.
 */
template<class T>
Graph<T> Graph<T>::getTransposed() const {
    Graph<T> transposedGraph;

    for (Vertex<T> *v : vertexSet) {
        transposedGraph.addVertex(v->id, v->getX(), v->getY());
    }

    for (Vertex<T> *v : vertexSet) {
        for (Edge<T>* e: v->adj) {
            transposedGraph.addEdge(e->getDest()->id, v->id, e->weight);
        }
    }

    return transposedGraph;
}

#endif /* GRAPH_H_ */
