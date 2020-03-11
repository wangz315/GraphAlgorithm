#include <iostream>
#include "matrixUtil.h"

using namespace std;


int matrix_equal(int* matrixA, int* matrixB, int n)
{
	for(int i = 0; i < n * n; i++)
	{
		if(matrixA[i] != matrixB[i])
		{
			return 0;
		}
	}

	return 1;
}

void matrix_deep_copy(int* origin, int* copy, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			copy[i * n + j] = origin[i * n + j];
		}
	}
}

void matrix_multiply(int* matrixA, int* matrixB, int* result, int n)
{
	int* temp = new int[n * n];

	for(int i = 0; i < n * n; i++)
	{
		temp[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				temp[i * n + j] += matrixA[i * n + k] * matrixB[k * n + j];
			}
		}
	}

	matrix_deep_copy(temp, result, n);
}


void matrix_pow(int* matrix, int* result, int pow, int n)
{
	matrix_deep_copy(matrix, result, n);
	
	for(int i = 0; i < pow - 1; i++)
	{
		matrix_multiply(result, matrix, result, n);
	}
}

void matrix_fast_pow(int* matrix, int* result, int pow, int n)
{
	matrix_deep_copy(matrix, result, n);

	int* temp = new int[n * n];

	for(int i = 0; i < n * n; i++)
	{
		if(i % n == i / n)
		{
			temp[i] = 1;
		}
		else
		{
			temp[i] = 0;
		}
	}
	
	if(pow != 0)
	{
		while(pow > 1)
		{
			if(pow % 2 == 0)
			{
				pow = pow / 2;
				matrix_multiply(result, result, result, n);
			}
			else
			{
				pow = pow - 1;
				matrix_multiply(result, temp, temp, n);

				pow = pow / 2;
				matrix_multiply(result, result, result, n);
			}
		}

		matrix_multiply(result, temp, result, n);
	}
	else
	{
		matrix_deep_copy(temp, result, n);
	}
}

void matrix_print(int* matrix, int n)
{
	cout << "Matrix" << endl;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << matrix[i * n + j] << " ";
		}
		cout << endl;
	}
}

