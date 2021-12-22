#include <stdio.h>
#include "mpi.h"
#define n 1000

void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	int *input = (int*)a;
	int *output = (int*)b;
	for (int i = 0; i < *l; i++)
		output[i] = (input[i] + output[i]) % 5;
}

void maximum(void *a, void *b, int *l, MPI_Datatype *type) {
	int *input = (int*)a;
	int *output = (int*)b;
	for (int i = 0; i < *l; i++)
		if (input[i] > output[i]) output[i] = input[i];
}

int main(int argc, char **argv)
{
	int rank, size;
	int a[n];
	int b[n];
	int b_mpi_max[n];
	int root_rank = 0;
	MPI_Init(&argc, &argv);
	
	MPI_Op op;
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	for (int i = 0; i < n; i++) a[i] = i + rank + 1;
	
	printf("process %d a[0] = %d\n", rank, a[0]);
	
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
	
	MPI_Op_create(&smod5, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , root_rank, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
	
	if (rank == 0) printf("b[0] = %d\n", b[0]);
	
	// MPI_MAX
	MPI_Reduce(a, b_mpi_max, n, MPI_INT, MPI_MAX , root_rank, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
	
	// MAX FUNCTION
	MPI_Op_create(&maximum, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , root_rank, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	
	// PRINTING
	if (rank == 0) 
		printf("\nCustomized maximum : b[0] = %d\nMPI_MAX : b_mpi_max[0] = %d\n", b[0], b_mpi_max[0]);
	
	MPI_Finalize();
}