#include <iostream>

#include "ham.h"

using namespace std;


void run_clq()
{
	char fileName[] = "graphs/test1.clq";


	cout << "Reading clq: " << fileName << endl;
	HAM* hp = new HAM(fileName);

	cout << "Computing number of hamiltonian cycles" << endl;
	cout << "Cycles = " << hp->compute_num_cycle() << endl;

	cout << "Computing path of hamiltonian cycles" << endl;
	cout << "Cycle:\n" << hp->compute_hami_cycle() << endl;
}


void run_gml()
{
	char fileName[] = "graphs/test1.gml";


	cout << "Reading gml: " << fileName << endl;
	HAM* hp = new HAM(fileName, DIRECT);

	cout << "Computing number of hamiltonian cycles" << endl;
	cout << "Cycles = " << hp->compute_num_cycle() << endl;

	cout << "Computing path of hamiltonian cycles" << endl;
	cout << "Cycle:\n" << hp->compute_hami_cycle() << endl;
}

void run_adj()
{
	char fileName[] = "graphs/test1.adj";


	cout << "Reading adj: " << fileName << endl;
	HAM* hp = new HAM(fileName);

	cout << "Computing number of hamiltonian cycles" << endl;
	cout << "Cycles = " << hp->compute_num_cycle() << endl;

	cout << "Computing path of hamiltonian cycles" << endl;
	cout << "Cycle:\n" << hp->compute_hami_cycle() << endl;
}

void run_txt()
{
	char fileName[] = "graphs/lpeter.txt";

	cout << "Reading txt: " << fileName << endl;
	HAM* hp = new HAM(fileName);

	cout << "Computing number of hamiltonian cycles" << endl;
	cout << "Cycles = " << hp->compute_num_cycle() << endl;

	cout << "Computing path of hamiltonian cycles" << endl;
	cout << "Cycle:\n" << hp->compute_hami_cycle() << endl;
}


void run_test()
{
	clock_t s, e;
	char fileName[] = "graphs/lpeter.txt";

	cout << "Reading: " << fileName << endl;
	HAM* hp = new HAM(fileName);

	cout << "Computing number of hamiltonian cycle" << endl;

	s = clock();
	cout << "Original: Cycles = " << hp->compute_num_cycle() << endl;
	e = clock();
	cout << "Clocks: " << e - s << endl;

	s = clock();
	cout << "Enhanced 1: Cycles = " << hp->compute_num_cycle_enhance() << endl;
	e = clock();
	cout << "Clocks: " << e - s << endl;

	s = clock();
	cout << "Enhanced 2: Cycles = " << hp->compute_num_cycle_enhance_2() << endl;
	e = clock();
	cout << "Clocks: " << e - s << endl;

}

int main()
{
	cout << "Program Starts...\n" << endl;

	run_test();

	cout << "\nProgram Ends..." << endl;
	return 0;
}