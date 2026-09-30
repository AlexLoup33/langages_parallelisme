#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    int buffer_size = 10;
    
    if (argc == 2){
        buffer_size = atoi(argv[1]);
    }
    int buffer[buffer_size];

    MPI_Status status;
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        for (int i; i < buffer_size; i++){
            buffer[i] = i;
        }

        MPI_Bcast(&buffer, buffer_size, MPI_INT, rank, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&buffer, buffer_size, MPI_INT, 0, MPI_COMM_WORLD);

        printf("Rank %d received the buffer\nDisplay tab received :\n", rank);
        for (int i = 0; i < buffer_size; i++){
            printf("Rank: %d | tab[%i] = %d\n", rank, i, buffer[i]);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}