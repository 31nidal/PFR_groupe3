#ifndef FORME_H
#define FORME_H
#include "../include/image.h"

typedef struct Forme * Forme;

char* trouver_nature_forme(Image image);
int* trouver_coordonnees_forme(Image image);
Forme remplir_forme(void);

#endif