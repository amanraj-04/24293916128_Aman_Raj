#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Binary Search function
int binary_search(int arr[], int size, int target) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

// Function to generate random numbers
void generateRandomArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        array[i] = rand() % 100000;
}

int main() {
    int input_size[8] = {10, 50, 100, 1000, 3000, 5000, 7000, 10000};

    for (int i = 0; i < 8; i++) {
        int size = input_size[i];
        int array[size];

        double total_time = 0;
        int iterations = 1000;

        for (int iter = 0; iter < iterations; iter++) {
            generateRandomArray(array, size);
            int target = rand() % 100000;

            clock_t start = clock();
            binary_search(array, size, target);
            clock_t end = clock();

            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        printf("Size: %d, Total time (1000 searches): %lf seconds\n", size, total_time);
    }

    return 0;
}
