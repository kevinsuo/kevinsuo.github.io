#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
#define NUMSTEPS 1000000

int main() {
        int i;
        double x, pi, sum, local_x;
        int my_rank, num_procs;
        double mypi;
        int proc_len;
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        int n = NUMSTEPS;
        struct timespec start, end;

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
        MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
        MPI_Get_processor_name(processor_name,&proc_len);

        clock_gettime(CLOCK_MONOTONIC, &start);

        //boardcast value n to all threads
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        sum = 0.0;
        double step = 1.0/(double) NUMSTEPS;

        local_x = 0.5 * step;
        for (i=my_rank;i<= n; i+=num_procs){   //each process jumps num_procs steps, calculate its local size
                local_x += step * num_procs;
                sum += 4.0/(1.0+local_x * local_x);
        }
        mypi = step * sum;   //mypi is the result of one process
        //dest_process is 0, which is responsible to add all mypis into pi
        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        clock_gettime(CLOCK_MONOTONIC, &end);
        u_int64_t diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

        MPI_Finalize();

        if(my_rank==0) {
                printf("PI is %.20f\n",pi);
                printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
        }

        return 0;
}