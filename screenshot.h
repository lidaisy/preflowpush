#ifndef _SCREENSHOT_H_
#define _SCREENSHOT_H_

#include <vector>
#include "node.h"
#include "arc.h"

class Screenshot{
    public:
    int op;
    std::vector<int> heights;
    std::vector<std::vector<int>> arcInfo;

    Screenshot(std::vector<Node*> nodes, std::vector<Arc*> arcs, int operation);
};

#endif