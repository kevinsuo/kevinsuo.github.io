#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
        clock_gettime(CLOCK_MONOTONIC, &start);
        quickSort(data, 0, count - 1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        u_int64_t diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

//      printArray(data, count);

        fclose(fp);

        return 0;
}