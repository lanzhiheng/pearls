#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printArray(int * array, int len) {
  for (int i = 0; i < len; i ++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void merge_sort_recursive(int * array, int * temp, int start, int end) {
  if (end <= start) return;

  assert(end > start);
  int mid = (end + start) / 2;
  merge_sort_recursive(array, temp, start, mid);
  merge_sort_recursive(array, temp, mid + 1, end);

  int i = start, j = mid + 1;
  int index = start;

  while (i <= mid && j <= end) {
    if (array[i] <= array[j]) {
      temp[index] = array[i++];
    } else {
      temp[index] = array[j++];
    }
    index++;
  }

  while (i <= mid) temp[index++] = array[i++];
  while (j <= end) temp[index++] = array[j++];

  for (index = start; index <= end; index++)
    array[index] = temp[index];
  printArray(array, 10);
}

void merge_sort(int * arr, const int len) {
  int * temp = malloc(sizeof(int) * len);
  merge_sort_recursive(arr, temp, 0, len - 1);
  free(temp);
}

int main() {
  int a[] = { 100, 2, 30, 44, 1, 8, 11, 34, 99, 70 };
  /* printArray(a, 10); */
  merge_sort(a, 10);
  printArray(a, 10);
}
