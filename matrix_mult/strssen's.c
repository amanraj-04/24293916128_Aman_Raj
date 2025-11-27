#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function for standard matrix addition: C = A + B
void add(int n, int A[][n], int B[][n], int C[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j]; // Element-wise addition
}

// Function for standard matrix subtraction: C = A - B
void subtract(int n, int A[][n], int B[][n], int C[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j]; // Element-wise subtraction
}

// Strassen's algorithm implementation: C = A * B
void strassen(int n, int A[][n], int B[][n], int C[][n])
{
    // Base case: If matrix size is 1x1, perform simple multiplication
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Calculate the size of the sub-matrices
    int mid = n / 2;

    // Allocate memory for 4 quadrants of A, 4 of B, 4 of C, and the 7 recursive products (P..V)
    int A11[mid][mid], A12[mid][mid], A21[mid][mid], A22[mid][mid];
    int B11[mid][mid], B12[mid][mid], B21[mid][mid], B22[mid][mid];
    int C11[mid][mid], C12[mid][mid], C21[mid][mid], C22[mid][mid];
    // P=M1, Q=M2, R=M3, S=M4, T=M5, U=M6, V=M7 (The seven recursive products)
    int P[mid][mid], Q[mid][mid], R[mid][mid], S[mid][mid], T[mid][mid], U[mid][mid], V[mid][mid];
    int T1[mid][mid], T2[mid][mid]; // Temporary matrices for addition/subtraction results

    // Partition A and B into their four n/2 x n/2 sub-matrices
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
        {
            // Top-Left Quadrant
            A11[i][j] = A[i][j];
            B11[i][j] = B[i][j];
            // Top-Right Quadrant
            A12[i][j] = A[i][j + mid];
            B12[i][j] = B[i][j + mid];
            // Bottom-Left Quadrant
            A21[i][j] = A[i + mid][j];
            B21[i][j] = B[i + mid][j];
            // Bottom-Right Quadrant
            A22[i][j] = A[i + mid][j + mid];
            B22[i][j] = B[i + mid][j + mid];
        }

    // --- Calculate the seven products (P to V) recursively ---

    // P (M1) = (A11 + A22) * (B11 + B22)
    add(mid, A11, A22, T1);     // T1 = A11 + A22
    add(mid, B11, B22, T2);     // T2 = B11 + B22
    strassen(mid, T1, T2, P);   // P = T1 * T2 (recursive call)

    // Q (M2) = (A21 + A22) * B11
    add(mid, A21, A22, T1);     // T1 = A21 + A22
    strassen(mid, T1, B11, Q);  // Q = T1 * B11

    // R (M3) = A11 * (B12 - B22)
    subtract(mid, B12, B22, T1); // T1 = B12 - B22
    strassen(mid, A11, T1, R);  // R = A11 * T1

    // S (M4) = A22 * (B21 - B11)
    subtract(mid, B21, B11, T1); // T1 = B21 - B11
    strassen(mid, A22, T1, S);  // S = A22 * T1

    // T (M5) = (A11 + A12) * B22
    add(mid, A11, A12, T1);     // T1 = A11 + A12
    strassen(mid, T1, B22, T);  // T = T1 * B22

    // U (M6) = (A21 - A11) * (B11 + B12)
    subtract(mid, A21, A11, T1); // T1 = A21 - A11
    add(mid, B11, B12, T2);     // T2 = B11 + B12
    strassen(mid, T1, T2, U);   // U = T1 * T2

    // V (M7) = (A12 - A22) * (B21 + B22)
    subtract(mid, A12, A22, T1); // T1 = A12 - A22
    add(mid, B21, B22, T2);     // T2 = B21 + B22
    strassen(mid, T1, T2, V);   // V = T1 * T2

    // --- Calculate the four result quadrants (C11, C12, C21, C22) using P..V ---

    // C11 = P (M1) + S (M4) - T (M5) + V (M7)
    add(mid, P, S, T1);          // T1 = P + S
    subtract(mid, T1, T, T2);    // T2 = T1 - T
    add(mid, T2, V, C11);        // C11 = T2 + V

    // C12 = R (M3) + T (M5)
    add(mid, R, T, C12);

    // C21 = Q (M2) + S (M4)
    add(mid, Q, S, C21);

    // C22 = P (M1) - Q (M2) + R (M3) + U (M6)
    subtract(mid, P, Q, T1);     // T1 = P - Q
    add(mid, T1, R, T2);         // T2 = T1 + R
    add(mid, T2, U, C22);        // C22 = T2 + U

    // Join the four result quadrants (C11, C12, C21, C22) back into the final matrix C
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
        {
            C[i][j] = C11[i][j];             // Place C11 (Top-Left)
            C[i][j + mid] = C12[i][j];       // Place C12 (Top-Right)
            C[i + mid][j] = C21[i][j];       // Place C21 (Bottom-Left)
            C[i + mid][j + mid] = C22[i][j]; // Place C22 (Bottom-Right)
        }
}

int main()
{
    // Initialize random seed for random matrix generation
    srand(time(NULL));
    
    // Open file to write execution times
    FILE *fp = fopen("strassen.txt", "w");
    if (!fp)
        return 1; // Exit if file cannot be opened

    // Array of matrix sizes to test (must be powers of 2 for this version)
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256};
    int num = sizeof(sizes) / sizeof(sizes[0]);
    int trials = 5; // Number of times to run each size for averaging

    for (int s = 0; s < num; s++)
    {
        int n = sizes[s];
        // Allocate dynamic memory for the n x n matrices A, B, and C (using VLA syntax with malloc)
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));
        if (!A || !B || !C) // Check for failed allocation
            continue;

        double total = 0.0;
        
        // Run multiple trials to get a stable time average
        for (int t = 0; t < trials; t++)
        {
            // Initialize matrices A and B with random values (0-9)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    A[i][j] = rand() % 10;
                    B[i][j] = rand() % 10;
                }
            
            // Start timing
            clock_t start = clock();
            strassen(n, A, B, C); // Run Strassen's multiplication
            clock_t end = clock();
            
            // Accumulate total time in seconds
            total += (double)(end - start) / CLOCKS_PER_SEC;
        }
        
        // Calculate and print the average time
        double avg = total / trials;
        printf("%d x %d -> %.9f sec\n", n, n, avg);
        
        // Write the size and average time to the file
        fprintf(fp, "%d %.9f\n", n, avg);
        
        // Free dynamically allocated memory
        free(A);
        free(B);
        free(C);
    }
    fclose(fp); // Close the file
    return 0;
}
