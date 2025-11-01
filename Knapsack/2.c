#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    int profit;
    int weight;
    float ratio;
} Item;

int compare(const void *a, const void *b)
{
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemA->ratio < itemB->ratio)
        return 1;
    if (itemA->ratio > itemB->ratio)
        return -1;
    return 0;
}
float knapsack(int capacity, int n, int profits[], int weights[])
{
    Item items[n];
    for (int i = 0; i < n; i++)
    {
        items[i].profit = profits[i];
        items[i].weight = weights[i];
        items[i].ratio = (float)profits[i] / weights[i];
    }
    qsort(items, n, sizeof(Item), compare);
    int currentWeight = 0;
    float finalProfit = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (currentWeight + items[i].weight <= capacity)
        {
            currentWeight += items[i].weight;
            finalProfit += items[i].profit;
        }
        else
        {
            int remainingCapacity = capacity - currentWeight;
            finalProfit += items[i].profit * ((float)remainingCapacity / items[i].weight);
            break;
        }
    }

    return finalProfit;
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
    int input_size[10] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
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