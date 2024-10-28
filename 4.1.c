#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

// Function to swap two persons
void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// Min-heapify function based on age
void minHeapify(struct person heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].age < heap[smallest].age)
        smallest = left;
    if (right < n && heap[right].age < heap[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// Max-heapify function based on weight
void maxHeapify(struct person heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].weight > heap[largest].weight)
        largest = left;
    if (right < n && heap[right].weight > heap[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

// Function to build a min-heap
void buildMinHeap(struct person heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(heap, n, i);
    }
}

// Function to build a max-heap
void buildMaxHeap(struct person heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, n, i);
    }
}

// Function to read data from file
struct person* readData(int *n) {
    FILE *file = fopen("students.txt", "r");
    if (!file) {
        printf("Unable to open file!\n");
        exit(1);
    }

    fscanf(file, "%d", n);  // Read the number of students
    struct person *students = (struct person*) malloc((*n) * sizeof(struct person));

    for (int i = 0; i < *n; i++) {
        students[i].name = (char*) malloc(100 * sizeof(char));
        fscanf(file, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age, &students[i].height, &students[i].weight);
    }

    fclose(file);
    return students;
}

// Function to insert a new person into the min-heap
struct person* insertPerson(struct person heap[], int *n, struct person newPerson) {
    heap = (struct person*) realloc(heap, (*n + 1) * sizeof(struct person));
    heap[*n] = newPerson;
    int i = *n;
    (*n)++;

    // Heapify-up to maintain min-heap property
    while (i > 0 && heap[(i - 1) / 2].age > heap[i].age) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    return heap;
}

// Function to delete the oldest person from the heap
struct person* deleteOldestPerson(struct person heap[], int *n) {
    if (*n == 0) {
        printf("Heap is empty!\n");
        return heap;
    }

    swap(&heap[0], &heap[*n - 1]);
    (*n)--;
    heap = (struct person*) realloc(heap, (*n) * sizeof(struct person));
    minHeapify(heap, *n, 0);

    return heap;
}

// Function to display the weight of the youngest person
void displayWeightOfYoungest(struct person heap[]) {
    printf("Weight of the youngest person: %.2f kg\n", heap[0].weight * 0.453592);  // Convert from pounds to kg
}

// Function to display the current heap (students)
void displayStudents(struct person heap[], int n) {
    printf("\nCurrent Students Details:\n");
    printf("Id\tName\t\t\tAge\tHeight\tWeight (pounds)\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-20s\t%d\t%d\t%d\n", heap[i].id, heap[i].name, heap[i].age, heap[i].height, heap[i].weight);
    }
}

// Display function for the menu
void displayMenu() {
    printf("\nMAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");
    printf("Enter option: ");
}

// Main function
int main() {
    struct person *students = NULL;
    int n = 0;
    int option;
    
    do {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                students = readData(&n);
                printf("Data read successfully.\n");
                displayStudents(students, n);
                break;
            case 2:
                buildMinHeap(students, n);
                printf("Min-heap created based on age.\n");
                displayStudents(students, n);
                break;
            case 3:
                buildMaxHeap(students, n);
                printf("Max-heap created based on weight.\n");
                displayStudents(students, n);
                break;
            case 4:
                if (n > 0) displayWeightOfYoungest(students);
                else printf("Heap is empty!\n");
                break;
            case 5: {
                struct person newPerson;
                newPerson.name = (char*) malloc(100 * sizeof(char));
                printf("Enter details (id, name, age, height, weight): ");
                scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);
                students = insertPerson(students, &n, newPerson);
                printf("New person inserted into the Min-heap.\n");
                displayStudents(students, n);
                break;
            }
            case 6:
                students = deleteOldestPerson(students, &n);
                printf("Oldest person deleted from the heap.\n");
                displayStudents(students, n);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (option != 7);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(students[i].name);
    }
    free(students);

    return 0;
}