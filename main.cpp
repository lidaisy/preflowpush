// collect head, tail, capacity
// create nodes, arcs here and pass into graph
// don't need forward & allArcs

// create step by step graphs for python to print

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Node.h"
#include "Arc.h"
#include "Graph.h"
#include "Screenshot.cpp"

int main(){
    // Create an input file stream object named 'file' and
    // open the file "GFG.txt".
    std::ifstream file("input.txt");

    // String to store each line of the file.
    std::string line;

    std::vector<Node*> nodes;
    std::vector<Arc*> arcs;

    if (file.is_open()) {
        int s, t;
        file >> s >> t;

        Node* startNode = new Node{s};
        Node* endNode = new Node{t};

        while (getline(file, line)) {
            std::istringstream iss(line);
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
        std::vector<Screenshot*> screenshots = graph->run(false);
        int index = 0;

        for(Screenshot* ss : screenshots){
            std::cout << index << std::endl;
            for(int h : ss->heights){
                std::cout<<h<<",";
            }
            std::cout << std::endl;
            
            for(std::vector<int> arc : ss->arcInfo){
                std::cout<<arc[0]<<","<<arc[1]<<","<<arc[2]<<","<<std::endl;
            }
        }
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        std::cerr << "Unable to open file!" << std::endl;
    }

    return 0;
}
