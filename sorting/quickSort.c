#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // random numbers in [0, 9999]
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 5000) {
        printf("Please enter a value greater than 5000\n");
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    clock_t start, end;
    double total_time = 0.0;

    for (int t = 0; t < 1000; t++) {
        generateRandomArray(arr, n);

        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();

        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    double average_time = total_time / 1000.0;
    printf("\nTime taken by QuickSort for %d elements: %f seconds\n", n, average_time);

    free(arr);
    return 0;
}
