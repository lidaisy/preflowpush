#ifndef _ARC_H_
#define _ARC_H_
#include "node.h"

class Arc{
    public:
    Node* head;
    Node* tail;
    bool isForward;
    int capacity;
    int flow = 0;
    Arc* reverse;

    Arc(Node* h, Node* t, bool forward, int cap = 0);

    bool hasHead(Node* node);

    bool hasTail(Node* node);

};

#endif