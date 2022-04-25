#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "picalc.h"


int main(int argc, char** argv) {
  unsigned int iterations = 1;
  unsigned int thread_count = 1;
  if (argc == 3) {
    thread_count = atoi(argv[1]);
    iterations = atoi(argv[2]); //change to 2 when implementing threads
  } else {
    printf("Invalid arguments\nProper usage: picalc <thread count> <iterations>\n", argc);
    return 1;
  }

  //time_t begin = time(NULL);

  pthread_t *pthread_list = malloc(sizeof(pthread_t) * thread_count);


  for (int i = 0; i < thread_count; i++) {
    pthread_create(&pthread_list[i], NULL, &calc, &iterations);
  }


  unsigned long total_in = 0;

  for (int i = 0; i < thread_count; i++) {
    unsigned int result = 0;
    pthread_join(pthread_list[i], &result);

    total_in += result; 
  }

  
  double pi = 4 * ((float) total_in / (float)(iterations * thread_count));

  //time_t end = time(NULL);

  printf("Approximated value of pi: %.8f\n", pi);
  printf("Percent error: %.8f\n", check_accuracy(pi));
  //printf("Time to complete: %.2f seconds\n", (begin - end));
  printf("Threads: %d\n", thread_count);
  printf("Iterations per thread: %d\n", iterations);
  printf("Total iterations: %d\n", iterations * thread_count);

  return 0;
}