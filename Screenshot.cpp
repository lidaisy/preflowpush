#include <vector>
#include "Node.h"
#include "Graph.h"
#include "Arc.h"

class Screenshot{
    public:
    std::vector<int> heights;
    std::vector<std::vector<int>> arcInfo;

    Screenshot(std::vector<Node*> nodes, std::vector<Arc*> arcs, int operation){
        std::vector<int> heights(nodes.size(), 0);

        for(Node* node : nodes){
            heights.at(node->index) = node->height;
        }
        for(Arc* arc : arcs){
            if(arc->isForward){
                std::vector<int> tmp{ arc->tail->index, arc->head->index, arc->flow};
                arcInfo.push_back(tmp);
            }
        }
    }
};