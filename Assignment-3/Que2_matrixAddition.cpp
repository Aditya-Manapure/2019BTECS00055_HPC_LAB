#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define THREAD_COUNT 8
#define ARRAY_SIZE 8
#define COUNT_PER_THREAD ARRAY_SIZE/THREAD_COUNT

void display(int arr[ARRAY_SIZE][ARRAY_SIZE])
{
    for(int i=0; i<ARRAY_SIZE; i++){
        for(int j=0; j<ARRAY_SIZE; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}


int main(){
    int i, j;
    int A[ARRAY_SIZE][ARRAY_SIZE], B[ARRAY_SIZE][ARRAY_SIZE], C[ARRAY_SIZE][ARRAY_SIZE];

    double start = omp_get_wtime();
    #pragma omp parallel shared(A, B, C) private(i, j)
    {
        #pragma omp for
        for(i=0; i<ARRAY_SIZE; i++)
        {
            for(j=0; j<ARRAY_SIZE; j++)
            {
                A[i][j] = i+j;
                B[i][j] = i+j;
            }
        }

        for(i=0; i<ARRAY_SIZE; i++)
        {
            for(j=0; j<ARRAY_SIZE; j++)
            {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }
    double end = omp_get_wtime();
	double total_time = end - start;

    printf("\n----------Matrix A-------------\n");
    display(A);

    printf("\n----------Matrix B-------------\n");
    display(B);

    printf("\n----------Sum Matrix C-------------\n");
    display(C);

	printf("Time taken for matrix size %d * %d with thread count %d is : %lf\n",ARRAY_SIZE, ARRAY_SIZE, THREAD_COUNT, total_time);
    return 0;
}