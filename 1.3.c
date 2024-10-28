#include <stdio.h>
#include <stdlib.h>

#define MAX 1000


void read_numbers_from_file(const char *filename, int *arr, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            perror("Error reading number from file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}


int count_duplicates(int *arr, int n) {
    int count = 0;
    int *seen = (int *)calloc(MAX, sizeof(int));

    for (int i = 0; i < n; i++) {
        if (seen[arr[i]] == 1) {
            count++;
        }
        seen[arr[i]]++;
    }

    free(seen);
    return count;
}


int find_most_repeating(int *arr, int n) {
    int *freq = (int *)calloc(MAX, sizeof(int));
    int max_count = 0;
    int most_repeating = arr[0];

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if (freq[arr[i]] > max_count) {
            max_count = freq[arr[i]];
            most_repeating = arr[i];
        }
    }

    free(freq);
    return most_repeating;
}

int main() {
    int n;
    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements should be greater than zero.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    read_numbers_from_file("numbers.txt", arr, n);

    int duplicate_count = count_duplicates(arr, n);
    int most_repeating = find_most_repeating(arr, n);

    printf("Total number of duplicate elements: %d\n", duplicate_count);
    printf("Most repeating element: %d\n", most_repeating);

    free(arr);
    return 0;
}