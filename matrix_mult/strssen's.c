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

void strassen(int n, int** arr1, int** arr2, int** arr) {
    // Base case: If the matrix is 1x1, perform a simple multiplication
    if (n == 1) {
        arr[0][0] = arr1[0][0] * arr2[0][0];
        return;
    }

    int sub_size = n / 2;
    
    // Dynamically allocate memory for the sub-matrices and temporary product matrices
    // A, B, C are partitioned into four sub-matrices each (A11, A12, etc.)
    // M1 to M7 are the seven temporary product matrices for Strassen's algorithm
    int** A11 = (int**)malloc(sub_size * sizeof(int*));
    int** A12 = (int**)malloc(sub_size * sizeof(int*));
    int** A21 = (int**)malloc(sub_size * sizeof(int*));
    int** A22 = (int**)malloc(sub_size * sizeof(int*));
    int** B11 = (int**)malloc(sub_size * sizeof(int*));
    int** B12 = (int**)malloc(sub_size * sizeof(int*));
    int** B21 = (int**)malloc(sub_size * sizeof(int*));
    int** B22 = (int**)malloc(sub_size * sizeof(int*));
    int** M1 = (int**)malloc(sub_size * sizeof(int*));
    int** M2 = (int**)malloc(sub_size * sizeof(int*));
    int** M3 = (int**)malloc(sub_size * sizeof(int*));
    int** M4 = (int**)malloc(sub_size * sizeof(int*));
    int** M5 = (int**)malloc(sub_size * sizeof(int*));
    int** M6 = (int**)malloc(sub_size * sizeof(int*));
    int** M7 = (int**)malloc(sub_size * sizeof(int*));
    int** temp1 = (int**)malloc(sub_size * sizeof(int*));
    int** temp2 = (int**)malloc(sub_size * sizeof(int*));

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
        M1[i] = (int*)malloc(sub_size * sizeof(int));
        M2[i] = (int*)malloc(sub_size * sizeof(int));
        M3[i] = (int*)malloc(sub_size * sizeof(int));
        M4[i] = (int*)malloc(sub_size * sizeof(int));
        M5[i] = (int*)malloc(sub_size * sizeof(int));
        M6[i] = (int*)malloc(sub_size * sizeof(int));
        M7[i] = (int*)malloc(sub_size * sizeof(int));
        temp1[i] = (int*)malloc(sub_size * sizeof(int));
        temp2[i] = (int*)malloc(sub_size * sizeof(int));
    }

    // Partition the main matrices A and B into their four sub-matrices
    copy_part(sub_size, arr1, A11, 0, 0);
    copy_part(sub_size, arr1, A12, 0, sub_size);
    copy_part(sub_size, arr1, A21, sub_size, 0);
    copy_part(sub_size, arr1, A22, sub_size, sub_size);

    copy_part(sub_size, arr2, B11, 0, 0);
    copy_part(sub_size, arr2, B12, 0, sub_size);
    copy_part(sub_size, arr2, B21, sub_size, 0);
    copy_part(sub_size, arr2, B22, sub_size, sub_size);

    // Calculate the seven products M1 to M7 using recursive calls
    // M1 = (A11 + A22) * (B11 + B22)
    add_matrix(sub_size, A11, A22, temp1);
    add_matrix(sub_size, B11, B22, temp2);
    strassen(sub_size, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    add_matrix(sub_size, A21, A22, temp1);
    strassen(sub_size, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract_matrix(sub_size, B12, B22, temp1);
    strassen(sub_size, A11, temp1, M3);

    // M4 = A22 * (B21 - B11)
    subtract_matrix(sub_size, B21, B11, temp1);
    strassen(sub_size, A22, temp1, M4);

    // M5 = (A11 + A12) * B22
    add_matrix(sub_size, A11, A12, temp1);
    strassen(sub_size, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract_matrix(sub_size, A21, A11, temp1);
    add_matrix(sub_size, B11, B12, temp2);
    strassen(sub_size, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract_matrix(sub_size, A12, A22, temp1);
    add_matrix(sub_size, B21, B22, temp2);
    strassen(sub_size, temp1, temp2, M7);

    // Calculate the four resulting sub-matrices C11, C12, C21, C22
    // C11 = M1 + M4 - M5 + M7
    add_matrix(sub_size, M1, M4, temp1);
    subtract_matrix(sub_size, temp1, M5, temp2);
    add_matrix(sub_size, temp2, M7, A11); // Reuse A11 as a temporary storage for C11
    
    // C12 = M3 + M5
    add_matrix(sub_size, M3, M5, A12); // Reuse A12 for C12
    
    // C21 = M2 + M4
    add_matrix(sub_size, M2, M4, A21); // Reuse A21 for C21

    // C22 = M1 - M2 + M3 + M6
    subtract_matrix(sub_size, M1, M2, temp1);
    add_matrix(sub_size, temp1, M3, temp2);
    add_matrix(sub_size, temp2, M6, A22); // Reuse A22 for C22

    // Join the four result sub-matrices into the final matrix C
    join_part(sub_size, A11, arr, 0, 0);
    join_part(sub_size, A12, arr, 0, sub_size);
    join_part(sub_size, A21, arr, sub_size, 0);
    join_part(sub_size, A22, arr, sub_size, sub_size);

    // Free the dynamically allocated memory for all temporary matrices to prevent leaks
    for (int i = 0; i < sub_size; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]);
        free(M5[i]); free(M6[i]); free(M7[i]);
        free(temp1[i]); free(temp2[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2); free(M3); free(M4);
    free(M5); free(M6); free(M7);
    free(temp1); free(temp2);
}


