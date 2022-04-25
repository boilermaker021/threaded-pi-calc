#ifndef PICALC_H
#define PICALC_H

#include <stdbool.h>

#define PI 3.14159265


typedef struct point {
  float x;
  float y;
} point_t;



float check_accuracy(double result);

point_t gen_point(int *seed);

bool inside_unit_circle(point_t point);

void *calc(void *iterations);

#endif