#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1024
#define FactorIntToDouble 1.1; 

double firstMatrix [N] [N] = {0.0};
double secondMatrix [N] [N] = {0.0};
double matrixMultiResult [N] [N] = {0.0};
int THREADS;

void matrixMulti() {

    #pragma omp parallel for num_threads(THREADS) 
    for(int row = 0 ; row < N ; row++) {
        for(int col = 0; col < N ; col++) {
            double resultValue = 0;
            for(int transNumber = 0 ; transNumber < N ; transNumber++) {
                resultValue += firstMatrix [row] [transNumber] * secondMatrix [transNumber] [col] ;
            }
	    //printf("Thread %d of %d is Adding\n", omp_get_thread_num(), omp_get_num_threads());
            matrixMultiResult [row] [col] = resultValue;
        }
    }

}


void matrixInit() {

    for(int row = 0 ; row < N ; row++ ) {
        for(int col = 0 ; col < N ;col++){
            srand(row+col);
            firstMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
            secondMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
        }
    }
}



int main(int argc, char *argv[])
{
    THREADS = strtol(argv[1], NULL, 10);
    matrixInit();

    clock_t t1 = clock(); 
    matrixMulti();
    clock_t t2 = clock(); 
    printf("opm time: %ld\n", t2-t1);

    return 0;
}
