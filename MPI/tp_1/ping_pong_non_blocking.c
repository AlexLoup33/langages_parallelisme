#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

int main(int argc, char **argv){
    MPI_Request req[2];
    MPI_Status status[2];

    int buffer_size = 10;

    if (argc == 2){
        buffer_size = atoi(argv[1]);
    }

    bool comm_before = false;
    if (argc == 3){
        buffer_size = atoi(argv[1]);

        bool comm_before = strcmp(argv[2], "true");
    }

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    int s_buffer[buffer_size];
    int r_buffer[buffer_size];
    
    for (int i = 0; i < buffer_size; i++) s_buffer[i] = i;
    
    int dest;
    int src;

    if (rank == size -1) dest = 0;
    else dest = rank+1;
    
    if (rank == 0) src = size-1;
    else src = rank -1;
    
    if (comm_before){
        if (rank == 0) printf("comm_before initialized");

        char s = 's';
        char r;

        MPI_Isend(&s, 1, MPI_CHAR, dest, 0, MPI_COMM_WORLD, &req[0]);
        MPI_Irecv(&r, 1, MPI_CHAR, src, 0, MPI_COMM_WORLD, &req[1]);
        MPI_Waitall(2, req, status);
    }
    double start = MPI_Wtime();

    MPI_Isend(&s_buffer, buffer_size, MPI_INT, dest, 0, MPI_COMM_WORLD, &req[0]);

    MPI_Irecv(&r_buffer, buffer_size, MPI_INT, src, 0, MPI_COMM_WORLD, &req[1]);

    MPI_Waitall(2, req, status);

    printf("Rank %d finished his tasks !\n", rank);
    printf("Time for comm in seconds for rank %d : %.9f\n", rank, MPI_Wtime() - start);

    MPI_Finalize();
    return EXIT_SUCCESS;
}