#include <iostream>
#include <mpi.h>

#define LENGTH 1'000'000

using namespace std;

void fillArray(int * array, int length)
{
	for (int i = 0; i < length; i++)
		array[i] = 1;
}

int main(int argc, char **argv)
{
	int size, rank, tempSum;
	double start, delta;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
	
	int array[LENGTH];
	
	if (rank == 0) fillArray(array, LENGTH);
			
	if ( LENGTH % size != 0 ) {
		printf("Error. Number of processes must have not the remainder of the division to LENGTH\n");
		return 0;
	}
	
	int subLength = LENGTH / size;
	
	int subArray[subLength];
	
	MPI_Scatter(&array, subLength, MPI_INT, &subArray, subLength, MPI_INT, 0, MPI_COMM_WORLD);
	
	int sum = 0;
	for (int i = 0; i < subLength; i++) sum += subArray[i];
	
	if (rank == 0) start = MPI_Wtime();
		
	for (int order = 2; order <= size; order *= 2)
	{
		// Processes, which rank has non zero reminder when divided by reduce order, sends info to process,\
		// which rank is the result of integer division
		if (rank % order == 0) {
			if (rank + order / 2 < size) { // check if need to receive 
				MPI_Recv(&tempSum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				sum += tempSum;
			}
		}
		else {
			MPI_Send(&sum, 1, MPI_INT, rank - (rank % order), 0, MPI_COMM_WORLD);
			break;
		}
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if (rank == 0) {		
		delta = MPI_Wtime() - start;
		printf("Answer is %d\n", sum);
		printf("Time %.0f ms\n", (delta) * 1'000);
	}


	MPI_Finalize();
	return 0;
}