#include <stdio.h>
#include <limits.h>

#define V 100 // Maximum number of vertices

int dist[V];
int prev[V];
int sptSet[V];

void printSolution(int n, int source) {
    printf("Source Destination Cost Path\n");
    for (int v = 1; v <= n; v++) {
        printf("%d %d %d ", source, v, dist[v]);
        printPath(v);
        printf("\n");
    }
}

void printPath(int v) {
    if (prev[v] == -1) {
        printf("%d", v);
        return;
    }
    printPath(prev[v]);
    printf("->%d", v);
}

int minDistance(int dist[], int sptSet[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 1; v <= n; v++) {
        if (sptSet[v] == 0 && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[][V], int n, int source) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        prev[i] = -1;
    }
    dist[source] = 0;
    for (int count = 1; count <= n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
    printSolution(n, source);
}

int main() {
    int n, source;
    int graph[V][V];

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    // Read the graph from the input file
    FILE *fp = fopen("inDiAdjMat1.dat", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }
    fclose(fp);

    dijkstra(graph, n, source);

    return 0;
}