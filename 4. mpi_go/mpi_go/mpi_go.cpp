#include <cstdio>
#include "mpi.h"


int main(int *argc, char **argv)
{
    //std::cout << "Hello World!\n";
    int numtasks, rank;

    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("My rank is %d, %d processes in work\n", rank, numtasks);

    MPI_Finalize();

    return 0;
}






