#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
using namespace std;

#define SIZE 5000
#define FROM_MASTER 4
#define FROM_WORKER 4
#define DEBUG 1 

MPI_Status status;

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

static void init_matrix(void)
{
    int i, j;
    int l = (-SIZE);
    for (i = 0; i < SIZE; i++)
    {
        l = l + SIZE;
        for (j = 0; j < SIZE; j++) {

            a[i][j] = 1;
            b[i][j] = j + l;

        }
    } 
} 

int main(int argc, char** argv)
{
    int buff_ = 1;
    int myrank, nproc;
    int rows;
    int mtype;
    int dest, src, offseta, offsetb;
    double start_time, end_time;
    int i, j, k, l;

    srand(time(NULL));
    setlocale(LC_ALL, "ru");

    const int n = 1000;
    const int m = n;

    long long duration = 0;

    //Созаем матрицу с заданной размерностью 
    auto* matrix = new float[n * m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            matrix[i * m + j] = floor(r * 10000000) / 10000000;
        }
    }
    // Вектор
    float vector[m];
    for (int i = 0; i < m; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vector[i] = floor(r * 10000000) / 10000000;
    }
    // второй вектор
    float vectorNext[n];
    for (int i = 0; i < n; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vectorNext[i] = floor(r * 10000000) / 10000000;
    }


    MPI_Init(&argc, &argv);

    auto startTime = std::chrono::high_resolution_clock::now();

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    rows = SIZE / nproc;
    mtype = FROM_MASTER; 

    if (myrank == 0) {
        printf("SIZE = %d, number of nodes = %d\n", SIZE, nproc);
        init_matrix();

        start_time = MPI_Wtime();

        if (nproc == 1) {
            for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++) {
                    for (k = 0; k < SIZE; k++)
                        c[i][k] = c[i][k] + b[i][j] * a[j][k];
                }
            } 
            end_time = MPI_Wtime();
            printf("Execution time on %2d nodes: %f\n", nproc, end_time -
                start_time);
        }

        else {

            for (l = 0; l < nproc; l++) {
                offsetb = rows * l; 
                offseta = rows;
                mtype = FROM_MASTER; 

                for (dest = 1; dest < nproc; dest++) {
                    MPI_Send(&offseta, buff_, MPI_INT, dest, mtype,
                        MPI_COMM_WORLD);
                    MPI_Send(&offsetb, buff_, MPI_INT, dest, mtype,
                        MPI_COMM_WORLD);
                    MPI_Send(&rows, buff_, MPI_INT, dest, mtype, MPI_COMM_WORLD);
                    MPI_Send(&a[offseta][0], rows * SIZE, MPI_DOUBLE, dest,
                        mtype, MPI_COMM_WORLD);
                    MPI_Send(&b[0][offsetb], rows * SIZE, MPI_DOUBLE, dest,
                        mtype, MPI_COMM_WORLD);

                    offseta += rows;
                    offsetb = (offsetb + rows) % SIZE;
                }

                offseta = rows;
                offsetb = rows * l;

                for (i = 0; i < offseta; i++) {
                    for (j = offsetb; j < offsetb + rows; j++) {
                        for (k = 0; k < SIZE; k++) {
                            c[i][k] = c[i][k] + b[i][j] * a[j][k];
                        }
                    } 
                }
                mtype = FROM_WORKER;
                for (src = 1; src < nproc; src++) {
                    MPI_Recv(&offseta, buff_, MPI_INT, src, mtype, MPI_COMM_WORLD,
                        &status);
                    MPI_Recv(&offsetb, buff_, MPI_INT, src, mtype, MPI_COMM_WORLD,
                        &status);
                    MPI_Recv(&rows, buff_, MPI_INT, src, mtype, MPI_COMM_WORLD,
                        &status);
                    for (i = 0; i < rows; i++) {
                        MPI_Recv(&c[offseta + i][offsetb], offseta, MPI_DOUBLE,
                            src, mtype, MPI_COMM_WORLD, &status);
                    } 
                }
            } 
            end_time = MPI_Wtime();
            printf("Execution time on %2d nodes: %f\n", nproc, end_time - start_time);
        }
    }

    else {
        if (nproc > 1) {
            for (l = 0; l < nproc; l++) {
                mtype = FROM_MASTER;
                MPI_Recv(&offseta, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD,
                    &status);
                MPI_Recv(&offsetb, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD,
                    &status);
                MPI_Recv(&rows, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD,
                    &status);

                MPI_Recv(&a[offseta][0], rows * SIZE, MPI_DOUBLE, 0, mtype,
                    MPI_COMM_WORLD, &status);
                MPI_Recv(&b[0][offsetb], rows * SIZE, MPI_DOUBLE, 0, mtype,
                    MPI_COMM_WORLD, &status);

                for (i = offseta; i < offseta + rows; i++) {
                    for (j = offsetb; j < offsetb + rows; j++) {
                        for (k = 0; k < SIZE; k++) {
                            c[i][k] = c[i][k] + b[i][j] * a[j][k];
                        }
                    }  
                }

                mtype = FROM_WORKER;
                MPI_Send(&offseta, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD);
                MPI_Send(&offsetb, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD);
                MPI_Send(&rows, buff_, MPI_INT, 0, mtype, MPI_COMM_WORLD);
                for (i = 0; i < rows; i++) {
                    MPI_Send(&c[offseta + i][offsetb], offseta, MPI_DOUBLE, 0,
                        mtype, MPI_COMM_WORLD);

                }
            }
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    if (myrank == 0) {
        std::cout << "Execution time (ms): " << (double)duration / 1000 / nproc << std::endl;
        printf("My rank is %d, %d processes in work\n", myrank, nproc);

        string mytime = "Duration " + to_string((double)duration / 1000) + "ms " + "Matrix:" + to_string(SIZE) + "x" + to_string(SIZE) + " Rang: "+ to_string(nproc) +"\n";
        ofstream streamText;
        streamText.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\Time.txt", ofstream::app);
        streamText << mytime;
    }

    MPI_Finalize();
    return 0;
}



