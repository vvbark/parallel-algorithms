#include <iostream>
#include <mpi.h>

#define MAX_L 1'000'000
#define B_TO_MB 0.000001

using namespace std;

int main(int argc, char **argv)
{	
	int size, rank, averaging = 10000, step = 10;;
	
	unsigned long long L = 1;
	double time_start, delta;
	int dataElems, data[MAX_L];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
		
	if (rank == 0) {
				
		while (L < MAX_L) {
			
			time_start = MPI_Wtime();
						
			for (int i = 0; i < averaging; i++) {
				MPI_Send(&data, L, MPI_INT, 1, 5, MPI_COMM_WORLD);
				MPI_Recv(&data, L, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
			}
			
			delta = MPI_Wtime() - time_start;
			
			printf("The package %f Mb was cicled for %f seconds; Mb/s is %f\n", 
					L * B_TO_MB * sizeof(int), delta, 
					2 * averaging * L * B_TO_MB * sizeof(int) / delta);
			L *= step;
		}
				
		time_start = MPI_Wtime();
					
		for (int i = 0; i < averaging; i++) {
			MPI_Send(&data, 0, MPI_INT, 1, 5, MPI_COMM_WORLD);
			MPI_Recv(&data, 0, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
		}
		
		delta = MPI_Wtime() - time_start;
		
		printf("\nLatency is %f/ N (N = 1'000)\n", delta / 2);

		MPI_Send(&rank, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
	}
	
	if (rank == 1) {
		while (true) {
			
			MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			if ( status.MPI_TAG == 15 ) break;
			
			MPI_Get_count( &status, MPI_INT, &dataElems );
			
			MPI_Recv(&data, dataElems, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
			MPI_Send(&data, dataElems, MPI_INT, 0, 10, MPI_COMM_WORLD);	
			}
		}
	
	MPI_Finalize();
}
