#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int min;
    int max;
    int secondMin;
    int secondMax;
} Result;

Result findSecondMinMax(int arr[], int left, int right) {
    Result result;

    if (left == right) {
        result.min = arr[left];
        result.max = arr[left];
        result.secondMin = INT_MAX;
        result.secondMax = INT_MIN;
        return result;
    }

    if (right == left + 1) {
        result.min = arr[left] < arr[right] ? arr[left] : arr[right];
        result.max = arr[left] > arr[right] ? arr[left] : arr[right];
        result.secondMin = arr[left] < arr[right] ? arr[right] : arr[left];
        result.secondMax = arr[left] > arr[right] ? arr[right] : arr[left];
        return result;
    }

    int mid = (left + right) / 2;
    Result leftResult = findSecondMinMax(arr, left, mid);
    Result rightResult = findSecondMinMax(arr, mid + 1, right);
    result.min = leftResult.min < rightResult.min ? leftResult.min : rightResult.min;
    result.max = leftResult.max > rightResult.max ? leftResult.max : rightResult.max;
    if (leftResult.min < rightResult.min) {
        result.secondMin = rightResult.min < leftResult.secondMin ? rightResult.min : leftResult.secondMin;
    } else {
        result.secondMin = leftResult.min < rightResult.secondMin ? leftResult.min : rightResult.secondMin;
    }
    if (leftResult.max > rightResult.max) {
        result.secondMax = rightResult.max > leftResult.secondMax ? rightResult.max : leftResult.secondMax;
    } else {
        result.secondMax = leftResult.max > rightResult.secondMax ? leftResult.max : rightResult.secondMax;
    }

    return result;
}

int main() {
  int arr[5];
  printf("The nos are: ");
  for (int i = 0; i < 5; i++) {
    arr[i] = rand() % 100;
    printf("%d ", arr[i]);
  }
    Result result = findSecondMinMax(arr, 0, 4);
    printf("\nMinimum: %d\n", result.min);
    printf("Second Minimum: %d\n", result.secondMin);
    printf("Maximum: %d\n", result.max);
    printf("Second Maximum: %d\n", result.secondMax);
    return 0;
}