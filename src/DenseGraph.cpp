#include <fstream>
#include <sstream>
#include <iostream>
#include "DenseGraph.h"
#include <stdexcept>
#include <queue>
#include <functional>
#include <limits>
#include <math.h>
#include <list>
static const int PLACEHOLDER = 0;
//static const double INFINITY = INFINITY; //std::numeric_limits<double>::infinity();
//static const int MAX = std::numeric_limits<int>::max();
using namespace std;

//Construct a graph
DenseGraph::DenseGraph() : numVertices(0), numEdges(0), adjMatrix(nullptr) {}

//Delete
DenseGraph::~DenseGraph(){
    if(adjMatrix != nullptr){
        for(int i = 0; i <= numVertices; ++i){
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
}

//Read A DenseGraph From A File
void DenseGraph::readFromFile(std::string file){
    ifstream inputFile(file);
    string line;
    getline(inputFile,line);
    numVertices = stoi(line);
    adjMatrix = new double*[numVertices+1];
    //cout << "Size of graph: " << numVertices << "\n";
    for(int i = 0; i <= numVertices; ++i){
        adjMatrix[i] = new double[numVertices+1];
        for(int j = 0; j <= numVertices; ++j){
            adjMatrix[i][j] = 0;
           //cout << "Edge " << "( " << i << "," << j << ")" << "=" << adjMatrix[i][j] << endl;
            //DEBUG
        }
    }
    vertices.push_back(PLACEHOLDER);
    getline(inputFile,line);
    numEdges = 0;
    while(getline(inputFile,line)){
        int vert1 = 0;
        int vert2 = 0;
        double weight;
        stringstream ss(line);
        ss >> vert1;
        if (vert1 == -1) break;
        if (!binary_search(vertices.begin(), vertices.end(), vert1)) {
            vertices.push_back(vert1);
        }
        ss >> vert2;
        if (!binary_search(vertices.begin(), vertices.end(), vert2)) {
            vertices.push_back(vert2);
        }
        ss >> weight;
        //cout << "Adding edge <" << vert1 << ", " << vert2 << ", " << weight << ">\n";
        addEdge(vert1,vert2,weight);
        numEdges++;
    }
    
}

void DenseGraph::printVertices(){
    cout << "Printing vertices" << endl;
    for(unsigned i = 0; i < vertices.size();++i){
        cout << vertices.at(i) << endl;
    }
}

void DenseGraph::printEdges(){
    cout << "Printing edges" << endl;
    for(unsigned i = 0; i < edges.size(); ++i){
        cout << "(" << edges.at(i).start << " ," << edges.at(i).end << ")" << endl;
    }
}

//Searches vector vec for a value. Returns the first index at which value appears in vector vec. If not found, -1 is returned.
int DenseGraph::searchVector(vector<int> vec, int value){
    for(unsigned i = 0; i < vec.size(); ++i){
        if(vec.at(i) == value){
            return i;
            break;
        }
    }
    return -1;
}

//Write A DenseGraph To A File
void DenseGraph::writeToFile(std::string file){
    ofstream outf(file);
    outf << to_string(numVertices) << "\n" << endl;
    outf << to_string(numEdges) << "\n" << endl;
    if(!edges.empty()){
        for(unsigned i = 0; i < edges.size(); ++i){
            outf << to_string(edges[i].start) << ", " <<
            to_string(edges[i].end) << ", " <<
            to_string(edges[i].weight) << "\n" << endl;
        }
    }
    else{
        outf << "empty graph" << "\n" << endl;
    }
}

//Empty
bool DenseGraph::empty(){
    bool retVal = false;
    if(vertices.empty()){
        retVal = true;
    }
    return retVal;
}

//Add Edge
void DenseGraph::addEdge(int v1, int v2, double weight){
    Edge e = Edge(v1,v2,weight);
    edges.push_back(e);
    int pos1 = searchVector(vertices, v1);
   // cout <<"Vector "<< v1 <<" pos 1" << pos1 << endl; DEBUG
    int pos2 = searchVector(vertices, v2);
   // cout <<"Vector "<< v2 << " pos 2" << pos2 << endl; DEBUG
    if(pos1 < 0 || pos2 < 0){
        throw std::invalid_argument("One of the vertices in the edge don't exist!");
    }
    adjMatrix[v1][v2] = weight;
}

//Add Vertex
void DenseGraph::addVertex(){
    numVertices++;
    vertices.push_back(vertices.size() + 1);
    double** tempMatrix = new double*[numVertices];
    //Allocate and copy adjMatrix to bigger array
    for(int i = 0; i < numVertices; ++i){
        tempMatrix[i] = new double[numVertices];
        for(int j = 0; j < (numVertices); ++j){
            if(i != (numVertices - 1) && j != (numVertices - 1)){
                tempMatrix[i][j] = adjMatrix[i][j];
            } else {
                tempMatrix[i][j] = 0;
            }
        }
    }
    
    //Delete old adjMatrix
    double ** tempPointer = adjMatrix;
    adjMatrix = tempMatrix;
    for(int i = 0; i < (numVertices - 1); ++i){
        delete tempPointer[i];
    }
    delete tempPointer;
}

//Count Connected Components
int DenseGraph::numConnectedComponents(){
    int i, retVal = 0;
    vector<int> accountedVertices;
    accountedVertices.push_back(PLACEHOLDER);
    i = 1;
    while(accountedVertices.size() <= (unsigned)numVertices){
        if(searchVector(accountedVertices, vertices.at(i)) == -1){ //If vertex in question is not accounted for
            accountedVertices.push_back(vertices.at(i));
            //cout << "Pushed " << vertices.at(i) << endl;
            followComponent(vertices.at(i), accountedVertices);
            //cout << "Retval incremented" << endl;
            retVal++;
        }
        ++i;
    }
    return retVal;
}

//Helper Method for numConnectedComponents
void DenseGraph::followComponent(int v, vector<int>& accountedVertices){
    int i;
    for(i = 1; i <= numVertices; ++i){
        if((adjMatrix[v][i] != 0 || adjMatrix[i][v] != 0) && searchVector(accountedVertices, i) < 0){ //If v connects to vertex i and i hasnt been accounted for yet
            //cout << "Pushed " << i << endl;
            
            accountedVertices.push_back(i);
            followComponent(i, accountedVertices); //Recursively follow children
        }
    }
}

//Tree Check
bool DenseGraph::tree(){
    bool retVal = false;
    if(edges.size()/2 == vertices.size() - 1){ //The conditions for a graph to be a tree
        retVal = true;
    }
    return retVal;
}

//Depth First Traverse
void DenseGraph::DFT(int source, string file){
    ofstream outf(file);
    Status visited[numVertices+1]; //Keeps track of the visited vertices
    int i;
    queue<int> traversedNodes; //Keeps the order of the traversed vertices
    for(i = 1; i <= numVertices; ++i){
        visited[i] = NOT_VISITED;
    }
    DFTHelper(source, visited, traversedNodes);
    int size = traversedNodes.size();
   // cout << "Size is: " << size << endl;
    for(i = 0; i < size; ++i){
        int front = traversedNodes.front();
        traversedNodes.pop();
        outf << front << endl;
    }
    outf.close();
}

//Helper for DFT
void DenseGraph::DFTHelper(int source, Status* visited, queue<int>& traversedNodes){
    int i;
    visited[source] = VISITED;
    for(i = 1; i <= numVertices; ++i){
        if(adjMatrix[source][i] != 0 && visited[i] == NOT_VISITED){
            DFTHelper(i, visited, traversedNodes);
        }
    }
    traversedNodes.push(source);
    //cout << "Pushed " << source << endl;
}

//Breadth First Traverse
void DenseGraph::BFT(int source, string file){
    ofstream outf(file);
    //mark verticies as not visited
    Status visited[numVertices+1];
	for(int i =1;i <= numVertices; ++i){
		visited[i]= NOT_VISITED;
	}
    queue<int> q;
    visited[source]= VISITED;
    q.push(source);
    outf << "BFT Source " << to_string(source) << ": " << endl;
   // cout << "BFT Source "  << to_string(source) << ": "<< endl; DEBUG
    while(!q.empty()){
       int v = q.front();
        q.pop();
       // cout << to_string(v) << " "<<endl; DEBUG
        outf << to_string(v) << " "<<endl;
        for( int i =1;i <=numVertices; ++i){
            if(adjMatrix[v][i] !=0 && visited[i]== NOT_VISITED){
                q.push(i);
                visited[i]=VISITED;
			}
		}
	}
}
//Closeness                                                                                                                                                          
int DenseGraph::closeness(int v1, int v2){
    int one = closenessHelp(v1,v2);
    int two = closenessHelp(v2, v1);
    if (one == -1) {
        if (two == -1) {
            return -1;
        }else{
            return 2;
        }
    }
    return one;

}

//* Partition
bool DenseGraph::partitionable(){
    vector<int> red;
    vector<int> blue;
    unsigned i;
    bool retVal = true;
    for(i = 0; i < edges.size(); ++i){
        int vect1 = edges.at(i).start;
        int vect2 = edges.at(i).end;
        int redVect1 = searchVector(red, vect1);
        int blueVect1 = searchVector(blue, vect1);
        int redVect2 = searchVector(red, vect2);
        int blueVect2 = searchVector(blue, vect2);
        if((redVect1 > 0 && redVect2 > 0) || (blueVect1 > 0 && blueVect2 > 0)){ //If both vertices are the same color, it cannot be partitionable;
            return false;
        }
        
        //If one of the vertices are in either the blue set or red set
        if(redVect1 != -1){
            if(blueVect2 == -1){ //Eliminate doubles
                blue.push_back(vect2);
            }
        }
        if(blueVect1 != -1){
            if(redVect2 == -1){ //Eliminate doubles
                red.push_back(vect2);
            }
        }
        if(redVect2 != -1){
            if(blueVect1 == -1){ //Eliminate doubles
                blue.push_back(vect1);
            }
        }
        if(blueVect2 != -1){
            if(redVect1 == -1){ //Eliminate doubles
                red.push_back(vect1);
            }
        }
        
        //If none of the vertices are in either
        if(redVect1 == -1 && redVect2 == -1 && blueVect1 == -1 && blueVect2 == -1){
            red.push_back(vect1); //Arbitrarily put each vertice in separate colors
            blue.push_back(vect2);
        }
    }
    unsigned j;
    for(i = 0; i < red.size();++i){
        for(j = 0; j < blue.size(); ++j){
            if(red.at(i) == blue.at(j)){
                return false;
            }
        }
    }
    return retVal;
}

//* MST                                                                                                                                                              
bool DenseGraph::MST(std::string file){
    ofstream outf(file);
    if (!outf.is_open()) {
        return false;
    }
    Status visited[numVertices +1];
    for(int i = 1; i<=numVertices;++i){
        visited[i] = NOT_VISITED;
    }
    for (int i = 1; i<=numVertices; ++i) {
        if (visited[i]== NOT_VISITED) {
            prim(i,outf,visited);
        }
    }


    return true;
}

//* Step Away                                                                                                                                                        
void DenseGraph::stepAway(int source, int closeness, std::string file){
    ofstream outf(file);
    int c = 0;
    for (int i=1;i<=numVertices; ++i) {
        c = this->closeness(source,i);
        if (c == closeness) {
            outf << to_string(i) <<endl;
        }
    }
}
// Helper function for closeness
int DenseGraph::closenessHelp(int v1, int v2){
    int dis=0;
    if (v1 == v2) {
        return 0;
    }
    int visited[numVertices];
    for(int i =1;i <= numVertices; ++i){
		visited[i]= -1;
	}
    visited[v1] = 0;
    int v = 0;
    queue<int> q;
    q.push(v1);
    while (visited[v2] < 0 && !q.empty()) {
        v = q.front();
        q.pop();
        if(visited[v] > dis){
            ++dis;
        }
        for (int i=1; i<=numVertices; ++i) {
            if(adjMatrix[v][i] !=0 && visited[i] < 0){
                visited[i] = dis+1;
                q.push(i);
            }
        }
    }
    ++dis;
    if(visited[v2] < 0){
        return -1;
    }
    return dis;
}
// Helper function for mst
void DenseGraph::prim(int source, ofstream& file, Status visited[]){
    
    
    visited[source] = VISITED;
    int edgeNum = 0;
    int u = 0;
    int v = 0;
    while(edgeNum < numVertices -1 ){
	    double minimum = numeric_limits<double>::infinity();
        file << "{" ;
        for (int i = 1; i <= numVertices; ++i) {
            if (visited[i] == VISITED) {
                for (int j =1 ; j <= numVertices; ++j) {
                    if (visited[j] == NOT_VISITED) {
                        if (adjMatrix[i][j] < minimum && adjMatrix[i][j] !=0) {
                            minimum = adjMatrix[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
        }
        visited[v] = VISITED;
        //cout << u << v << endl;
        file << u << ", " << v << ", " << adjMatrix[u][v];
        file << "}" ;
        edgeNum += 1;
    }


}

int DenseGraph::getVertSize()
{
    return numVertices;
}
    
const list<Edge> DenseGraph::getEdges(int v)
{
    list<Edge> ret;
    for( int i = 1; i <= numVertices; ++i){
        if(adjMatrix[v][i] != 0){
            Edge e = Edge(v,i, adjMatrix[v][i]);
            ret.push_back(e);
        }
    }
    return ret;
}
