#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<conio.h>

#define THREAD_COUNT 10
#define ARRAY_SIZE 100
#define N_PER_THREAD ARRAY_SIZE/THREAD_COUNT


int sort(int arr[], int n) 
{
    int i, j;

    printf("\n------Ascending sorting------");
    #pragma omp parallel 
    {
        #pragma omp for 
        for (i = 0; i < n-1; i++){
            for (j = 0; j < n-i-1; j++){
                if (arr[j] > arr[j+1]){
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
            
        }
    }
     
}

int sort_des(int arr[], int n)
{
    int i,j;

    printf("\n------Descending sorting------");
    #pragma omp parallel
    {
        #pragma omp for
        for (i = 0; i < n; ++i){
            for (j = i + 1; j < n; ++j){
                if (arr[i] < arr[j]){
                    int a = arr[i];
                    arr[i] = arr[j];
                    arr[j] = a;
                }
            }
            
        }
    }
}

void display(int arr[], int n)
{
    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
}

int main()
{
    int arr1[ARRAY_SIZE], arr2[ARRAY_SIZE];
    int i;
    
    printf("\n--------------Array_1_input-------------");
    #pragma omp parallel
    for(i = 1; i <= ARRAY_SIZE; i++){
        arr1[i] = 1 + (rand() % ARRAY_SIZE);
        printf("\nThread no. %d taking input of %d at index %d", omp_get_thread_num(), arr1[i], i);
    }
    
    printf("\n--------------Array_2_input-------------");
    #pragma omp parallel for
    for(i = 1; i <= ARRAY_SIZE ; i++){
        arr2[i] = 1 + (rand() % ARRAY_SIZE);
        printf("\nThread no. %d taking input of %d at index %d", omp_get_thread_num(), arr2[i], i);
    }

    sort(arr1, ARRAY_SIZE);
    printf("\n\nSorted Array : \n");
    display(arr1, ARRAY_SIZE);


    sort_des(arr2, ARRAY_SIZE);
    printf("\n\nDescending Sorted Array : \n");
    display(arr2, ARRAY_SIZE);

    int sum = 0;

    #pragma omp parallel reduction(+: sum) shared(arr1, arr2)
    {
        for(i = 0; i < ARRAY_SIZE ; i++){
            sum += (arr1[i] * arr2[i]);
        }
    }
    
    printf("\nSum : %d",sum);
    return 0;
}