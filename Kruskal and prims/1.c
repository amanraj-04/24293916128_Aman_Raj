#include <stdio.h>
#include <limits.h>

#define MAX 100

// Function to find the vertex with minimum key value
int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the MST
void printMST(int parent[], int graph[MAX][MAX], int V) {
    int total_weight = 0;
    printf("Prim's MST Edges:\n");
    for (int i = 1; i < V; i++) {
        printf("Edge: (%d -- %d)  Weight = %d\n", parent[i], i, graph[i][parent[i]]);
        total_weight += graph[i][parent[i]];
    }
    printf("\nTotal MST Weight: %d\n", total_weight);
}

// Prim's Algorithm (Adjacency Matrix)
void primMST(int graph[MAX][MAX], int V) {
    int parent[MAX]; // Stores MST
    int key[MAX];    // Key values to pick minimum edge
    int mstSet[MAX]; // To track included vertices

    // Initialize all keys as infinite
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Take vertex 0 as starting node
    key[0] = 0;
    parent[0] = -1;

    // Construct MST with V-1 edges
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;

        // Update key values of adjacent vertices of u
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

int main() {
    int V = 5;

    int graph[MAX][MAX] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph, V);

    return 0;
}