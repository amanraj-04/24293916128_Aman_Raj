#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int knapsack(int W, int n, int profits[], int weights[])
{
    int **table = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
    {
        table[i] = (int *)malloc((W + 1) * sizeof(int));
    }
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                table[i][w] = 0;
            else if (weights[i - 1] <= w)
            {
                table[i][w] = max(profits[i - 1] + table[i - 1][w - weights[i - 1]], table[i - 1][w]);
            }
            else
                table[i][w] = table[i - 1][w];
        }
    }
    int result = table[n][W];
    for (int i = 0; i <= n; i++)
    {
        free(table[i]);
    }
    free(table);
    return result;
}
void generateRandomArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        array[i] = rand() % 100000;
}
int avg(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += array[i];
    return sum /= size;
}
int main()
{
    int input_size[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    for (int i = 0; i < 10; i++)
    {
        int size = input_size[i];
        int profits[size];
        int weights[size];
        int capacity;
        double total_time = 0;
        int iterations = 1000;
        for (int iter = 0; iter < iterations; iter++)
        {
            generateRandomArray(profits, size);
            generateRandomArray(weights, size);
            capacity = avg(weights, size);
            clock_t start = clock();
            knapsack(capacity, size, profits, weights);
            clock_t end = clock();
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Size: %d, Total time: %lf seconds\n", size, total_time);
    }
    return 0;
}