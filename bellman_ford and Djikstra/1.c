#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5
#define E 8

typedef struct {
    int src, dest, weight;
} Edge;

void printSol(int dest[]) {
    printf("\nVertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dest[i] == INT_MAX) {
            printf("%d \t Unreachable\n", i);
        } else {
            printf("%d \t %d\n", i, dest[i]);
        }
    }
}

void bellman_ford(Edge edges[], int src) {
    int dest[V];
    
    for (int i = 0; i < V; i++) {
        dest[i] = INT_MAX;
    }
    dest[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dest[u] != INT_MAX && dest[u] + w < dest[v]) {
                dest[v] = dest[u] + w;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dest[u] != INT_MAX && dest[u] + w < dest[v]) {
            printf("\nGraph contains a negative weight cycle! Cannot find shortest paths.");
            return;
        }
    }

    printSol(dest);
}


int main() {
    
    Edge edge_list[E] = {
        {0, 1, -1}, 
        {0, 2, 4},  
        {1, 2, 3},  
        {1, 3, 2},  
        {1, 4, 2},  
        {3, 2, 5},  
        {3, 1, 1},  
        {4, 3, -3}  
    };
    
    int source_vertex = 0;
    
    printf("--- Bellman-Ford Algorithm ---\n");
    printf("Graph Vertices (V): %d, Edges (E): %d, Source: %d\n", V, E, source_vertex);
    
    bellman_ford(edge_list, source_vertex);
    
    return 0;
}