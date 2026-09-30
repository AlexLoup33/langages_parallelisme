#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, size;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    time_t time_value; 
    MPI_Status status;

    if (rank == 0){
        time_value = time(NULL);
        MPI_Send(&time_value, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD);
    } else if (rank == size-1){
        MPI_Recv(&time_value, 1, MPI_LONG, rank-1, 0, MPI_COMM_WORLD, &status);
        printf("Last rank get the time %l\n", ctime(&time_value));
    } else {
        MPI_Recv(&time_value, 1, MPI_LONG, rank-1, 0, MPI_COMM_WORLD, &status);

        printf("Rank %d received the hour and transfer it !\n", rank);

        MPI_Send(&time_value, 1, MPI_LONG, rank+1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}