#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/forme.h"
#include "../include/image.h"

struct Forme {
  char* nature;
  int x_dep;
  int y_dep;
  int x_arr;
  int y_arr;
};


Forme init_forme(char* nature, int x_dep, int y_dep, int x_arr, int y_arr) {
  Forme forme = malloc(sizeof(struct Forme));
  forme->nature = nature;
  forme->x_dep = x_dep;
  forme->y_dep = y_dep;
  forme->x_arr = x_arr;
  forme->y_arr = y_arr;
  return forme;
}