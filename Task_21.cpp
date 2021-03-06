#include <stdio.h>
#include "mpi.h"
#include <fstream>

#define CHAR_NUM 5

using namespace std;

void writeFile(const char* text) {
	ofstream outfile("file1.txt");
	outfile << text;
	outfile.close();
}

int main(int argc, char **argv)
{
	int rank;
	
	writeFile("my name is Jotaro Kujo\n");
	
	MPI_Init(&argc, &argv);
	MPI_File fh;
	
	char buf[CHAR_NUM];
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	
	MPI_File_set_view(fh, rank * CHAR_NUM, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, CHAR_NUM, MPI_CHAR, MPI_STATUS_IGNORE);
	
	printf("process %d, buf=%s\n", rank, buf);
	MPI_File_close(&fh);
	MPI_Finalize();
	
	remove("file1.txt");
	return 0;
}