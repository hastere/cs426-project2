#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int max, min, size, avg;
int *array;

void *average(void *x) {
    int sum = 0;
    int i;
    for (i = 0; i < size; ++i) {
      sum += array[i];
    }
    avg = sum / size;
    pthread_exit(0);
}

void *maxi(void *x) {
  int maximum = array[0];
  int i;
  for (i = 1; i < size; ++i) {
    if (maximum < array[i])
      maximum = array[i];
  }
  max = maximum;
  pthread_exit(0);
}

void *mini(void *x) {
  int minimum = array[0];
  int i;
  for (i = 1; i < size; ++i) {
    if (minimum > array[i])
      minimum = array[i];
  }
  min = minimum;
  pthread_exit(0);
}

int main(int argc, char **argv) {
  //declare storage array
  array = malloc(sizeof(int) * (argc - 1));
  //error checking
  if (argc < 2) {
    printf("Usage: Input a series of integers on the command line when running");
    printf("this program. Try again with additional arguements.\n");
    return -1;
  }
  //fill array
  int i;
  for (i = 1; i < argc; ++i) {
    array[i - 1] = atoi(argv[i]);
  }
  //variable declarations
  size = argc - 1;
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  //start thread for avg
  pthread_create(&tid, &attr, average, NULL);
  pthread_join(tid, NULL);
  //start thread for max
  pthread_create(&tid, &attr, maxi, NULL);
  pthread_join(tid, NULL);
  //start thread for min
  pthread_create(&tid, &attr, mini, NULL);
  pthread_join(tid, NULL);
  //print results
  printf("avg = %d\nmax = %d\nmin = %d\n", avg, max, min);


  return 0;
}
