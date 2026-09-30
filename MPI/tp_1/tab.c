#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    int tab[10];
    int rank, size;

    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        for (int i = 0; i < 10; i++){
            tab[i] = i;
        }

        MPI_Send(&tab, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&tab, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < 10; i++){
            printf("%d\n", tab[i]);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
