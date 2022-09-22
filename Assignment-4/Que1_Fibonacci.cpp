//Fibonacci Computation
//Author : 2019BTECS00055 Aditya Manapure
#include<stdio.h>
#include<omp.h>

#define THREAD_COUNT 8

int fib(int n)
{
    int i, j;
    if (n < 2)
        return n;
    else
    {
        #pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1);

        #pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}


int main ()

{
	int n = 10;
    double start = omp_get_wtime();		

    //omp_set_dynamic(0);
	omp_set_num_threads(THREAD_COUNT);   
	#pragma omp parallel shared(n)
	{
		#pragma omp single
		printf("fib(%d) = %d\n", n, fib(n));
	}
    double end = omp_get_wtime();
	double total_time = end - start;
    printf("\nExecution Time : %lf\n", total_time);
    return 0;
}



