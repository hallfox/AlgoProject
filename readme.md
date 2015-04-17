#ALGORITHMS!

[![Join the chat at https://gitter.im/hallfox/AlgoProject](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/hallfox/AlgoProject?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Ideas:
- Finding communities in a graph
- A* search algorithm and comparison to Dijkstra

#Proposal
Proposal:

We will implement and evaluate the A* shortest paths algorithm. This algorithm finds the shortest path between any two nodes in a graph and can operate faster than Dijkstra's algorithm. This is because A* is built on top of Dijkstra's algorithm with added heuristics.

Because of this we will implement the following:
- Adjacency List Graph (Sparse) (Taylor Foxhall)
- Adjacency Matrix Graph (Dense) (Armond St. Juste)
- Dikjstra's Algorithm for shortest paths (Alexander Strong)
- A* Heuristic function and A* search (all)

We will evaluate A* and how it compares with Dijkstra by measuring the run time to find the shortest path. The parameters we will test with include:
- Dense adj matrix graph
- Sparse adj matrix graph
- Dense adj list graph
- Sparse adj list graph
- Mixed adj matrix graph
- Mixed adj list graph

Additionally as we learn more about the structure of A* we will look for certain optimizations to A* and test to see how the above parameters affect the runtime.
