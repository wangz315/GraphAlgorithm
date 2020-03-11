#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "mpi.h"
#include "gcolor.h"


// read the graph from txt file to adjacency matrix
int* readgraph(int* v)
{
	int* adjmatrix;
	char* filename = "G.txt";
	char line[256];
	int token, index, n;
	char *split;

	FILE *file = fopen(filename, "r");

	if(file != NULL)
	{
		// remove graph name
		fgets(line, sizeof(line), file);
		// get graph size
		n = atoi(fgets(line, sizeof(line), file));
		*v = n;
		// set adj matrix
		adjmatrix = (int*) malloc(n * n * sizeof(int));
		// init graph
		for(int i = 0; i < n*n; i++) adjmatrix[i] = 0;
		// next line
		while(fgets(line, sizeof(line), file))
		{
			// split line
			split = strtok(line, " ");
			token = atoi(split);
			index = -1 * token;
			index--;

			split = strtok(NULL, " ");
			while(split != NULL)
			{
				token = atoi(split);
				token--;

				adjmatrix[token*n+index] = 1;
				adjmatrix[index*n+token] = 1;

				split = strtok(NULL, " ");
			}
		}
	}
	else
	{
		printf("%s does not exist\n", filename);
	}

	fclose(file);

	return adjmatrix;
}


int main(int argc, char *argv[])
{
	int my_rank;
    int num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	// omp_set_num_threads(2);

	int k; // k color
	int* adjmatrix = NULL;
	int n; // graph size
	double t1, t2, t3, t4, t5;

	// only one p read graph
	if(!my_rank)
	{
		printf("computing graph k-colorability\n");

		t1 = MPI_Wtime();
		adjmatrix = readgraph(&n);
		t2 = MPI_Wtime();

		printf("read graph time: \t\t%f\n", t2 - t1);
	}
		
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int size = pow(2, n);
	int* table = (int*) malloc(sizeof(int) * size); // every p needs a copy of table

	if(!my_rank)
	{

		t3 = MPI_Wtime();
		printf("bcast table time \t\t%f\n", t3 - t2);

		compute_table_omp(adjmatrix, n, table, size);
		t4 = MPI_Wtime();

		printf("compute table time \t\t%f\n", t4 - t3);
		// k = binary_search(adjmatrix, n, table, size, 0, n);
	}


	MPI_Bcast(table, size, MPI_INT, 0, MPI_COMM_WORLD);
	int start = my_rank * size / num_procs;
	int message = -1;
	int recvmessage[num_procs];

	for(int i = start; i < size / num_procs; i++)
	{
		long long value = 0l;

		if(i < size)
			value = gcolor_2_omp(adjmatrix, n, table, i, size);

		if(value > 0)
		{
			message = i;
			break;
		}

	}


	MPI_Gather(&message, 1, MPI_INT, recvmessage, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(!my_rank)
	{
		t5 = MPI_Wtime();

		printf("find k time \t\t\t%f\n", t5 - t4);

		for(int i = 0; i < num_procs; i++)
		{
			if(recvmessage[i] > 0)
				k = recvmessage[i];
		}
		
		printf("total time: \t\t\t%f\n", t5 - t1);
		printf("graph is %d-colorable\n", k);
	}
	

	MPI_Finalize();
	return EXIT_SUCCESS;
}



















