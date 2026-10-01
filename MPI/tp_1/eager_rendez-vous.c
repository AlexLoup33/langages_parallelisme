#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char **argv){
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    FILE *f = NULL;

    if (rank == 0){
        f = fopen("eager_rendez-vous_latence.txt", "w");
        
        if (f == NULL){
            perror("fopen");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        printf("File correctly loaded !\n");
        fprintf(f, "message_size,time_seconds\n");  
    }
    
    for (int i = 2048; i < 32768; i += 64){
        int buffer[i];
        
        if (rank == 0){
            for (int j = 0; j < i; j++){
                buffer[j] = j;
            }

            double time_start = MPI_Wtime();

            MPI_Send(&buffer, i, MPI_INT, 1, 0, MPI_COMM_WORLD);

            double time_end = MPI_Wtime();
            double latency = time_end - time_start;

            char latency_buffer[20];

            fprintf(f, "%d,%.9f\n", i, latency);
        }else{
            MPI_Recv(&buffer, i, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }
    }
    
    if (rank == 0) fclose(f);

    MPI_Finalize();
    return EXIT_SUCCESS;
}