#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define THREAD_COUNT 4
#define SIZE 200
#define N_THREAD SIZE/THREAD_COUNT

void display(int arr[]){
    for(int i=0; i<SIZE; i++){
        printf("%d ", arr[i]);
    }
}

int main(){
    int i;
    int scalar = 20;
    int vector[SIZE];

    omp_set_num_threads(THREAD_COUNT);
    double start = omp_get_wtime();
    #pragma omp parallel 
    {

        #pragma omp single
        printf("\n---------Vector Input-------------\n\n");

        #pragma omp for schedule(static, N_THREAD) 
        for(i=0; i<SIZE; i++){
            vector[i] = i;
            printf("\nThread No : %d is accessing on index %d", omp_get_thread_num(), i);
        }
        #pragma omp barrier

        #pragma omp single     
        printf("\n\n\n--------Vector Scalar Addition-------\n\n");

        #pragma omp for schedule(static, N_THREAD)
        for(i=0; i<SIZE; i++){ 
            vector[i] += scalar;
            printf("\nThread No : %d is accessing on index %d", omp_get_thread_num(), i);
        }
    }    
    double end = omp_get_wtime();
    // printf("\n------Resultant Vector-----\n");
    // display(vector);
    printf("\nTotal Time : %lf", end-start);
    return 0;
}