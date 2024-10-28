#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

// Find the subset of an element i using path compression
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union of two sets by rank
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Compare two edges based on weight, for qsort
int compare(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Function to print the MST and its total cost
void printMST(struct Edge result[], int e) {
    int totalCost = 0;
    
    printf("Edge \tCost\n");
    for (int i = 0; i < e; i++) {
        printf("%d--%d \t%d\n", result[i].src + 1, result[i].dest + 1, result[i].weight);
        totalCost += result[i].weight;
    }
    
    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

// Function to apply Kruskal's algorithm to find MST
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[MAX]; // Store the resultant MST
    int e = 0; // Initial number of edges in the result
    int i = 0; // Initial index for sorted edges
    
    // Sort edges by increasing order of weight
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compare);
    
    // Allocate memory for creating subsets
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));
    
    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Number of edges in the MST will be V-1
    while (e < V - 1 && i < graph->E) {
        // Pick the smallest edge
        struct Edge nextEdge = graph->edges[i++];
        
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);
        
        // If this edge doesn't cause a cycle, include it in the result
        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }
    
    // Print the result
    printMST(result, e);
    
    // Free allocated memory for subsets
    free(subsets);
}

int main() {
    int V, E;
    
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    struct Graph* graph = createGraph(V, E);
    
    printf("Enter the edges (u v w) with their weights:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
        // Adjust indices for 0-based array indexing
        graph->edges[i].src--;
        graph->edges[i].dest--;
    }
    
    // Apply Kruskal's algorithm
    KruskalMST(graph);
    
    // Free allocated memory for graph
    free(graph->edges);
    free(graph);
    
    return 0;
}