#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "ham.h"
#include "matrixUtil.h"

using namespace std;

// constructors
HAM::HAM(int x)
{
	if(x == 3)
	{
		HAM::create_instance_3();
	}
	else
	{
		HAM::create_instance_4();
	}
	
}

HAM::HAM(int n, int* matrix)
{
	this->n = n;
	this->matrix = matrix;
}


HAM::HAM(char* fileName, int direct)
{
	HAM::read_gml(fileName, direct);
}

HAM::HAM(char* fileName)
{
	string name = fileName;
	string ext = name.substr(name.find_last_of(".") + 1, name.length() - 1);

	if(!ext.compare("adj"))
	{
		HAM::read_adj(fileName);
	}
	else if(!ext.compare("clq"))
	{
		HAM::read_clq(fileName);
	}
	else if(!ext.compare("txt"))
	{
		HAM::read_txt(fileName);
	}
}


// destructor
HAM::~HAM(){}


void HAM::read_clq(char* fileName)
{
	string token;
	char* tag = new char[TAGSIZE];
	char id;

	int value;
	int s;
	int t;

	ifstream input;
	input.open(fileName);

	while(getline(input, token))
	{
		token = string_trim(token);

		if(token.at(0) == 'p')
		{
			sscanf(token.c_str(), "%c %s %d %d", &id, tag, &n, &value);

			matrix = new int[n * n];

			for(int i = 0; i < n; i++)
			{
				matrix[i] = 0;
			}

			while(getline(input, token))
			{
				if(token.at(0) == 'e')
				{
					sscanf(token.c_str(), "%c %d %d", &id, &s, &t);

					s--;
					t--;

					matrix[s * n + t] = 1;
					matrix[t * n + s] = 1;
				}
			}
		}
	}


	input.close();
}


void HAM::read_gml(char* fileName, int direct)
{
	string token;
	char* tag = new char[TAGSIZE];

	n = 0;

	int value;
	int s;
	int t;

	ifstream input;
	input.open(fileName);

	while(getline(input, token))
	{
		token = string_trim(token);

		if(!token.compare("node"))
		{
			n++;
		}
		else if(!token.compare("edge"))
		{
			matrix = new int[n * n];

			for(int i = 0; i < n; i++)
			{
				matrix[i] = 0;
			}

			while(getline(input, token))
			{
				sscanf(token.c_str(), "%s %d", tag, &value);
				if(!strcmp(tag, "source"))
				{
					s = value;
				}
				else if(!strcmp(tag, "target"))
				{
					t = value;
				}
				else if(!strcmp(tag, "edge"))
				{
					matrix[s * n + t] = 1;
					if(!direct)
					{
						matrix[t * n + s] = 1;
					}
				}
			}

			matrix[s * n + t] = 1;

			if(!direct)
			{
				matrix[t * n + s] = 1;
			}
		}
	}

	input.close();
}


void HAM::read_adj(char* fileName)
{
	int token = 0;
	int index = 0;

	ifstream input;
	input.open(fileName);

	input >> n;

	matrix = new int[n * n];

	while(input >> token)
	{
		matrix[index] = token;
		index++;
	}

	input.close();
}

void HAM::read_txt(char* fileName)
{
	int token = 0;
	int index = 0;

	ifstream input;
	input.open(fileName);

	input >> n;


	matrix = new int[n * n];

	for(int i = 0; i < n; i++)
	{
		matrix[i] = 0;
	}

	input >> token;

	while(token != 0)
	{
		index = -1 * token;
		index--;

		input >> token;
		while(token > 0)
		{
			token--;

			matrix[index * n + token] = 1;
			matrix[token * n + index] = 1;

			input >> token;
		}
	}

	input.close();
}


// create a simple instances
void HAM::create_instance_3()
{
	n = 3;

	matrix = new int[n * n];
	for(int i = 0; i < n * n; i++)
	{
		matrix[i] = 0;
	}

	matrix[0 * n + 1] = 1;
	matrix[1 * n + 2] = 1;
	matrix[2 * n + 0] = 1;
}


void HAM::create_instance_4()
{
	n = 4;

	matrix = new int[n * n];
	for(int i = 0; i < n * n; i++)
	{
		matrix[i] = 0;
	}

	matrix[0 * n + 1] = 1;
	matrix[0 * n + 2] = 1;
	matrix[1 * n + 2] = 1;
	matrix[1 * n + 3] = 1;
	matrix[2 * n + 3] = 1;
	matrix[3 * n + 0] = 1;
}


string HAM::string_trim(string str)
{
	size_t first = str.find_first_not_of(' ');
	if(string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

// convert val to a binary in string format
// return number of 1s in subset
int HAM::int_to_binary(unsigned int val, int n, char* subset)
{
	unsigned int mask = 1 << (n - 1);
	int count = 0;

	for(int i = 0; i < n; i++)
	{
		if((val & mask) == 0)
		{
			subset[i] = '0';
		}
		else
		{
			subset[i] = '1';
			count++;
		}

		mask >>= 1;
	}

	return count;
}


int HAM::binary_to_int(int n, char* subset)
{
	int val = 0;

	for(int i = 0; i < n; i++)
	{
		if(subset[i] == '1')
		{
			val += pow(2, i);
		}
	}

	return val;
}


// compare two subsets, works as if(subset & removed)
// faster way: bitset
int HAM::subset_cmp(char* subset, char* removed)
{
	for(int i = 0; i < n; i++)
	{
		if(subset[i] == '1' && removed[i] == '1')
		{
			return 0;
		}
	}

	return 1;
}


int HAM::is_superset(vector<int>* set, int superset)
{
	for(unsigned int i = 0; i < set->size(); i++)
	{
		if(((*set)[i] & superset) >= (*set)[i])
		{
			return 1;
		}
	}

	return 0;
}


void HAM::set_flags(int numObj, unordered_map<int, int>* flags, char* subset)
{
	char* zeroset = new char[n - numObj];
	char* currSet = new char[n];
	int currIndex;

	for(unsigned int i = 0; i < pow(2, n - numObj); i++)
	{
		currIndex = 0;
		HAM::int_to_binary(i, n - numObj, zeroset);

		for(int j = 0; j < n; j++)
		{
			if(subset[j] == '1')
			{
				currSet[j] = '1';
			}
			else
			{
				currSet[j] = zeroset[currIndex];
				currIndex++;
			}
		}

		int index = HAM::binary_to_int(n, currSet);
		(*flags)[index] = ZERO;
	}
}


// basic function
int HAM::compute_num_paths(int s, int t, int length, int* matrix)
{
	int count = 0;
	uint64_t size = pow(2, n);

	//#pragma omp parallel for reduction(+:count)
	for(unsigned int i = 0; i < size; i++)
	{
		int* subMatrix = new int[n * n];
		matrix_deep_copy(matrix, subMatrix, n);

		char* subset = new char[n];
		int numObj = HAM::int_to_binary(i, n, subset);

		for(int j = 0; j < n; j++)
		{
			if(subset[j] == '1')
			{
				for(int k = 0; k < n; k++)
				{
					subMatrix[j * n + k] = 0;
					subMatrix[k * n + j] = 0;
				}
			}
		}

		int* result = new int[n * n];
		matrix_fast_pow(subMatrix, result, length, n);
		count += pow(-1, numObj) * result[s * n + t];
	}

	return count;
}

int HAM::compute_num_paths_enhance(int s, int t, int length, int* matrix)
{

	int count = 0;
	int current;
	char* subset = new char[n];
	int* result = new int[n * n];
	int* subMatrix = new int[n * n];

	unordered_map<int, int> flags;

	matrix_deep_copy(matrix, subMatrix, n);

	for(unsigned int i = 0; i < pow(2, n); i++)
	{
		if(flags[i] == UNDEFINED)
		{
			int numObj = HAM::int_to_binary(i, n, subset);

			for(int j = 0; j < n; j++)
			{
				if(subset[j] == '1')
				{
					for(int k = 0; k < n; k++)
					{
						subMatrix[j * n + k] = 0;
						subMatrix[k * n + j] = 0;
					}
				}
			}

			matrix_fast_pow(subMatrix, result, length, n);

			current = pow(-1, numObj) * result[s * n + t];
			count += current;

			if(current == 0)
			{
				HAM::set_flags(numObj, &flags, subset);
			}

			matrix_deep_copy(matrix, subMatrix, n);
		}
		
	}

	return count;
}





int HAM::compute_num_paths_enhance_2(int s, int t, int length, int* matrix)
{
	unordered_map<int, int> com;
	vector<int> prune;
	int count;
	int numObj;
	int current;


	// u set
	int* result = new int[n * n];
	matrix_fast_pow(matrix, result, length, n);
	count = result[s * n + t];

	if(count == 0)
	{
		return 0;
	}

	// sets ordered by number objs
	for(int k = 1; k <= n; k++)
	{
		for (int i = 0; i < k; i++)
		{
			com[i] = i;
		}

		while (com[k - 1] < n)
		{
			char* subset = new char[n];

			for (int i = 0; i < n; i++)
			{
				subset[i] = '0';
			}


			for (int i = 0; i < k; i++)
			{
				subset[com[i]] = '1';
			}


			int intset = binary_to_int(n, subset);

			if(!is_superset(&prune, intset))
			{
				int* result = new int[n * n];
				int* subMatrix = new int[n * n];

				matrix_deep_copy(matrix, subMatrix, n);

				numObj = k;

				for(int j = 0; j < n; j++)
				{
					if(subset[j] == '1')
					{
						for(int k = 0; k < n; k++)
						{
							subMatrix[j * n + k] = 0;
							subMatrix[k * n + j] = 0;
						}
					}
				}

				matrix_fast_pow(subMatrix, result, length, n);

				current = pow(-1, numObj) * result[s * n + t];
				count += current;

				if(current == 0)
				{
					prune.push_back(intset);
				}

				matrix_deep_copy(matrix, subMatrix, n);
			}
			

			int t = k - 1;
			while (t != 0 && com[t] == n - k + t)
			{
				t--;
			}

			com[t]++;

			for (int i = t + 1; i < k; i++)
			{
				com[i] = com[i - 1] + 1;
			}
		}
	}

	return count;
}


int HAM::compute_num_sub_paths(int s, int t, int length, int* matrix, char* removed)
{
	int count = 0;
	char* subset = new char[n];
	int* subMatrix = new int[n * n];

	matrix_deep_copy(matrix, subMatrix, n);

	for(unsigned int i = 0; i < pow(2, n); i++)
	{
		int numObj = HAM::int_to_binary(i, n, subset);

		if(HAM::subset_cmp(subset, removed))
		{
			for(int j = 0; j < n; j++)
			{
				if(subset[j] == '1')
				{
					for(int k = 0; k < n; k++)
					{
						subMatrix[j * n + k] = 0;
						subMatrix[k * n + j] = 0;
					}
				}
			}

			int* result = new int[n * n];
			matrix_fast_pow(subMatrix, result, length, n);

			count += pow(-1, numObj) * result[s * n + t];

			matrix_deep_copy(matrix, subMatrix, n);

		}
	}

	return count;
}

// helper functions
int HAM::compute_num_paths(int s, int t, int* matrix)
{
	if(s == t)
	{
		return HAM::compute_num_paths(s, t, n, matrix);
	}
	else
	{
		return HAM::compute_num_paths(s, t, n - 1, matrix);
	}
}

int HAM::compute_num_paths(int s, int t)
{
	if(s == t)
	{
		return HAM::compute_num_paths(s, t, n, matrix);
	}
	else
	{
		return HAM::compute_num_paths(s, t, n - 1, matrix);
	}
}

int HAM::compute_num_cycle()
{
	return HAM::compute_num_paths(0, 0);
}


int HAM::compute_num_paths_enhance(int s, int t)
{
	if(s == t)
	{
		return HAM::compute_num_paths_enhance(s, t, n, matrix);
	}
	else
	{
		return HAM::compute_num_paths_enhance(s, t, n - 1, matrix);
	}
}

int HAM::compute_num_paths_enhance_2(int s, int t)
{
	if(s == t)
	{
		return HAM::compute_num_paths_enhance_2(s, t, n, matrix);
	}
	else
	{
		return HAM::compute_num_paths_enhance_2(s, t, n - 1, matrix);
	}
}

int HAM::compute_num_cycle_enhance()
{
	return HAM::compute_num_paths_enhance(0, 0, n, matrix);
}

int HAM::compute_num_cycle_enhance_2()
{
	return HAM::compute_num_paths_enhance_2(0, 0, n, matrix);
}


// basic function
string HAM::compute_hami_path_origin(int s, int t, int length)
{
	stringstream path;
	int count = 0;
	int* subMatrix = new int[n * n];

	matrix_deep_copy(matrix, subMatrix, n);

	if(HAM::compute_num_paths(s, t, length, subMatrix) > 0)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(subMatrix[i * n + j] > 0)
				{
					subMatrix[i * n + j] = 0;
					count = HAM::compute_num_paths(s, t, subMatrix);

					if(count == 0)
					{
						subMatrix[i * n + j] = 1;
						path << i << "->" << j << " " << endl;
					}
				}
			}
		}
	}
	else
	{
		path << "Path does not exist" << endl;
	}



	path << endl;

	return path.str();
}


string HAM::compute_hami_path(int s, int t, int length)
{
	stringstream path;
	int count1 = 0;
	int count2 = 0;
	int* subMatrix = new int[n * n];
	char* removed = new char[n];

	for(int i = 0; i < n; i++)
	{
		removed[i] = '0';
	}

	matrix_deep_copy(matrix, subMatrix, n);
	count1 = HAM::compute_num_paths(s, t, subMatrix);


	if(count1 > 0)
	{
		while(length > 0)
		{
			for(int i = 0; i < n; i++)
			{
				if(subMatrix[s * n + i] > 0)
				{
					subMatrix[s * n + i] = 0;

					count2 = HAM::compute_num_sub_paths(s, t, length, subMatrix, removed);

					if(count1 > count2)
					{
						path << s << "->" << i << " " << endl;
						removed[s] = '1';

						for(int j = i + 1; j < n; j++)
						{
							subMatrix[s * n + j] = 0;
						}

						s = i;
						length--;
						count1 = HAM::compute_num_sub_paths(s, t, length, subMatrix, removed);

						break;
					}
				}
			}
		}


		path << endl;
	}
	else
	{
		path << "Path does not exist" << endl;
	}

	return path.str();
}

// helper functions
string HAM::compute_hami_path(int s, int t)
{
	if(s == t)
	{
		return HAM::compute_hami_path(s, t, n);
	}
	else
	{
		return HAM::compute_hami_path(s, t, n - 1);
	}
}

string HAM::compute_hami_cycle()
{
	return HAM::compute_hami_path(0, 0, n);
}
