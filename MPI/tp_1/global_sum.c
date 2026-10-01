#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    MPI_Status status;
    
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    printf("Size %d and Rank %d initialized !\n", size, rank);

    int sum = 0;

    int buffer[size];

    // Compute the sum
    for (int i = 0; i < size; i++){
        if (i != rank){
            sum += i;
        }
    }
    buffer[rank] = sum;

    // Every rank broadcast his result
    for (int i = 0; i < size; i++){
        int ret = sum;
        if (i == rank) MPI_Bcast(&sum, 1, MPI_INT, i, MPI_COMM_WORLD);
        else MPI_Bcast(&ret, 1, MPI_INT, i, MPI_COMM_WORLD);

        buffer[i] = ret;
    }
    printf("Rank %d had finished to process !\n", rank);

    if (rank == 0){
        for (int i = 0; i < size; i++){
            printf("tab[%d] = %d\n", i, buffer[i]);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}