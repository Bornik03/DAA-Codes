#include <stdio.h>
#include <stdlib.h>
int comparisions=0;
void merge(int arr[], int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    comparisions++;
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

// Print the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
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
        mergeSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        comparisions=0;
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
        mergeSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file in descending order
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        comparisions=0;
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
        mergeSort(arr,0,i-1); // Sort the array
        for (int j = 0; j < i; j++) {
            fprintf(q, "%d ", arr[j]); // Write sorted numbers to the file in descending order
        }
        printArray(arr,i);
        printf("Number of comparisons: %d\n", comparisions);
        comparisions=0;
        break;
    }
    }
    fclose(f);
    fclose(q);
    return 0;
}
