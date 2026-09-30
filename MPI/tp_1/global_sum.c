#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    MPI_Status status;
    
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int sum = 0;

    int buffer[size];

    // Compute the sum
    for (int i = 0; i < size; i++){
        if (i != rank){
            sum += i;
        }

        buffer[rank] = sum;
    }

    for (int i = 0; i < size; i++){
        int ret;

        if (i != rank){
            MPI_Sendrecv(&sum, 1, MPI_INT, i, rank, &ret, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);

            buffer[i] = ret;
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}