#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_matrix(int n,int** arr1, int** arr2, int** arr){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j]=arr1[i][j]+arr2[i][j];
        }
    }
}

void add_matrix(int n,int** arr1, int** arr2, int** arr){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j]=arr1[i][j]-arr2[i][j];
        }
    }
}

// Function to copy a sub-matrix from a larger matrix
void copy_part(int n, int** from, int** to, int row_offset, int col_offset){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            to[i][j]= from[i+row_offset][j+col_offset];
        }
    }
}

// Function to join a sub-matrix to a larger matrix
void join_part(int n, int** from, int** to, int row_offset, int col_offset){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            to[i+row_offset][j+col_offset]=from[i][j];
        }
    }
}

void mult_recursivly(int n,int** arr1, int** arr2, int** arr){
    if (n==1)
    {
        arr[0][0]=arr1[0][0]*arr2[0][0];
        return;
    }

    int sub_size = n/2;

    // Dynamically allocate memory for the 8 sub-matrices
    int** A11 = (int**)malloc(sub_size * sizeof(int*));
    int** A12 = (int**)malloc(sub_size * sizeof(int*));
    int** A21 = (int**)malloc(sub_size * sizeof(int*));
    int** A22 = (int**)malloc(sub_size * sizeof(int*));
    int** B11 = (int**)malloc(sub_size * sizeof(int*));
    int** B12 = (int**)malloc(sub_size * sizeof(int*));
    int** B21 = (int**)malloc(sub_size * sizeof(int*));
    int** B22 = (int**)malloc(sub_size * sizeof(int*));
    int** C11 = (int**)malloc(sub_size * sizeof(int*));
    int** C12 = (int**)malloc(sub_size * sizeof(int*));
    int** C21 = (int**)malloc(sub_size * sizeof(int*));
    int** C22 = (int**)malloc(sub_size * sizeof(int*));
    
    // Allocate memory for each row of the sub-matrices
    for (int i = 0; i < sub_size; i++) {
        A11[i] = (int*)malloc(sub_size * sizeof(int));
        A12[i] = (int*)malloc(sub_size * sizeof(int));
        A21[i] = (int*)malloc(sub_size * sizeof(int));
        A22[i] = (int*)malloc(sub_size * sizeof(int));
        B11[i] = (int*)malloc(sub_size * sizeof(int));
        B12[i] = (int*)malloc(sub_size * sizeof(int));
        B21[i] = (int*)malloc(sub_size * sizeof(int));
        B22[i] = (int*)malloc(sub_size * sizeof(int));
        C11[i] = (int*)malloc(sub_size * sizeof(int));
        C12[i] = (int*)malloc(sub_size * sizeof(int));
        C21[i] = (int*)malloc(sub_size * sizeof(int));
        C22[i] = (int*)malloc(sub_size * sizeof(int));
    }

    // Partition matrices A and B into their four sub-matrices
    copy_part(n,arr1,A11,0,0);
    copy_part(n,arr1,A12,0,sub_size);
    copy_part(n,arr1,A21,sub_size,0);
    copy_part(n,arr1,A22,sub_size,sub_size);

    copy_part(n,arr2,B11,0,0);
    copy_part(n,arr2,B12,0,sub_size);
    copy_part(n,arr2,B21,sub_size,0);
    copy_part(n,arr2,B22,sub_size,sub_size);

    // Perform the 8 recursive multiplications for a naive divide and conquer
    // P1 = A11 * B11
    int** P1 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P1[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A11, B11, P1);

    // P2 = A12 * B21
    int** P2 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P2[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A12, B21, P2);

    // P3 = A11 * B12
    int** P3 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P3[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A11, B12, P3);

    // P4 = A12 * B22
    int** P4 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P4[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A12, B22, P4);

    // P5 = A21 * B11
    int** P5 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P5[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A21, B11, P5);

    // P6 = A22 * B21
    int** P6 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P6[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A22, B21, P6);

    // P7 = A21 * B12
    int** P7 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P7[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A21, B12, P7);

    // P8 = A22 * B22
    int** P8 = (int**)malloc(sub_size * sizeof(int*));
    for (int i = 0; i < sub_size; i++){
        P8[i] = (int*)malloc(sub_size * sizeof(int));
    }
    multiply_recursive(sub_size, A22, B22, P8);

    // Calculate the four resulting sub-matrices
    // C11 = P1 + P2
    add_matrix(sub_size, P1, P2, C11);

    // C12 = P3 + P4
    add_matrix(sub_size, P3, P4, C12);

    // C21 = P5 + P6
    add_matrix(sub_size, P5, P6, C21);

    // C22 = P7 + P8
    add_matrix(sub_size, P7, P8, C22);

    // Join the four sub-matrices into the final result matrix C
    join_part(sub_size, C11, arr, 0, 0);
    join_part(sub_size, C12, arr, 0, sub_size);
    join_part(sub_size, C21, arr, sub_size, 0);
    join_part(sub_size, C22, arr, sub_size, sub_size);

    // Free the dynamically allocated memory for all temporary matrices
    for (int i = 0; i < sub_size; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(C11[i]); free(C12[i]); free(C21[i]); free(C22[i]);
        free(P1[i]); free(P2[i]); free(P3[i]); free(P4[i]);
        free(P5[i]); free(P6[i]); free(P7[i]); free(P8[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
    free(P1); free(P2); free(P3); free(P4);
    free(P5); free(P6); free(P7); free(P8);
}

int main() {
    int n, i, j;
    printf("Enter the size of the square matrices (n, must be a power of 2): ");
    scanf("%d", &n);

    // Check if n is a power of 2
    if ((n & (n - 1)) != 0 && n != 1) {
        printf("Error: Matrix size must be a power of 2 for this algorithm\n");
        return 1;
    }

    // Dynamically allocate memory for the main matrices
    int** arr1 = (int**)malloc(n * sizeof(int*));
    int** arr2 = (int**)malloc(n * sizeof(int*));
    int** arr = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        arr1[i] = (int*)malloc(n * sizeof(int));
        arr2[i] = (int*)malloc(n * sizeof(int));
        arr[i] = (int*)malloc(n * sizeof(int));
    }

    // Initialize matrices with some values for demonstration
    srand(time(0));
    printf("\nMatrix A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            arr1[i][j] = rand() % 10;
            printf("%d\t", arr1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            arr2[i][j] = rand() % 10;
            printf("%d\t", arr2[i][j]);
        }
        printf("\n");
    }

    // Call the recursive multiplication function
    multiply_recursive(n, arr1, arr2, arr);

    printf("\nResultant Matrix C:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    // Free all dynamically allocated memory to prevent memory leaks
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