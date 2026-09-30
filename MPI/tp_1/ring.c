#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

int main(int argc, char** argv){
    bool visited = false;
    bool end_of_ring = false;

    int rank, size;
    
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int token;

    if (rank == 0){
        while (! end_of_ring){
            if (visited){
                MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
                printf("End of the ring with token value : %d !\n", token);
                end_of_ring = true;
            } else {
                token = rank;
                
                MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                visited = true;
            }
        }
    } else {
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
            
        token += rank;
    
        if (rank == size-1){
            MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else {
            MPI_Send(&token, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;
}
