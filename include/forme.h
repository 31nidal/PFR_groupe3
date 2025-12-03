#ifndef FORME_H
#define FORME_H
#include "../include/image.h"

typedef struct Forme * Forme;

/* Initialise une forme (allocation mémoire) */
Forme init_forme(char* nature, int x_dep, int y_dep, int x_arr, int y_arr);

/* à coder */
char* trouver_nature_forme(Image image);

/* à coder */
int* trouver_coordonnees_forme(Image image);

/* à coder */
Forme remplir_forme(void);

#endif