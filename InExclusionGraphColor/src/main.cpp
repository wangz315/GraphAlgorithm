#include <iostream>
#include <ctime>
#include <chrono>

#include "readgraph.h"
#include "graphcolor.h"


using namespace std;


int main()
{
	cout << "Program starts...\n" << endl;

	char path[] = "graphs/Graph1.txt";

	cout << "Reading the graph " << path << "..." << endl;
	GraphMatrix* g = gtom(path);
	cout << "Computing the chromatic number, start the timer..." << endl;
	auto start_time = chrono::high_resolution_clock::now();
	int color = chromatic_number(g);
	auto end_time = chrono::high_resolution_clock::now();
	cout << "\nchromatic number: " << color << endl;
	cout << "time cost: " << chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count() << " milliseconds" << endl;

	cout << "\nProgram ends..." << endl;
	return 0;
}