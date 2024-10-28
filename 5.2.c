#include <stdio.h>
#include <stdlib.h>

// Define the structure for Huffman tree nodes
struct HuffmanNode {
    char alphabet;
    int frequency;
    struct HuffmanNode *left, *right;
};

// Structure for priority queue (min-heap)
struct PriorityQueue {
    int size;
    int capacity;
    struct HuffmanNode** array;
};

// Create a new Huffman tree node
struct HuffmanNode* createNode(char alphabet, int frequency) {
    struct HuffmanNode* node = (struct HuffmanNode*)malloc(sizeof(struct HuffmanNode));
    node->alphabet = alphabet;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Create a priority queue (min-heap)
struct PriorityQueue* createPriorityQueue(int capacity) {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (struct HuffmanNode**)malloc(queue->capacity * sizeof(struct HuffmanNode*));
    return queue;
}

// Swap two nodes of the priority queue
void swapNodes(struct HuffmanNode** a, struct HuffmanNode** b) {
    struct HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify the priority queue
void minHeapify(struct PriorityQueue* queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size && queue->array[left]->frequency < queue->array[smallest]->frequency)
        smallest = left;
    if (right < queue->size && queue->array[right]->frequency < queue->array[smallest]->frequency)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&queue->array[smallest], &queue->array[idx]);
        minHeapify(queue, smallest);
    }
}

// Check if the size of queue is one
int isSizeOne(struct PriorityQueue* queue) {
    return (queue->size == 1);
}

// Extract the minimum value node from the queue
struct HuffmanNode* extractMin(struct PriorityQueue* queue) {
    struct HuffmanNode* temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    --queue->size;
    minHeapify(queue, 0);
    return temp;
}

// Insert a new node to the priority queue
void insertQueue(struct PriorityQueue* queue, struct HuffmanNode* node) {
    ++queue->size;
    int i = queue->size - 1;
    while (i && node->frequency < queue->array[(i - 1) / 2]->frequency) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}

// Build the Huffman tree
struct HuffmanNode* buildHuffmanTree(char alphabets[], int frequencies[], int size) {
    struct HuffmanNode *left, *right, *top;

    // Create a min-heap (priority queue)
    struct PriorityQueue* queue = createPriorityQueue(size);

    // Insert all characters into the priority queue
    for (int i = 0; i < size; ++i)
        queue->array[i] = createNode(alphabets[i], frequencies[i]);

    queue->size = size;

    // Build the min-heap
    for (int i = (queue->size - 1) / 2; i >= 0; --i)
        minHeapify(queue, i);

    // Iterate while the size of the heap is not 1
    while (!isSizeOne(queue)) {
        // Extract the two nodes with the lowest frequency
        left = extractMin(queue);
        right = extractMin(queue);

        // Create a new internal node with frequency equal to the sum of the two nodes
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // Insert the new node into the priority queue
        insertQueue(queue, top);
    }

    // The remaining node is the root of the Huffman tree
    return extractMin(queue);
}

// In-order traversal of the Huffman tree
void inorderTraversal(struct HuffmanNode* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    if (root->alphabet != '$')
        printf("%c ", root->alphabet);
    inorderTraversal(root->right);
}

int main() {
    int n;

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int frequencies[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &alphabets[i]);
    }

    printf("Enter their frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &frequencies[i]);
    }

    // Build Huffman Tree
    struct HuffmanNode* root = buildHuffmanTree(alphabets, frequencies, n);

    // Perform in-order traversal of the Huffman Tree
    printf("In-order traversal of the Huffman tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}