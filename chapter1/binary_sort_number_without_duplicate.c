#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define MAX 10000000

#define SIZE (MAX / sizeof(int)) + 1
int vector[SIZE]; // 一个单位有 4 * 8 个字节 大概是32位

int main() {
  FILE * p = fopen("./shuffle_number_without_duplicate.seed", "r");
  char * line = NULL;
  size_t len = 0;
  size_t int_size_by_bit = sizeof(int) * 8;
  while (getline(&line, &len, p) != -1) {
    int val = atoi(line);
    int index = val / int_size_by_bit;
    int position = val % int_size_by_bit;
    int bmode = 1 << (int_size_by_bit - position - 1);
    vector[index] |= bmode;
  }
  fclose(p);

  p = fopen("./sorted_number_without_duplicate.seed", "w");
  for (int i = 0; i < MAX; i ++) {
    int index = i / int_size_by_bit;
    int position = i % int_size_by_bit;
    int bmode = 1 << (int_size_by_bit - position - 1);
    if (bmode & vector[index]) {
      fprintf(p, "%d\n", i);
    }
  }
  fclose(p);
  free(line);
}
