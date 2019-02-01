#pragma once
#include "List.h"

struct Gnode{
	int data;
	int vertex;
	bool visited;
	List<Gnode> *adj;

	Gnode(const int & val) : data(val), adj(NULL), vertex(0), visited(false) {}
	Gnode(List<Gnode> *n = NULL) : adj(n) {}
};

class graph {
private:
	int size;
	Gnode *G;

public:
	
	graph() {
		size = 10;
		G = new Gnode[10];
	}

	graph (int s) {
		size = s;		
		G = new Gnode[s];
	}

	void addEdge(int v, int w) {
		G->vertex = v;
		G->adj->push_back(w);
	}

	bool isEmpty() {
	
	}

	void createGraph() {

	
	}

	void print() {
	
	}

};