#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, start, stop, sum = 0;
	int size_of_vectors = 1'000'000;
	int array1[size_of_vectors],
		array2[size_of_vectors];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
	
	if (rank == 0) {
		for (int i = 0; i < size_of_vectors; i++) {
			array1[i] = 1;
			array2[i] = 1;
		}
		
		start = 0;
		stop = start + size_of_vectors / size + size_of_vectors % size;
		
		for (int i = 1; i < size; i++) {
			start = stop;
			stop = min(start + size_of_vectors / size, size_of_vectors);
			
			MPI_Send(&array1[start], stop - start, MPI_INT, i, 1, MPI_COMM_WORLD);
			MPI_Send(&array2[start], stop - start, MPI_INT, i, 2, MPI_COMM_WORLD);
		}
		
		int temp_sum = 0;
		
		start = 0;
		stop = start + size_of_vectors / size + size_of_vectors % size;
		
		for (int i = start; i < stop; i++) 
			sum += (array1[i] * array1[i]);
						
		for (int i = 1; i < size; i++) {
			MPI_Recv(&temp_sum, size_of_vectors / size, MPI_INT, i, 3, MPI_COMM_WORLD, &status);
			sum += temp_sum;
		}
		
		printf("sum = %d\n", sum);
	}
	
	else {			
	
		MPI_Recv(&array1, size_of_vectors / size, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&array2, size_of_vectors / size, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		
		for (int i = 0; i < size_of_vectors / size; i++)
			sum += (array1[i] * array2[i]);
		
		MPI_Send(&sum, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
	}
	
	//printf("%d / %d\n", rank, size);
	
	MPI_Finalize();
}
