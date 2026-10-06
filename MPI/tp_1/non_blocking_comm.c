#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char **argv){
    MPI_Status status;

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buffer_Sr0[10];
    int buffer_Rr0[10];

    int buffer_Sr1[10];
    int buffer_Rr1[10];

    if (rank == 0){
        for (int i = 0; i < 10; i++) buffer_Sr0[i] = i*2;

        MPI_Sendrecv(&buffer_Sr0, 10, MPI_INT, 1, 0, &buffer_Rr0, 10, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
    }else{
        for (int i = 0; i < 10; i++) buffer_Sr1[i] = i*3;

        MPI_Sendrecv(&buffer_Sr1, 10, MPI_INT, 0, 0, &buffer_Rr1, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    printf("Rank %d finished the task !\n", rank);

    MPI_Finalize();
    return EXIT_SUCCESS;
}