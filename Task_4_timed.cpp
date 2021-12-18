#include <iostream>
#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	
	int rank, n, i, message, len;
	char *name = new char;
	double time_start, time_finish;
	
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &len);
	
	time_start = MPI_Wtime(); // start time
	
	if (rank == 2) // the number of my task
	{
		cout << "Receaving from process " << rank << "\n";
		MPI_Recv(&message, 1, MPI_INT, 0,
				MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << "Hello from process --- " << message << endl;
	}
	
	if (rank == 0) // root process
		MPI_Send(&rank, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		// there are we send from main process the message 
		// (rank) to the process '2'
		
	time_finish = MPI_Wtime();	
	
	cout << "processor " << name << ", process " << rank << " time = " << (time_finish - time_start) << endl;

	MPI_Finalize();
	return 0;
}