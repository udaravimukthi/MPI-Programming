// 174083C_TH2_MPI_Matrix_Matrix_Mul.cpp 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define NCOLS 5

//Print the matrices 
void print_matrix(char* prompt, float matrix[NCOLS][NCOLS]) { 
    printf("\n%s\n", prompt); 
    for (int i = 0; i < NCOLS; i++) {
        for (int j = 0; j < NCOLS; j++) {
            printf(" %g", matrix[i][j]);
        } 
        printf("\n");
    } 
    printf("\n"); 
}

int main(int argc, char** argv) {
    int rank, size, nprocs, root;

    //resulting matrix with computed matrix
    float A[NCOLS][NCOLS],Apart[NCOLS];
    //iitial matrix with received vector
    float B[NCOLS][NCOLS],Bpart[NCOLS];
    //initial matrix2 
    float C[NCOLS][NCOLS];
    //resulting matrix for serial computation
    float A_exact[NCOLS][NCOLS];
    
    root = 1;

    /* Initiate MPI. */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Generate random numbers
    srand(time(NULL));
    for (int row = 0; row < NCOLS; row++) {
        for (int col = 0; col < NCOLS; col++) {
            B[row][col] = rand() % 10;
            C[row][col] = rand() % 5;
        }
    }

    // Scatter matrix B by rows. 
    MPI_Scatter(B, NCOLS, MPI_FLOAT, Bpart, NCOLS, MPI_FLOAT, root, MPI_COMM_WORLD);

    // Do the vector-scalar multiplication. 
    float sum = 0.0; 
    for (int i = 0; i < NCOLS; i++) {
        for (int j = 0; j < NCOLS; j++) {
            sum += Bpart[j] * C[j][i];
        } 
        Apart[i] = sum;
        sum = 0.0;
    }

    MPI_Gather(Apart, NCOLS, MPI_FLOAT, A, NCOLS , MPI_FLOAT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Original Matrixes : \n"); 
        print_matrix((char*)"B = ", B); 
        print_matrix((char*)"C = ", C); 
        
        printf("Parallel result: \n"); 
        print_matrix((char*)"A = ", A); 
        printf("\nSequintial result: \n"); 
        for (int i = 0; i < NCOLS; i++) { 
            for (int j = 0; j < NCOLS; j++) {
                A_exact[i][j] = 0.0;
                for (int k = 0; k < NCOLS; k++){
                    A_exact[i][j] += B[i][k] * C[k][j]; 
                } 
            }
        }
        print_matrix((char*)"A exact = ", A_exact);
    }

    // Put up a barrier until I/O is complete 
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}
