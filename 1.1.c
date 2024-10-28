#include <stdio.h>
#include <stdlib.h>

struct Pair {
  int max;
  int min;
};

struct Pair maxMinDivideConquer(int arr[], int low, int high) {
  struct Pair result;
  if (low == high) {
    result.max = arr[low];
    result.min = arr[low];
    return result;
  }

  int mid = (low + high) / 2;
  struct Pair left = maxMinDivideConquer(arr, low, mid);
  struct Pair right = maxMinDivideConquer(arr, mid + 1, high);
  result.max = (left.max > right.max) ? left.max : right.max;
  result.min = (left.min < right.min) ? left.min : right.min;
  return result;
}

int main() {
  int arr[5];
  printf("The nos are: ");
  for (int i = 0; i < 5; i++) {
    arr[i] = rand() % 100;
    printf("%d ", arr[i]);
  }
  
  struct Pair result = maxMinDivideConquer(arr, 0, 4);
  printf("\nMaximum element is: %d\n", result.max);
  printf("Minimum element is: %d\n", result.min);
  return 0;
}