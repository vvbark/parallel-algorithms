#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	int size, rank, position, i;
	float a[10];
	char b[10], buf[100];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 10; i++) {
		a[i] = rank + 1.0;
		if (rank == 0) b[i] = 'a';
		else b[i] = 'b';
	}
	position = 0;
	if (rank == 0) {
		
		printf("rank = %d\n", rank);
		for (int i = 0; i < 10; i++) 
			printf("a[%d]=%f ", i, a[i]);
		printf("\n");
		for (int i = 0; i < 10; i++) 
			printf("b[%i]=%c ", i, b[i]);
		printf("\n-----------------------\n");
		
		MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
	}
	else {
		if (rank == 1) {
			printf("BEFORE UNPACK\n");
			printf("rank = %d\n", rank);
			for (int i = 0; i < 10; i++) 
				printf("a[%d]=%f ", i, a[i]);
			printf("\n");
			for (int i = 0; i < 10; i++) 
				printf("b[%i]=%c ", i, b[i]);
			printf("\n-----------------------\n");
		}
		
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
		position = 0;
		MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
		
		if (rank == 1) {
			printf("AFTER UNPACK\n");
			printf("rank = %d\n", rank);
			for (int i = 0; i < 10; i++) 
				printf("a[%d]=%f ", i, a[i]);
			printf("\n");
			for (int i = 0; i < 10; i++) 
				printf("b[%i]=%c ", i, b[i]);
			printf("\n-----------------------\n");
		}
	}
	
	MPI_Finalize();
}