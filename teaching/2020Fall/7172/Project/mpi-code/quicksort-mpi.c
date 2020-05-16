#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

int data[1000000];

void swap(int* a, int* b)
{
        int t = *a; *a = *b; *b = t;
}

int partition (int arr[], int low, int high)
{
        int pivot = arr[high];          // pivot
        int i = (low - 1);              // Index of smaller element

        for (int j = low; j <= high- 1; j++)
        {
                if (arr[j] < pivot)
                {
                        i++;    // increment index of smaller element
                        swap(&arr[i], &arr[j]);
                }
        }
        swap(&arr[i + 1], &arr[high]);
        return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
        if (low < high)
        {
                int pi = partition(arr, low, high);
                quickSort(arr, low, pi - 1);
                quickSort(arr, pi + 1, high);
        }
}

void printArray(int arr[], int size)
{
        int i;
        for (i=0; i < size; i++)
                printf("%d\n", arr[i]);
}

int main()
{
        //read the unsorted array
        char str[100];
        int count = 0;
        struct timespec start, end;
        FILE* fp = fopen("data.txt", "r");
        while (fscanf(fp, "%s", str) != EOF) {
                data[count] = atoi(str);
                count++;
        }
        //quick sort the array

        int rank, size;
        MPI_Init(NULL, NULL);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);
        MPI_Comm_size (MPI_COMM_WORLD, &size);
        MPI_Status status;

        if (rank == 0) {   //process 0 is responsible for receiving data
                for (int i=1; i<size; i++)
                        MPI_Recv(data+i*count/size, count/size, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        } else {           //other processes are responsible for sending data, the amount for each process is count/size
                MPI_Send(data, count/size,  MPI_INT,  0,  0,  MPI_COMM_WORLD);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);

        int pivot;
        int localDataSize =  count;
        for (int s=size; s > 1; s /= 2) {
                if (rank % s == 0) {
                        pivot = partition(data, 0, localDataSize);
                        MPI_Send(data + pivot, localDataSize - pivot, MPI_INT, rank + s/2, 0, MPI_COMM_WORLD);
                        localDataSize = pivot;
                } else if (rank % s == s/2) {
                        MPI_Recv(data,  count,  MPI_INT,  rank - s/2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                        MPI_Get_count(&status,  MPI_INT, &localDataSize);
                }
        }
        quickSort(data, 0, localDataSize);
        clock_gettime(CLOCK_MONOTONIC, &end);

        MPI_Finalize();

        if (rank == 0 ) {
                u_int64_t diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
                printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
        }
//      printArray(data, count);

        fclose(fp);

        return 0;
}
