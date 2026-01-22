#ifndef OBJET_H
#define OBJET_H

#include "../include/image.h"
#include "../include/forme.h"

typedef struct Objet * Objet;

/* Initialise un objet (allocation mémoire) */
Objet init_objet(Couleur couleur, Forme forme);

/* Renvoie la sous-image centrée sur l'objet */
Image sous_image_objet(Image image, int valeur_objet, int delta);

/* Trouve la couleur d'un objet */
Couleur trouver_couleur_objet(Image sous_image);

/* Trouve où se situe l'objet sur l'image (renvoie "gauche", "milieu" ou "droite") */
char* trouver_direction_objet(Image image, int valeur_objet);

/* Trouve la distance réelle en mètre(approximation) entre la prise de la photo et un objet */
int trouver_distance_objet(Image image, int valeur_objet);

/* Trouve l'angle réelle en dégré (approximation) entre la prise de la photo et un objet */
int trouver_angle_objet(Image image, int valeur_objet);

#endif