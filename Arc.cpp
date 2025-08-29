#include "Arc.h"

Arc::Arc(Node* h, Node* t, bool forward, int cap){
    head = h;
    tail = t;
    isForward = forward;
    capacity = cap;
}

bool Arc::hasHead(Node* node){
    return head->index == node->index;
}

bool Arc::hasTail(Node* node){
    return tail->index == node->index;
}
