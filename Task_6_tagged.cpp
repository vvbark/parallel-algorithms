#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, ibuf;
	MPI_Status status;
	float rbuf;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	ibuf = rank;
	rbuf = 1.0 * rank;
	
	if (rank == 1) MPI_Send(&ibuf, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
	if (rank == 2) MPI_Send(&rbuf, 1, MPI_FLOAT, 0, 10, MPI_COMM_WORLD);
	
	if (rank == 0) {
		for (int i = 0; i < 2; i++) {
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			
			if (status.MPI_SOURCE == 1) 
				MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
			if (status.MPI_SOURCE == 2)
				MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 10, MPI_COMM_WORLD, &status);
		}
		cout << "Process 0 recv " << ibuf << " from process 1, " << rbuf << " from process 2\n";
	}
	MPI_Finalize();
}