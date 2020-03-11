#include "readgraph.h"

// read text graph to adjacency matrix
GraphMatrix* gtom(char* path)
{
	GraphMatrix* g = new GraphMatrix();
	int token = 0;
	int index = 0;

	ifstream input;
	input.open(path);
	getline(input, g->name);
	input >> g->v;

	g->matrix = new int[g->v * g->v];

	for(int i = 0; i < g->v; i++)
	{
		g->matrix[i] = 0;
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

			g->matrix[index * g->v + token] = 1;
			g->matrix[token * g->v + index] = 1;

			input >> token;
		}
	}

	input.close();

	return g;
}