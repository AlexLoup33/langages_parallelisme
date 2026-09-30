#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank % 2 == 0)
        printf("I'm an even rank at rank %d\n", rank);
    else printf("I'm an odd rank at rank %d\n", rank);
    MPI_Finalize();
    return EXIT_SUCCESS;
}