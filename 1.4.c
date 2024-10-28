#include <stdio.h>


void EXCHANGE(int *arr, int p, int q) {
    int temp = arr[p];
    arr[p] = arr[q];
    arr[q] = temp;
}


void ROTATE_RIGHT(int *arr, int p2) {
    if (p2 <= 1) {
        return;  
    }

    int last = arr[p2 - 1]; 

    
    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(arr, i, i - 1);
    }
    arr[0] = last;  
}


void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int p2 = 3;  

    printf("Original array:\n");
    printArray(arr, 5);

    ROTATE_RIGHT(arr, p2);

    printf("Array after rotation:\n");
    printArray(arr, 5);

    return 0;
}