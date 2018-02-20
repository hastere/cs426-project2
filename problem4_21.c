#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Let us create a global variable to change it in threads
int max, min, size;
double avg;
int *array;
// The function to be executed by all threads
void *average(void *avg_gl) {
    double *avg_l = avg_gl;
    int sum = 0;
    for (int i = 0; i < size; ++i) {
      sum += array[i];
    }
    *avg_l = sum / size;
    return NULL;
}

void *maxi(void *max_gl) {
  int *max_l = max_gl;
  int maximum = array[0];
  for (int i = 1; i < size; ++i) {
    if (maximum < array[i])
      maximum = array[i];
  }
  *max_l = maximum;
  return NULL;
}

void *mini(void *min_gl) {
  int *min_l = min_gl;
  int minimum = array[0];
  for (int i = 1; i < size; ++i) {
    if (minimum > array[i])
      minimum = array[i];
  }
  *min_l = minimum;
  return NULL;
}

int main(int argc, char **argv) {
  array = malloc(sizeof(int) * (argc - 1));

  if (argc < 1) {
    printf("Usage: Input a series of integers on the command line when running");
    printf("this program. Try again with additional arguements.\n");
    return -1;
  }

  for (int i = 1; i < argc; ++i) {
    array[i - 1] = atoi(argv[i]);
  }

  size = argc - 1;
  pthread_t tid;
  pthread_create(&tid, NULL, &average, &avg);
  pthread_create(&tid, NULL, &maxi, &max);
  pthread_create(&tid, NULL, &mini, &min);

  //pthread_exit(NULL);

  //wait for child to finish
  while(1) {
    sleep(1);
    if (avg != 0) {
      printf("avg = %f\nmax = %d\nmin = %d\n", avg, max, min);
      break;
    }
  }

  return 0;
}
