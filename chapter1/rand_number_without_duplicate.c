#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* #define MAX 1000000000 */
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

static void generate_files_with_shuffled_num(char * prefix, int range) {
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
}

static void shuffle_all_exist_files(char * prefix, int range) {
  char name[MAX_SIZE_OF_NAME];

  int avaiable = NUM;
  FILE * file[avaiable]; // We will build a dynamic array

  for (int i = 0; i < NUM; i++) { // Open all File with number
    sprintf(name, "seed/%s-%d.seed", prefix, i);
    file[i] = fopen(name, "r");
  }

  for (int i = 0; i < NUM; i++) {
    sprintf(name, "seed/other-%s-%d.seed", prefix, i);
    FILE * f = fopen(name, "w");
    char * line = NULL;
    size_t len = 0;

    int index = rand() % avaiable;

    for (int j = 0; j < range; j++) {
      while (getline(&line, &len, file[index]) == -1) { // current seed file has been empty
        srand(time(0));
        FILE * temp = file[index];
        file[index] = file[avaiable - 1];
        file[avaiable - 1] = temp;
        avaiable --;
        index = rand() % avaiable;
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

int main(int args, char ** argv) {
  if (args != 2) abort();
  srand(time(0));
  char * prefix = argv[1];
  int range = MAX / NUM;

  generate_files_with_shuffled_num(prefix, range);
  shuffle_all_exist_files(prefix, range);
}
