#include <cstdlib>
#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, size;
	double startTime, delta;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int matrixSize = 500;
	
	int A[matrixSize][matrixSize], 
		B[matrixSize][matrixSize],
		C[matrixSize][matrixSize];
		
//matrix initialization by each process
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			C[i][j] = 0;
			A[i][j] = rand();
			B[i][j] = rand();
		}
	}

	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
	
// start timing for each process
	startTime = MPI_Wtime();
	
// matrix multiplication
	for (int i = 0; i < matrixSize; i++)
	    for (int j = 0; j < matrixSize; j++)
	        for (int k = 0; k < matrixSize; k++)
	            C[i][j] += A[i][k] * B[k][j];

// end of timing
	delta = MPI_Wtime() - startTime;
	
// output the execution time of matrix multiplication at each process
	printf("Process %d spent %f seconds\n", rank, delta);
	
	MPI_Finalize();
}