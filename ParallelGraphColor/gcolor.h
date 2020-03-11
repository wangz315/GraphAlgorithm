#ifndef COLOR_H_
#define COLOR_H_

#include <math.h>

// return min number color
int gcolor(int* adj, int n);
// return k-color
long long gcolor_2(int* adj, int n, int* table, int k, int size);
// binary seach of k
int binary_search(int* adj, int n, int* table, int size, int left, int right);
// n choose k with replacement
int nCk_withreplace(int n, int k);
// factorial
int factorial(int x);
// remove a vertex from set, return the id of that vertex
int remove_vertex(int* adj, int n, int* set);
// remove a vertex's (vertex is already removed) adj vertices from set
int remove_vertex_2(int* adj, int n, int* set, int vid);
// compute the dynamic table
int compute_table(int* adj, int n, int* table, int size);
// compute the dynamic table (helper function)
int compute_table_helper(int* adj, int n, int* table, int index);
// count the number of vertices NOT in the set
int num_vertex(int* set, int length);
// transfer int value to a set
int int_to_set(int* set, int val, int n);
// transfer set to int value
int set_to_int(int* set, int n);
// determine if W is subset of S
int is_subset(int* S, int* W, int length);


// compute the dynamic table
int compute_table_omp(int* adj, int n, int* table, int size);
// compute the dynamic table (helper function)
int compute_table_helper_omp(int* adj, int n, int* table, int index);
// return k-color
long long gcolor_2_omp(int* adj, int n, int* table, int k, int size);

#endif