#include <graph.h>

Graph::Graph()
{
	e = -1;
	v = -1;
}

Graph::~Graph()
{

}


GraphMatrix::GraphMatrix()
{
	e = -1;
	v = -1;
	matrix = NULL;
}

GraphMatrix::~GraphMatrix()
{

}

void GraphMatrix::print()
{
	for(int i = 0; i < v; i++)
	{
		cout << "vertex " << i << " : ";
		for(int j = 0; j < v; j++)
		{
			if(matrix[i*v+j])
			{
				cout << j << " ";
			}
		}
		cout << endl;
	}
}