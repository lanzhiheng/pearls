#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000000
#define MAX_SIZE_OF_NAME 255
#define NUM 10

void shuffle(int * array, int size) {
  for (int i = size - 1; i > 0; i --) {
    int r = rand() % i;
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
}

int * random_number_list(int start, int len) {
  int * array = malloc(sizeof(int) * len);
  for (int i = 0; i < len; i++) {
    array[i] = i + start;
  }
  shuffle(array, len);
  return array;
}

int main(int args, char ** argv) {
  if (args != 2) abort();
  srand(time(0));
  char * prefix = argv[1];
  int range = MAX / NUM;
  char name[MAX_SIZE_OF_NAME];

  for (int i = 0; i < NUM; i ++) {
    sprintf(name, "seed/%s-%d.seed", prefix, i);
    FILE * p = fopen(name, "w");
    int * array = random_number_list(i * range, range);
    for (int j = 0; j < range; j++) {
      fprintf(p, "%d\n", array[j]);
    }
    fclose(p);
    free(array);
  }

  FILE * file[NUM];

  for (int i = 0; i < NUM; i++) {
    sprintf(name, "seed/%s-%d.seed", prefix, i);
    file[i] = fopen(name, "r");
  }

  for (int i = 0; i < NUM; i++) {
    sprintf(name, "seed/other-%s-%d.seed", prefix, i);
    FILE * f = fopen(name, "w");
    char * line = NULL;
    size_t len = 0;

    int index = rand() % NUM;

    for (int j = 0; j < range; j++) {
      while (getline(&line, &len, file[index]) == -1) {
        index = rand() % NUM;
      }
      int val = atoi(line);
      fprintf(f, "%d\n", val);
    }
    fclose(f);
  }

  for (int i = 0; i < NUM; i++) {
    sprintf(name, "seed/%s-%d.seed", prefix, i);
    fclose(file[i]);
    remove(name);
  }
}
