#ifndef COLOR_H_
#define COLOR_H_

#include "graph.h"
#include <math.h>

// return min number of vertex color
int chromatic_number(Graph* g);
// return k-color
long long chromatic_number(Graph* g, int* table, int k, int size);
// binary seach of k
int binary_search(Graph* g, int* table, int size, int left, int right);
// n choose k with replacement
int nCk_withreplace(int n, int k);
// factorial
int factorial(int x);
// remove a vertex from set, return the id of that vertex
int remove_vertex(Graph* g, int* set);
// remove a vertex's (vertex is already removed) adj vertices from set
int remove_vertex(Graph* g, int* set, int vid);
// compute the dynamic table
int compute_table(Graph* g, int* table, int size);
// compute the dynamic table (helper function)
int compute_table_helper(Graph* g, int* table, int index);
// count the number of vertices NOT in the set
int num_vertex(int* set, int length);
// transfer int value to a set
int int_to_set(int* set, int val, int n);
// transfer set to int value
int set_to_int(int* set, int n);
// determine if W is subset of S
int is_subset(int* S, int* W, int length);
// print set S
int print_set(int* S, int length);
// print table
int print_table(Graph* g, int* table, int size);
// dirty debug function, could be removed after release
int dirty_debug(Graph* g);


#endif