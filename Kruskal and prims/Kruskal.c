#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

typedef struct {
    int src, dest, weight;
} Edge;

// Disjoint Set Union Arrays
int parent[MAX_VERTICES];
int rank[MAX_VERTICES]; // Used for Union by Rank optimization

// initialised the set
void initialise_set(int V) {
    for (int i = 0; i < V; i++) {
        parent[i] = i; // Every vertex is its own parent
        rank[i] = 0;   // Initial rank is 0
    }
}


int find_set(int i) {
    if (parent[i] == i){
        return i;
    }
    return parent[i] = find_set(parent[i]);   // Path Compression to make the current node point directly to the root
}


void union_sets(int i, int j) {
    int root_1 = find_set(i);
    int root_2 = find_set(j);

    if (root_1 != root_2) {
        // taking Union by Rank by Attaching the smaller rank tree under the root of the higher rank tree
        if (rank[root_1] < rank[root_2]) {
            parent[root_1] = root_2;
        } else if (rank[root_1] > rank[root_2]) {
            parent[root_2] = root_1;
        } else {
            // If ranks are equal then choose one as parent and increment its rank
            parent[root_2] = root_1;
            rank[root_1]++;
        }
    }
}

// function to compare edges
int compare_edges(const* a, const* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}


//Kruskals Algorithum
void kruskalMST(int V, int E, Edge edge_list[]) {
    Edge MST[V - 1]; // has V-1 edges
    int mst_edge_count = 0;
    int mst_total_weight = 0;

    // Sorting edges by weight
    qsort(edge_list, E, sizeof(Edge), compare_edges);

    // Step 2: Initialise set union
    initialise_set(V);

    printf("Kruskal's MST Edges \n");
    // Iterate through sorted edges (Greedy Choice)
    for (int i = 0; i < E && mst_edge_count < V - 1; i++) {
        int u = edge_list[i].src;
        int v = edge_list[i].dest;
        int w = edge_list[i].weight;

        // Checking if adding this edge creates a cycle
        if (find_set(u) != find_set(v)) {
            // No cycle then Add edge to MST and Union the sets
            MST[mst_edge_count++] = edge_list[i];
            union_sets(u, v);
            mst_total_weight += w;
            printf("Edge %d: (%d -- %d) with weight %d\n", mst_edge_count, u, v, w);
        }
    }

    printf("\nTotal MST Weight: %d\n", mst_total_weight);
}


int main() {
    int V = 4;
    int E = 5;
    
    Edge edge_list[MAX_EDGES] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    
    kruskalMST(V, E, edge_list);
    
    return 0;
}