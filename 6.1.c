#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX // Define infinity as the maximum integer value

// Function to find the vertex with minimum key value
int minKey(int key[], bool mstSet[], int V) {
    int min = INF, minIndex;
    
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    
    return minIndex;
}

// Function to print the adjacency matrix of the MST
void printMST(int parent[], int graph[100][100], int V) {
    int totalCost = 0;
    int mstAdjMatrix[100][100] = {0}; // Adjacency matrix of the MST
    
    printf("Minimum Spanning Tree (Adjacency Matrix):\n");
    for (int i = 1; i < V; i++) {
        mstAdjMatrix[parent[i]][i] = graph[i][parent[i]];
        mstAdjMatrix[i][parent[i]] = graph[i][parent[i]];
        totalCost += graph[i][parent[i]];
    }
    
    // Print the MST adjacency matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", mstAdjMatrix[i][j]);
        }
        printf("\n");
    }
    
    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

// Function to implement Prim's algorithm
void primMST(int graph[100][100], int V, int startVertex) {
    int parent[100];  // Array to store constructed MST
    int key[100];     // Key values to pick minimum weight edge
    bool mstSet[100]; // To represent set of vertices included in MST
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }
    
    // Start from the given vertex
    key[startVertex] = 0;
    parent[startVertex] = -1; // First node is the root of the MST
    
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);
        
        mstSet[u] = true; // Add the picked vertex to the MST
        
        // Update the key values and parent index of the adjacent vertices
        for (int v = 0; v < V; v++) {
            // Update key if graph[u][v] is smaller than key[v] and v is not in MST
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    // Print the MST adjacency matrix and total cost
    printMST(parent, graph, V);
}

int main() {
    int V, startVertex;
    int graph[100][100];
    FILE *inputFile;
    
    // Read the input adjacency matrix from file
    inputFile = fopen("inUnAdjMat.dat", "r");
    
    if (!inputFile) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }
    
    printf("Enter the Number of Vertices: ");
    scanf("%d", &V);
    
    printf("Enter the Starting Vertex: ");
    scanf("%d", &startVertex);
    startVertex--; // To handle 1-based index from user
    
    // Read the cost adjacency matrix from the file
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(inputFile, "%d", &graph[i][j]);
        }
    }
    
    fclose(inputFile);
    
    // Apply Prim's algorithm
    primMST(graph, V, startVertex);
    
    return 0;
}