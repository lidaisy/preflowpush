# In progress: check networkx syntax

import sys
import networkx

input = sys.stdin.read().strip().split('\n')

num_steps, num_nodes, num_arcs = map(int, input[0].strip().split())

step_counter = 0
line = 1

graphs = []
operations = []
nodes = range(num_nodes)

while step_counter < num_steps:
    graph = networkx.graph()

    operations.append(int(input[line]))
    heights = map(int, input[line + 1].strip().split())

    for i in range(num_nodes):
        graph.add_node(i, heights[i])

    arc_counter = 0

    for inp in input[line + 2:line + num_arcs]:
        tail, head, flow = map(int, input[line + 1].strip().split())
        graph.add_edge(tail, head, flow)
    step_counter+=1
    line += 2 + num_arcs
    graphs.append[graph]

for graph in graphs:
    pass