// Example 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[])
{
	int myid, numprocs;
	MPI_Status status;
	int mytag, ierr, icount, j, * i;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	printf("Hello from c process: %d Numprocs is %d\n", myid, numprocs);

	mytag = 123;

	if (myid == 0) {
		j = 200;
		icount = 1;
		ierr = MPI_Send(&j, icount, MPI_INT, 1, mytag, MPI_COMM_WORLD);
	}

	if (myid == 1) {
		ierr = MPI_Probe(0, mytag, MPI_COMM_WORLD, &status);
		ierr = MPI_Get_count(&status, MPI_INT, &icount);
		i = (int*)malloc(icount * sizeof(int));
		printf("getting %d\n", icount);
		ierr = MPI_Recv(i, icount, MPI_INT, 0, mytag, MPI_COMM_WORLD, &status);
		printf("i=");
		for (j = 0; j < icount; j++);
		printf("%d ", i[j]);
		printf("\n");
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
