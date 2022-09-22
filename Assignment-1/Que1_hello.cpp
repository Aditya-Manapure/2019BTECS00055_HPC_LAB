//Hello World using OpenMP
//Author : Aditya Manapure
//2019BTECS00055

#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define THREAD_COUNT 8

int main(){

	double start = omp_get_wtime();		// start time
	omp_set_num_threads(THREAD_COUNT);  // fixing number of threads 
	#pragma omp parallel
	{
		printf("thread No. %d  Hello World\n", omp_get_thread_num());
	}
	double end = omp_get_wtime();
	double total_time = end - start;
	printf("Time taken : %lf\n", total_time);
    return 0;

}