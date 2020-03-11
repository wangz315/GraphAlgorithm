#include "gcolor.h"

int gcolor(int* adj, int n)
{

	int size = pow(2, n);
	int table[size];

	compute_table_omp(adj, n, table, size);

	// binary seach k
	int k = binary_search(adj, n, table, size, 0, n);

	return k;
}


long long gcolor_2(int* adj, int n, int* table, int k, int size)
{
	long long sum = 0;

	for(int i = 0; i < size; i++)
	{
		int set[n];
		int num = int_to_set(set, i, n);
		int m = table[i];
		long long sxk = pow(m, k);
		sum = sum + pow(-1, n-num)*sxk;
	}

	return sum;
}


long long gcolor_2_omp(int* adj, int n, int* table, int k, int size)
{
	long long sum = 0;

	#pragma omp parallel for reduction(+: sum)
	for(int i = 0; i < size; i++)
	{
		int set[n];
		int num = int_to_set(set, i, n);
		int m = table[i];
		long long sxk = pow(m, k);
		sum = sum + pow(-1, n-num)*sxk;
	}

	return sum;
}


int binary_search(int* adj, int n, int* table, int size, int left, int right)
{
	int flags[n+1]; // 0 = undefined, 1 = valid colouring, -1 = invalid colouring

	while(left <= right)
	{
		int middle = (left + right) / 2;
		long long value = gcolor_2(adj, n, table, middle, size);

		if(value > 0 && middle > 0 && flags[middle - 1] == -1)
		{
			return middle;
		}
		else if(value <= 0 && middle < (n-1) && flags[middle + 1] == 1)
		{
			return middle + 1;
		}
		else if(value > 0)
		{
			flags[middle] = 1;
			right = middle - 1;
		}
		else
		{
			flags[middle] = -1;
			left = middle + 1;
		}

	}

	return -1;
}



int nCk_withreplace(int n, int k)
{
	if(n < k)
	{
		return 0;
	}
		

	int top = factorial(n + k - 1);
	int down = factorial(k) * factorial(n - 1);
	return top/down;
}


int factorial(int x)
{
	return (x == 1 ? x : x * factorial(x - 1));
}


int remove_vertex(int* adj, int n, int* set)
{

	for(int i = 0; i < n; i++)
	{
		if(set[i] == 1)
		{
			set[i] = 0;
			return i;
		}
	}

	return -1;
}


int remove_vertex_2(int* adj, int n, int* set, int vid)
{
	for(int i = 0; i < n; i++)
	{
		if(adj[i * n + vid] == 1 && set[i] == 1) // if there is i to v, and i is in the set
		{
			set[i] = 0; // remove i for the set
		}
	}

	return -1;
}



int compute_table(int* adj, int n, int* table, int size)
{

	// sets are V subsets
	for(int set = 0; set < size; set++)
	{
		table[set] = -1; // -1 = undefined
	}

	table[0] = 0; // s[V] = 0, no sets

	for(int set = size-1; set >= 0; set--)
	{
		compute_table_helper(adj, n, table, set);
	}

	return 1;
}


int compute_table_helper(int* adj, int n, int* table, int index)
{

	if(table[index] == -1) // if it is not defined
	{
		int set[n];
		int_to_set(set, index, n);
		int vid = remove_vertex(adj, n, set);
		int vindex = set_to_int(set, n);

		compute_table_helper(adj, n, table, vindex); // s(X U v)

		remove_vertex_2(adj, n, set, vid);
		int vadjindex = set_to_int(set, n);

		compute_table_helper(adj, n, table, vadjindex); // s(X U v U N(v)}

		table[index] = table[vindex] + table[vadjindex] + 1;
	}


	return 1;
}



int compute_table_omp(int* adj, int n, int* table, int size)
{

	// sets are V subsets
	for(int set = 0; set < size; set++)
	{
		table[set] = -1; // -1 = undefined
	}

	table[0] = 0; // s[V] = 0, no sets


	// #pragma omp parallel
	#pragma omp single nowait
	for(int set = size-1; set >= 0; set--)
	{
		compute_table_helper_omp(adj, n, table, set);
	}

	return 1;
}


int compute_table_helper_omp(int* adj, int n, int* table, int index)
{

	if(table[index] == -1) // if it is not defined
	{
		int set[n];
		int_to_set(set, index, n);
		int vid = remove_vertex(adj, n, set);
		int vindex = set_to_int(set, n);

		#pragma omp task
		compute_table_helper(adj, n, table, vindex); // s(X U v)

		remove_vertex_2(adj, n, set, vid);
		int vadjindex = set_to_int(set, n);
		
		#pragma omp task
		compute_table_helper(adj, n, table, vadjindex); // s(X U v U N(v)}

		#pragma omp taskwait
		table[index] = table[vindex] + table[vadjindex] + 1;
	}


	return 1;
}


int num_vertex(int* set, int length)
{
	int count = 0;
	
	for(int i = 0; i < length; i++)
	{
		if(set[i] == 0)
		{
			count++;
		}
	}

	return count;
}


int int_to_set(int* set, int val, int n)
{
	unsigned int mask = 1 << (n - 1);
	int count = 0;

	for(int i = 0; i < n; i++)
	{
		if((val & mask) == 0)
		{
			set[i] = 0;
		}
		else
		{
			set[i] = 1;
			count++;
		}

		mask >>= 1;
	}

	return count; // return number of 1s
}

int set_to_int(int* set, int n)
{
	int val = 0;

	for(int i = 0; i < n; i++)
	{
		if(set[i] == 1)
		{
			val += pow(2, n-i-1);
		}
	}

	return val;
}


int is_subset(int* S, int* W, int length)
{
	for(int i = 0; i < length; i++)
	{
		if((S[i] == 0) && (W[i] == 1))
		{
			return 0;
		}
	}

	return 1;
}