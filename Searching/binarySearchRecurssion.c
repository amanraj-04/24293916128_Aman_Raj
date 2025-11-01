#include <stdio.h>

int binarySearchRecursive(int arr[], int start, int end, int target) {
    if (start > end) {
        return -1;
    }
    int mid = start + (end - start) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }

    if (target < arr[mid]) {
        return binarySearchRecursive(arr, start, mid - 1, target);
    }

    return binarySearchRecursive(arr, mid + 1, end, target);
}

int main() {
    int n, target;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements (in sorted order): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the element to search: ");
    scanf("%d", &target);
    
    int result = binarySearchRecursive(arr, 0, n - 1, target);
    
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found in the array\n", target);
    }
    
    return 0;
}