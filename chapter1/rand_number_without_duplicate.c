#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000000

void shuffle(int * array, int size) {
  for (int i = size - 1; i > 0; i --) {
    int r = rand() % i;
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
}

int main() {
  srand(time(0));
  FILE * p = fopen("shuffle_number_without_duplicate.seed", "w");
  int * array = malloc(sizeof(int) * MAX);
  for (int i = 0; i < MAX; i++) {
    array[i] = i;
  }
  shuffle(array, MAX);

  for (int i = 0; i < MAX; i++) {
    fprintf(p, "%d\n", array[i]);
  }
  fclose(p);
}
