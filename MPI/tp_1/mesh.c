#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char **argv){
    if (argc != 2){
        perror("Missing Argument !\n");
        exit(1);
    }

    int N = atoi(argv[1]);

    MPI_Init(&argc, &argv);

    MPI_Status status;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int global_mesh[size*N][size*N];
    
    int local_mesh[(size/N)+2][size*N];

    // Master rank cut the mesh & other retrieve it
    if (rank == 0){
        for (int j = 0; j < N / size; j++){
            memcpy(local_mesh[j], global_mesh[j], sizeof(global_mesh[j]));
        }

        for (int i = 1; i < size; i++){
            if (i == size-1){
                int send_mesh[(size/N)+1][N];
                int pos = 0;
                for (int j = 2*N-1; j < N-1; j++){
                    memcpy(send_mesh[pos], global_mesh[j], sizeof(global_mesh[j]));
                    pos++;
                }

                MPI_Send(&send_mesh, (size/N)+2, MPI_INT, i, 0, MPI_COMM_WORLD);
            }else{
                int send_mesh[(size/N)+2][N];

                int pos = 0;
                for (int j = 2*N-1; j < 2*rank+2; j++){
                    memcpy(send_mesh[pos],global_mesh[j], sizeof(global_mesh[j]));
                    pos++;
                }

                MPI_Send(&send_mesh, (size/N)+2, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }else{
        if (rank == size-1) MPI_Recv(&local_mesh, (size/N)+1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        else MPI_Recv(&local_mesh, (size/N)+2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    
}