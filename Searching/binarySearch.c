#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Correct compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Binary Search function
int binary_search(int *arr, int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (key == arr[mid]) {
            return mid;
        } else if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

// Function to generate random array
void random_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0–999
    }
}

int main() {
    int n, key, pos;
    printf("Enter the number of elements you want in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    // Generate random numbers
    random_array(arr, n);

    // Input element to search
    printf("Enter the element you want to search: ");
    scanf("%d", &key);

    // Sort array before applying binary search
    qsort(arr, n, sizeof(int), compare);

    // Measure time for 10000 searches
    clock_t start = clock();
    for (int i = 0; i < 10000; i++) {
        pos = binary_search(arr, n, key);
    }
    clock_t end = clock();

    // Print search result
    if (pos != -1) {
        printf("Element found at index %d\n", pos);
    } else {
        printf("Element not found.\n");
    }

    // Time calculation (average per search)
    double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    double avg_time = total_time / 10000.0;

    printf("Total time for 10000 searches: %f seconds\n", total_time);
    printf("Average time per search: %f seconds\n", avg_time);

    free(arr);
    return 0;
}
