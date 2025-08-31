#include <vector>
#include "node.h"
#include "arc.h"
#include "screenshot.h"

Screenshot::Screenshot(std::vector<Node*> nodes, std::vector<Arc*> arcs, int operation){
    op = operation;
    std::vector<int> heights(nodes.size(), 0);

    for(Node* node : nodes){
        heights.at(node->index) = node->height;
    }
    this->heights = heights;

    for(Arc* arc : arcs){
        if(arc->isForward){
            std::vector<int> tmp{ arc->tail->index, arc->head->index, arc->flow};
            arcInfo.push_back(tmp);
        }
    }
}