#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int r;
	
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	
	MPI_Open_port(MPI_INFO_NULL, port_name);
	printf("portname: %s\n", port_name);
	printf("Waiting for a client...\n");
	
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("Client connected\n");
	
	int s = 256;
	MPI_Send(&s, 1, MPI_INT, 0, 10, intercomm);
	printf("Server sent %d value to client\n", s);
	
	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	printf("Server recieved %d from client\n", r);
	
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	
	MPI_Finalize();
	return 0;
}