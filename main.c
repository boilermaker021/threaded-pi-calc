#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "picalc.h"


int main(int argc, char** argv) {
  unsigned long iterations = 1;
  unsigned long thread_count = 1;
  if (argc == 3) {
    thread_count = atoi(argv[1]);
    iterations = atoi(argv[2]);
  } else {
    printf("Invalid arguments\nProper usage: picalc <thread count> <iterations>\n");
    return 1;
  }

  time_t begin = time(NULL);

  pthread_t *pthread_list = malloc(sizeof(pthread_t) * thread_count);


  for (unsigned long i = 0; i < thread_count; i++) {
    pthread_create(&pthread_list[i], NULL, &calc, &iterations);
  }


  unsigned long total_in = 0;
 
  for (int i = 0; i < thread_count; i++) {
    unsigned long result = 0;
    pthread_join(pthread_list[i], &result);

    total_in += result; 
  }

  
  double pi = 4 * ((double) total_in / (double)(iterations * thread_count));

  time_t end = time(NULL);

  printf("Approximated value of pi: %.8f\n", pi);
  printf("Percent error: %.8f%%\n", check_accuracy(pi));
  printf("Time to complete: %d seconds\n", (end - begin));
  printf("Threads: %d\n", thread_count);
  printf("Iterations per thread: %d\n", iterations);
  printf("Total iterations: %lu\n", iterations * thread_count);

  return 0;
}