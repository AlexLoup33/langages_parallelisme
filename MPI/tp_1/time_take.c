#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv){
    
    int message_size = 10;
    if (argc == 2){
	    message_size = atoi(argv[1]);
    }
    int tab[message_size];

    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
   
    double start_time;

    if (rank == 0){
        start_time = MPI_Wtime();

        for (int i = 0; i < message_size; i++){
            tab[i] = i;
        }

        MPI_Send(&tab, message_size, MPI_INT, 1, 0, MPI_COMM_WORLD);

	    MPI_Recv(&tab, message_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

        printf("Send second tab modified by %d\n", rank);
        for (int i = 0; i < message_size; i++){
            printf("%d\n", tab[i]);
        }

        double end_time = MPI_Wtime();
        printf("Time to process message size (%d) communications : %f seconds\n", message_size, end_time-start_time);
    }else{
        MPI_Recv(&tab, message_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        
        printf("Send first tab from rank %d\n", rank);
        for (int i = 0; i < message_size; i++){
            printf("%d\n", tab[i]);
        }

	for (int i = 0; i < message_size; i++){
            tab[i] = tab[i] * 4;
        }

        MPI_Send(&tab, message_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
