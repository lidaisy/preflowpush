#include <vector>
#include <map>
#include "Node.h"
#include "Graph.h"
#include "Arc.h"
#include "Screenshot.cpp"

Graph::Graph(std::vector<Arc*> arcs, std::vector<Node*> nodes, Node* s, Node* t){
    start = s;
    tail = t;

    for(Arc* arc : arcs){
        this->arcs.push_back(arc);
        this->residualArcs[arc] = true;
        Arc* reverseArc = new Arc(arc->tail, arc->head, false);
        this->arcs.push_back(reverseArc);
        this->residualArcs[reverseArc] = false;

        arc->reverse = reverseArc;
        reverseArc->reverse = arc;
    }
}

void Graph::initialize(){
    start->height = nodes.size();

    for(Arc* arc : arcs){
        if(arc->isForward && arc->hasTail(start)){
            push(arc, arc->capacity);
        }
    }
}

void Graph::push(Arc* arc, bool init){
    // this is wrong. backward arcs never have flow. always update forward arcs
    int amount = init ? arc->capacity : (arc->isForward ? std::min(arc->tail->excess, arc->capacity - arc->flow) : std::min(arc->tail->excess, arc->reverse->flow));

    arc->head->excess += amount;
    arc->tail->excess -= amount;

    if(arc->isForward){ // arc->flow must be > 0 since amount > 0
        arc->flow += amount;

        if(arc->flow == arc->capacity){
            residualArcs[arc] = false;
        }
        if(residualArcs[arc->reverse] == false){
            residualArcs[arc->reverse] == true;
        }
    }
    else{ // arc->flow must be < capacity since amount > 0
        arc->reverse->flow -= amount;

        if(arc->reverse->flow == 0){
            residualArcs[arc] = false;
        }
        if(residualArcs[arc->reverse] == false){
            residualArcs[arc->reverse] == true;
        }
    }
}

std::vector<Screenshot*> Graph::run(bool trackSteps){
    std::vector<Screenshot*> ss;

    initialize();

    bool updated = true;

    while(updated){
        updated = false;

        for(Node* node : nodes){
            while(node->index != tail->index && node->excess > 0){
                bool shouldRelabel = true;
                int h_tail = node->height;
                std::vector<Arc*> outArcs = {};
                
                for(Arc* arc : arcs){
                    if(residualArcs[arc] && arc->hasTail(node)){
                        int h_head = arc->head->height;

                        if(h_head == h_tail - 1){
                            push(arc);
                            shouldRelabel = false;

                            if(trackSteps){
                                ss.push_back(new Screenshot{nodes, arcs, 1});
                            }
                            break;
                        }
                        else{
                            outArcs.push_back(arc);
                        }
                    }
                }
                if(shouldRelabel){
                    Arc* minArc;
                    int minHeight = INT_MAX;

                    for(Arc* arc : outArcs){
                        int amt = arc->head->height;

                        if(amt < minHeight){
                            minHeight = amt;
                            minArc = arc;
                        }
                    }
                    node->height = minHeight + 1;

                    if(trackSteps){
                        ss.push_back(new Screenshot{nodes, arcs, 0});
                    }
                    push(minArc);

                    if(trackSteps){
                        ss.push_back(new Screenshot{nodes, arcs, 1});
                    }
                }
                updated = true;
            }
        }
    }
    if(!trackSteps){
        ss.push_back(new Screenshot{nodes, arcs, 2});
    }
    return ss;
}
