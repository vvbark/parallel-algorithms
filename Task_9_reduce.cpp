#include <iostream>
#include <mpi.h>

#define LENGTH 1'000'000

using namespace std;

void fillArray(int * array, int length)
{
	for (int i = 0; i < length; i++)
		array[i] = 1;
}

void displayArray(int * array, int length)
{
	for (int i = 0; i < length; i++)
		printf("%d ", array[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	int size, rank;
	double start, delta;
	int subLength;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
	
	int array[LENGTH];
	
	if (rank == 0) {
		
		fillArray(array, LENGTH);
	}
	
	if ( LENGTH % size == 0 ) {
		
		subLength = LENGTH / size;
		
	} else {
		printf("Error. Number of processes must have not the remainder of the division to LENGTH\n");
		return 0;
	}

	int subArray[subLength];
	
	MPI_Scatter(&array, subLength, MPI_INT, &subArray, subLength, MPI_INT, 0, MPI_COMM_WORLD);
	
	int sum = 0, sum_final;
	
	for (int i = 0; i < subLength; i++) 
		sum += subArray[i];

	if (rank == 0) 
		start = MPI_Wtime();
	
	MPI_Reduce(&sum, &sum_final, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		delta = MPI_Wtime() - start;
		printf("Answer is %d\n", sum_final);
		printf("Time %.0f ms\n", (delta) * 1'000);
	}

	MPI_Finalize();
	return 0;
}