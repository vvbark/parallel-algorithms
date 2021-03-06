#include <iostream>
#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
	if (rank == 2) // the number of my task
	{
		cout << "Receaving from process " << rank << "\n";
		for (int i = 0; i < n - 1; i++) {
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
					MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Hello from process --- " << message << endl;
		}
	}
	
	if (rank != 2) // root process
		MPI_Send(&rank, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		// there are we send from main process the message 
		// (rank) to the process '2'
		
	MPI_Finalize();
	return 0;
}