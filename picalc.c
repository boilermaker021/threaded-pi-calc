#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


#include "picalc.h"



float check_accuracy(double result) {
  

  return 0;
}

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


void *calc(void *iterations) {
  int state = time(NULL) ^ pthread_self();

  unsigned int total_in = 0;
  for (int i = 0; i < (*(int *)iterations); i++) {
    if (inside_unit_circle(gen_point(&state))) {
      total_in++;
    }
  }

  return total_in;
}