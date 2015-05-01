//Put any include statements here
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

//This class will be used to create a graph library.
struct Edge{
int vect1;
int vect2;
double weight;
	Edge(int v1, int v2, double w){
		vect1 = v1;
		vect2 = v2;
		weight = w;
	}
};

//This class will be used to create a graph library.   
enum Type {DIRECTED,UNDIRECTED};
enum Status{NOT_VISITED,VISITED};

class Graph{
	private:
		//Put your private data members here
		int numVertices;
		int numEdges;
		std::vector<int> vertices;
		std::vector<Edge> edges;
		double **adjMatrix; //2d array of bools
		Type direction;
		//Put your private methods here
        void followComponent(int v, std::vector<int> &accountedVertices);
        void DFTHelper(int source , Status * visited, std::queue<int> &traverseNodes);
		int searchVector(std::vector<int> vec, int value);
        void prim(int source, std::ofstream& file, Status visited[]);
	public:
		//Construct
		Graph();
		//Delete
		~Graph();
		//Read A Graph From A File
		void readFromFile(std::string file);
		//Write A Graph To A File
		void writeToFile(std::string file);
		//Print vertices
		void printVertices();
		//Print edges
		void printEdges();
		//Empty
		bool empty();
		//Add Edge
		void addEdge(int v1, int v2, double weight);
		//Add Vertex
		void addVertex();
		//Count Connected Components
		int numConnectedComponents();
		//Tree Check
		bool tree();
		//Depth First Traverse
		void DFT(int source, std::string file);
		//Breadth First Traverse
		void BFT(int source, std::string file);
		//Closeness
		int closeness(int v1, int v2);
		//* Partition
		bool partitionable();
		//* MST
		bool MST(std::string file);
		//* Step Away
		void stepAway(int source, int closeness, std::string file);
        int closenessHelp(int v1, int v2);
};
#endif // GRAPH_H
