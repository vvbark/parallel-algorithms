#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, r;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
	
	strcpy(port_name, argv[1]);
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("Client connected with server above %s port\n", port_name);
	
	MPI_Recv(&r, 1, MPI_INT, 0, 10, intercomm, &status);
	printf("Client recieved %d value from server\n", r);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Send(&rank, 1, MPI_INT, 0, 0, intercomm);
	printf("Client sent %d value to server\n", rank);
	
	MPI_Finalize();
	return 0;
}