#include <stdio.h>
#include "mpi.h"
#define BUFSIZE 100
#include <fstream>

using namespace std;

void writeFile(const char* text) {
	ofstream outfile("file.txt");
	outfile << text;
	outfile.close();
}

int main(int argc, char **argv)
{
	int bufsize, num, sum;
	
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_File fh;
	
	char buf[BUFSIZE];
	
	writeFile("my name is Jotaro Kujo\n");
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//print the number of read symbols sum from the file
	printf("Number of read symbols : %d\n", sum);
	remove("file.txt");
	MPI_Finalize();
}
