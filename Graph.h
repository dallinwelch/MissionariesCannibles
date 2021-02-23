#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
using namespace std;


template <typename Type>
class Graph;

template <typename Type>
ostream& operator << (ostream& out, const Graph<Type>& g);

template <typename Type>
class Graph {
private:
	vector<Type> verticies;
	vector<vector<Type> > edges;
	//TODO Add private variables here

public:
	Graph();
	void addVertex(Type vertex);
	void addEdge(Type, Type);
	int getVertexPos(Type item);
	int getNumVertices()const;
	bool isEdge(Type, Type);
	friend ostream& operator << <>(ostream& out, const Graph<Type>& g);
	vector<Type>getPath(Type, Type);
	void search(shared_ptr<bool[]> closed, stack<Type> open, Type start, Type destination, stack<Type>& solution, bool& found);
};



/*********************************************
* Constructs an empty graph
*
*********************************************/
template<typename Type>
Graph<Type>::Graph() {

}




/*********************************************
* Adds a Vertex to the Graphs. Note that the vertex may not be an int value
*********************************************/
template <typename Type>
void Graph<Type>::addVertex(Type vertex) {
	verticies.push_back(vertex);
	vector<Type>lst;
	edges.push_back(lst);
}

/*********************************************
* Returns the current number of vertices
*
*********************************************/
template<typename Type>
int Graph<Type>::getNumVertices()const {
	return verticies.size();
}



/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
*
*********************************************/
template <typename Type>
int Graph<Type>::getVertexPos(Type item) {
	for (unsigned i = 0; i < verticies.size(); i++) {
		if (item == verticies[i]) {
			return i;
		}
	}
	return -1; //return negative one
}//End findVertexPos

/*********************************************
* Adds an edge going in the direction of source going to target
*
*********************************************/
template <typename Type>
void Graph<Type>::addEdge(Type source, Type target) {
	int srcPos = getVertexPos(source);
	if (srcPos < 0) {
		throw runtime_error("Vertex not found");
	}
	edges[srcPos].push_back(target);
}

template <typename Type>
bool Graph<Type>::isEdge(Type source, Type dest) {
	int srcPos = getVertexPos(source);
	if (srcPos < 0) {
		throw runtime_error("Vertex not found");
	}
	for (unsigned int i = 0; i < edges[i].size(); i++) {
		if (edges[srcPos][i] == dest) {
			return true;
		}
	}
	return false;
}



/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
* Note: This is not a traversal, just output
*********************************************/
template <typename Type>
ostream& operator << (ostream& out, const Graph<Type>& g) {
	for (unsigned int i = 0; i < g.verticies.size(); i++) {
		out << g.verticies[i] << ": ";
		for (unsigned int e = 0; e < g.edges[i].size(); e++) {
			out << g.edges[i][e] << " ";
		}
	}
	return out;
}

/*
  getPath will return the shortest path from source to dest.
  You are welcome to use any solution not limited to the following, depth first search to traverse
  graph to find the solution, breadth first, shortest path first, or any
  other graph algorithm.

  You will return a vector with the solution from the source to the destination.
  IE: The source will be in position 1 the destination is in the last position of the solution, and each node in between
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.
*/
template <typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) {
	//two verticies and the rest nodes
	int pos = getVertexPos(source);
	vector<Type> solution;
	stack<Type> sol;
	stack<Type> open;
	stack<Type> switcher;

	bool found = false;
	shared_ptr<bool[]>closed(new bool [getNumVertices()]  );
	for (unsigned int e = 0; e < getNumVertices(); e++) {
		closed[e] = false;
	}
	//array<bool> closed(getNumVertices());//make all false
	//sol.push(source);
	search(closed, open, source, dest, sol, found);
	while (!sol.empty()) {
		Type temp = sol.top();

		switcher.push(temp);
		sol.pop();

		//cout <<"Solution" <<temp << endl;
	}
	
	while (!switcher.empty()) {
		Type temp = switcher.top();
		
		solution.push_back(temp); 
		switcher.pop();
		
		//cout <<"Solution" <<temp << endl;
	}
	
	solution.push_back(dest);
	return solution;
}


template <typename Type>
void Graph<Type>::search(shared_ptr<bool[]> closed, stack<Type> open, Type start, Type destination, stack<Type>  &solution,bool &found) {
	//Type eval;

	int pos = getVertexPos(start);
	//always true so it aways skips the if statement in for loop
	closed[pos] = true;
	for (unsigned int e = 0; e < edges[pos].size(); e++) {
		
		//open.push(edges[getVertexPos(eval) ] [e] );
		if (closed[ (getVertexPos (edges[pos] [e]) ) ] == false) {
			//closed[(getVertexPos(edges[pos][e]))] = true;
			if (found == false) {
				solution.push(start);
			}
			if (edges[pos][e] == destination) {
				found = true;
			}
			search(closed, open, edges[pos][e], destination, solution, found);
			if (found == false) {
				solution.pop();
			}
		}
	
	}

}
