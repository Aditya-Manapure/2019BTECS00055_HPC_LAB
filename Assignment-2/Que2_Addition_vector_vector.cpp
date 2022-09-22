//Implement a parallel code for vector-vector addition
//Author : 2019BTECS00055 Aditya Manapure

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define THREAD_COUNT 8
#define ARRAY_SIZE 100
#define COUNT_PER_THREAD ARRAY_SIZE/THREAD_COUNT


int main(){
    
    int A[ARRAY_SIZE], B[ARRAY_SIZE], C[ARRAY_SIZE];

    for(int i=0; i<ARRAY_SIZE; i++){
        A[i] = i;
        B[i] = i;
    }

    omp_set_num_threads(THREAD_COUNT);
    int i=0;
    double start = omp_get_wtime();
    #pragma omp parallel 
    {
        
        #pragma omp single
            printf("Number of threds Allocated %d\n", omp_get_num_threads());

        #pragma omp single   
            printf("Processing Data ... ");
        
        #pragma omp for
        for(i=0; i<ARRAY_SIZE; i++){
            printf("\n Thread id %d is proccessing on index %d\n", omp_get_thread_num(), i);
            C[i] = A[i] + B[i];
        }
        

        #pragma omp barrier

        #pragma omp single nowait
            printf("Displaying Data ... ");
        
        #pragma omp for
        for(i=0; i<ARRAY_SIZE; i++){
            printf("\n Thread id %d is printing on index %d : %d + %d = %d", omp_get_thread_num(), i,  A[i], B[i], C[i]);
        }
        
    }
    double end = omp_get_wtime();
	double total_time = end - start;
	printf("\n\nTime taken : %lf\n", total_time);
    
    return 0; 
}