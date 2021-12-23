#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, size, rank1;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Comm_split(MPI_COMM_WORLD, 1, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	printf("color = %d; key = %d; rank = %d; rank1 = %d\n", 1, size - rank, rank, rank1);
	MPI_Comm_free(&comm_revs);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) printf("---------------------------------------\n");
	
	MPI_Comm_split(MPI_COMM_WORLD, rank % 2, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	printf("color = %d; key = %d; rank = %d; rank1 = %d\n", rank % 2, size - rank, rank, rank1);
	MPI_Comm_free(&comm_revs);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) printf("---------------------------------------\n");

	MPI_Comm_split(MPI_COMM_WORLD, rank % 3, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	printf("color = %d; key = %d; rank = %d; rank1 = %d\n", rank % 3, size - rank, rank, rank1);
	MPI_Comm_free(&comm_revs);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) printf("---------------------------------------\n");
	
	MPI_Finalize();
}