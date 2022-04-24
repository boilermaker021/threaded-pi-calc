#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

typedef struct point {
  float x;
  float y;
} point_t;

point_t gen_point(int *seed) {
  point_t pt = { 0 };
  pt.x = ((float)rand_r(seed) / (float)(RAND_MAX / 2)) - 1;
  pt.y = ((float)rand_r(seed) / (float)(RAND_MAX / 2)) - 1;
  return pt;
}

bool inside_unit_circle(point_t point) {
  float magnitude = sqrt(pow(point.x, 2) + pow(point.y, 2));
  if (magnitude <= 1) {
    return true;
  }
  return false;
}


int calc(int iterations) {
  int state = time(NULL) ^ pthread_self();

  int total_in = 0;
  for (int i = 0; i < iterations; i++) {
    if (inside_unit_circle(gen_point(&state))) {
      total_in++;
    }
  }

  return total_in;
}

int main(int argc, char** argv) {
  int iterations = 0;
  int thread_count = 1;
  if (argc == 3) {
    thread_count = atoi(argv[1]);
    iterations = atoi(argv[2]); //change to 2 when implementing threads
  } else {
    printf("Invalid arguments\nProper usage: picalc <iterations>\n", argc);
    return 1;
  }

  //start threads:

  int in = calc(iterations);
  double pi = 4 * ((float) in / (float)(iterations * thread_count));

  printf("Approximated value of pi: %.8f\n", pi);

  return 0;
}