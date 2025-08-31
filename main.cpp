#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "node.h"
#include "arc.h"
#include "graph.h"
#include "screenshot.h"

int main(){
    std::ifstream file("input.txt");

    std::string line;

    std::vector<Node*> nodes;
    std::vector<Arc*> arcs;

    if (file.is_open()) {
        int s, t;
        getline(file, line);
        std::istringstream ss(line);
        ss >> s >> t;

        Node* startNode = new Node{s};
        Node* endNode = new Node{t};

        nodes.push_back(startNode);
        nodes.push_back(endNode);

        while (getline(file, line)) {
            std::istringstream iss {line};
            int tail, head, capacity;

            if (!(iss >> tail >> head >> capacity)){
                break;
            }
            Node* headNode;
            Node* tailNode;

            bool foundHead = false;
            bool foundTail = false;

            for(Node* node : nodes){
                if(node->index == tail){
                    tailNode = node;
                    foundTail = true;
                }
                if(node->index == head){
                    headNode = node;
                    foundHead = true;
                }
            }
            if(!foundTail){
                tailNode = new Node(tail);
                nodes.push_back(tailNode);
            }
            if(!foundHead){
                headNode = new Node(head);
                nodes.push_back(headNode);
            }
            arcs.push_back(new Arc(headNode, tailNode, true, capacity));
        }
        file.close();

        Graph* graph = new Graph(arcs, nodes, startNode, endNode);
        std::vector<Screenshot*> screenshots = graph->run(true);

        int index = 0;

        std::ofstream file("output.txt");

        // print number of screenshots, number of nodes, and number of arcs
        file << screenshots.size() << " " << nodes.size() << " "<< arcs.size() << std::endl;

        for(Screenshot* ss : screenshots){
            file << ss->op << std::endl;
            for(int h : ss->heights){
                file<<h<<" ";
            }
            file << std::endl;

            for(std::vector<int> arc : ss->arcInfo){
                file<<arc[0]<<" "<<arc[1]<<" "<<arc[2]<<std::endl;
            }
            index++;
        }
        for(Screenshot* s : screenshots){
            delete s;
        }
        delete graph;
    }
    else {
        std::cerr << "Unable to open file!" << std::endl;
    }
    return 0;
}
