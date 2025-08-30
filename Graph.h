#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Arc.h"
#include <vector>
#include <map>

class Graph{
    Node* start;
    Node* tail;
    std::vector<Node*> nodes;
    std::vector<Arc*> arcs;
    std::map<Arc*, bool> residualArcs;

    void initialize();

    void push(Arc* arc, bool init = false);

    public:

    Graph(std::vector<Arc*> arcs, std::vector<Node*> nodes, Node* s, Node* t);

    std::vector<Screenshot*> run(bool trackSteps = false);

    ~Graph();
};

#endif