#include <stdio.h>
#include <stdlib.h>
int worst_case_count = 0; // Counter for worst-case scenarios
int best_case_count = 0;
int comparisions=0;
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
  
    // Choose the pivot
    int pivot = arr[high];
  
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        comparisions++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);

    if (i == low - 1) { // Worst case: pivot is the smallest element
        worst_case_count++;
    } else if (i == high - 1) { // Best case: pivot is the largest element
        best_case_count++;
    }
    
    return i + 1;
}

// The QuickSort function implementation
void quickSort(int arr[], int low, int high) {
  
    if (low < high) {
      
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main() {
    printf("1.Ascending Data\n");
    printf("2.Descending Data\n");
    printf("3.Random Data\n");
    printf("4.Exit\n");
    printf("Enter choice: ");
    int ch;
    scanf("%d", &ch);
    if(ch>=4)
    return 0;
    FILE *f,*q;
    char ch1[20], ch2[20];
    printf("Enter source text file name: ");
    scanf("%s", ch1);
    printf("Enter destination text file name: ");
    scanf("%s", ch2);
    f=fopen(ch1,"r");
    if (f == NULL) {
        printf("Error opening %s\n", ch1);
        return 1; // Indicate an error
    }
    printf("The file %s is now opened.\n", ch1);
    q=fopen(ch2,"w");
    if (q == NULL) {
        printf("Error opening %s\n", ch2);
        fclose(q);
        return 1; // Indicate an error
    }
    int num;
    switch (ch)
    {
    case 1:
    {
        int arr[100]; // Assuming a maximum of 100 numbers
        int i=0;
        while (fscanf(f,"%d",&num)==1)
        {
            arr[i]=num;
            i++;
        }
        quickSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        printf("Worst-case scenarios: %d\n", worst_case_count);
        printf("Best-case scenarios: %d\n", best_case_count);
        comparisions=0;
        worst_case_count = 0;
        best_case_count = 0;
        break;
    }
    case 2:
    {
        int arr[100]; // Assuming a maximum of 100 numbers
        int i=0;
        while (fscanf(f,"%d",&num)==1)
        {
            arr[i]=num;
            i++;
        }
        quickSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file in descending order
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        printf("Worst-case scenarios: %d\n", worst_case_count);
        printf("Best-case scenarios: %d\n", best_case_count);
        comparisions=0;
        worst_case_count = 0;
        best_case_count = 0;
        break;
    }
    case 3:
    {
        int arr[100]; // Assuming a maximum of 100 numbers
        int i=0;
        while (fscanf(f,"%d",&num)==1)
        {
            arr[i]=num;
            i++;
        }
        quickSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file in descending order
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        printf("Worst-case scenarios: %d\n", worst_case_count);
        printf("Best-case scenarios: %d\n", best_case_count);
        comparisions=0;
        worst_case_count = 0;
        best_case_count = 0;
        break;
    }
    }
    fclose(f);
    fclose(q);
    return 0;
}