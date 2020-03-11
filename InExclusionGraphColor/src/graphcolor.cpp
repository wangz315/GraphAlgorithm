#include "graphcolor.h"

int chromatic_number(Graph* g)
{

	int size = pow(2, g->v);
	int table[size];

	compute_table(g, table, size);

	// binary seach k
	int k = binary_search(g, table, size, 0, g->v);


	return k;
}


long long chromatic_number(Graph* g, int* table, int k, int size)
{
	long long sum = 0;

	for(int i = 0; i < size; i++)
	{
		int set[g->v];
		int num = int_to_set(set, i, g->v);
		int n = table[i];
		long long sxk = pow(n, k);
		sum = sum + pow(-1, g->v-num)*sxk;
	}

	return sum;
}


int binary_search(Graph* g, int* table, int size, int left, int right)
{
	int flags[g->v+1]; // 0 = undefined, 1 = valid colouring, -1 = invalid colouring

	while(left <= right)
	{
		int middle = (left + right) / 2;
		long long value = chromatic_number(g, table, middle, size);

		if(value > 0 && middle > 0 && flags[middle - 1] == -1)
		{
			return middle;
		}
		else if(value <= 0 && middle < (g->v-1) && flags[middle + 1] == 1)
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


int remove_vertex(Graph* g, int* set)
{

	for(int i = 0; i < g->v; i++)
	{
		if(set[i] == 1)
		{
			set[i] = 0;
			return i;
		}
	}

	return -1;
}


int remove_vertex(Graph* g, int* set, int vid)
{
	for(int i = 0; i < g->v; i++)
	{
		if(((GraphMatrix* )g)->matrix[i * g->v + vid] == 1 && set[i] == 1) // if there is i to v, and i is in the set
		{
			set[i] = 0; // remove i for the set
		}
	}

	return -1;
}


int compute_table(Graph* g, int* table, int size)
{

	// sets are V subsets
	for(int set = 0; set < size; set++)
	{
		table[set] = -1; // -1 = undefined
	}

	table[0] = 0; // s[V] = 0, no sets


	for(int set = size-1; set >= 0; set--)
	{
		compute_table_helper(g, table, set);
	}

	return 1;
}


int compute_table_helper(Graph* g, int* table, int index)
{

	if(table[index] == -1) // if it is not defined
	{
		int set[g->v];
		int_to_set(set, index, g->v);
		int vid = remove_vertex(g, set);
		int vindex = set_to_int(set, g->v);
		compute_table_helper(g, table, vindex); // s(X U v)

		remove_vertex(g, set, vid);
		int vadjindex = set_to_int(set, g->v);
		compute_table_helper(g, table, vadjindex); // s(X U v U N(v)}
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


int print_set(int* S, int length)
{
	cout << "{";
	for(int i = 0; i < length-1; i++)
		cout << S[i] << ",";
	cout << S[length-1] << "}" << endl;

	return 1;
}


int print_table(Graph* g, int* table, int size)
{
	for(int i = 0; i < size; i++)
	{
		int set[g->v];
		int_to_set(set, i, g->v);
		
		cout << "{";
		for(int j = 0; j < g->v-1; j++)
		{
			cout << set[j] << ",";
		}
		cout << set[g->v-1] << "}";

		cout << "=" << i;

		cout << " : " << table[i] << endl;
	}

	return 1;
}


int dirty_debug(Graph* g)
{
	return chromatic_number(g);
}

	