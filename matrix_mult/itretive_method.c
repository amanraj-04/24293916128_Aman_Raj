#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void itrative_mult(int n, int **arr1, int **arr2, int **arr){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j]=0;
            for (int k = 0; k < n; k++)
            {
                arr[i][j]+=arr1[i][k]*arr2[k][j];
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int n,i,j;
    printf("Enter the size of the matrix");
    scanf("%d",&n);

    int **arr1= (int**)malloc(n*sizeof(int*));
    int **arr2= (int**)malloc(n*sizeof(int*));
    int **arr= (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        arr1[i]=(int*)malloc(n*sizeof(int));
        arr2[i]=(int*)malloc(n*sizeof(int));
        arr[i]=(int*)malloc(n*sizeof(int));
    }
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n; i++)
        {
            arr1[i][j]=rand() % 10;
            arr2[i][j]=rand() % 10;
        }
    }
    
    clock_t start_time = clock();
    itrative_mult(n,arr1,arr2,arr);
    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time for iterative multiplication: %f seconds\n", elapsed_time);

    for (i = 0; i < n; i++) {
        free(arr1[i]);
        free(arr2[i]);
        free(arr[i]);
    }
    free(arr1);
    free(arr2);
    free(arr);

    
    return 0;
}
