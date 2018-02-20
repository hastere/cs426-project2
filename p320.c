#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MIN PID 300;
#define MAX PID 5000;
int *bitmap;

int allocate_map(void) {
  printf("Allocating array for pids...\t");

  bitmap = malloc(sizeof(int) * 4700);
  int i;
  for (i = 0; i < 4700; ++i) {
    bitmap[i] = 0;
  }
  if (bitmap) {
    return 1;
  }
  else {
    fprintf(stderr, "Array allocation failed.\n");
    return -1;
  }
}

int allocate_pid(void) {
  int i;
  for (i = 0; i < 4700; ++i) {
    if (bitmap[i] == 0) {
      bitmap[i] = 1;
      return i + 300;
    }
  }
  return 1;
}

void release_pid(int pid) {
  bitmap[(pid-300)] = 0;
}

int main(int argc, char **argv) {

}
