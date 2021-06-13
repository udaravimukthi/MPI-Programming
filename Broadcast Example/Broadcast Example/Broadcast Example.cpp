// Broadcast Example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <mpi.h>
#include <stdio.h>
#include <iostream>  

using namespace std;


int main(int argc, char** argv)
{
	char buff[128];
	int secret_num;

	int numprocs;
	int myid;
	int i;

	MPI_Status stat;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	// ------------------------------------------
	// Node 0 obtains the secret number
	// ------------------------------------------
	if (myid == 0)
	{
		if (argc > 1) {
			secret_num = atoi(argv[1]);
		}

	}

	// ------------------------------------------
	// Node 0 shares the secret with everybody
	// ------------------------------------------
	MPI_Bcast(&secret_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (myid == 0)
	{
		for (i = 1; i < numprocs; i++)
		{
			MPI_Recv(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD, &stat);
			//cout << buff << endl;
			cout << sizeof(buff) << endl;
			//printf(sizeof(buff));
		}
	}
	else
	{
		int x = sizeof(buff);
		//printf(buff,"Processor %d knows the secret code: %d",myid, secret_num);
		printf("Processor %d knows the secret code: %d", myid, secret_num);
		MPI_Send(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

}