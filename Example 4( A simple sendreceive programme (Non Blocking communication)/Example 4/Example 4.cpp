// Example 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[])
{
	int myid, numprocs;
	int tag, source, destination, count;
	int buffer;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	tag = 1234;
	source = 0;
	destination = 1;
	count = 1;
	request = MPI_REQUEST_NULL;

	if (myid == source) {
		buffer = 5678;
		MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request);
	}

	if (myid == destination) {
		MPI_Irecv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &request);
		printf("processor %d got %d\n", myid, buffer);
	}
	MPI_Wait(&request, &status);
	if (myid == source) {
		printf("processor %d sent %d\n", myid, buffer);
	}
	if (myid == destination) {
		printf("processor %d got %d\n", myid, buffer);
	}

	// Finalize the MPI environment.
	MPI_Finalize();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
