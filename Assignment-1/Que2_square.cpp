//squares of first 100 numbers followed by addition of all these squares
//Author : 2019BTECS00055 
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define THREAD_COUNT 10

int main(int argc, char* argv[]){
	int i=1;
	int sum = 0;
	int square = 0;
	double start = omp_get_wtime();
	omp_set_num_threads(THREAD_COUNT);
	#pragma omp parallel 
	{	
		#pragma omp single
		printf("No. of Threads Allocated : %d \n", omp_get_num_threads());

		#pragma omp for schedule(static, 10)
        for(i=1; i<=100; i++){
			square =  i* i;
		    printf("thread No. %d   Num : %d   square : %d\n", omp_get_thread_num(), i, square);
			sum += square;
        }
	}
	double end = omp_get_wtime();
	double total_time = end - start;

	printf("\nSum of 1-100 squares : %d", sum);
	printf("\nTime taken : %lf\n", total_time);
    return 0;
}


