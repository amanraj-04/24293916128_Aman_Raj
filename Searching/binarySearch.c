#include <stdio.h>

int binarySearch(int arr[], int n, int target){
    int start, end, mid;
    int start = 0;
    int mid = start + (end - start) / 2;
    int length = sizeof(arr)/sizeof(arr[0]);
    int end = arr[length];

    for (int i = 0; i < end; i++)
    {
        if (arr[i]==mid)
        {
            return i;
        }
        else if (arr[i]<arr[mid])
        {
            end = mid-1;
        }
        else {
            start = mid + 1;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int n, target;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the element to search: ");
    scanf("%d", &target);

    binarySearch(arr,n,target);
    return 0;
}
