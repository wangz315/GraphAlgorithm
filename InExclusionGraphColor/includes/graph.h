#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>

using namespace std;

class Graph
{
	public:
		string name;
		int e; // number edges
		int v; // number vertices

		Graph();
		~Graph();

		void print();
};


class GraphMatrix : public Graph
{
	public:
		int* matrix;

		GraphMatrix();
		~GraphMatrix();

		void print();
};


#endif