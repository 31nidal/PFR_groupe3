#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/objet.h"
#include "../include/forme.h"
#include "../include/image.h"
#include "../include/config.h"

struct Objet {
  Couleur couleur;
  Forme forme;
};


Objet init_objet(Couleur couleur, Forme forme) {
  Objet objet = malloc(sizeof(struct Objet));
  objet->couleur = couleur;
  objet->forme = forme;
  return objet;
}


Image sous_image_objet(Image image, int valeur_objet, int delta) {
  /* Initialisation et allocation des variables */
  int* tab_coord = trouver_coordonnees_forme(image, valeur_objet);

  /* Application du delta en vérifiant que l'on ne sort pas du cadre */
  if ((tab_coord[0] - delta) < 0) tab_coord[0] = 0;
  else tab_coord[0] -= delta;

  if ((tab_coord[1] - delta) < 0) tab_coord[1] = 0;
  else tab_coord[1] -= delta;

  if ((tab_coord[2] + delta) > get_largeur(image)) tab_coord[2] = get_largeur(image)-1;
  else tab_coord[2] += delta;

  if ((tab_coord[3] + delta) > get_hauteur(image)) tab_coord[3] = get_hauteur(image)-1;
  else tab_coord[3] += delta;

  /* Définitions de la largeur et hauteur de la sous-image, puis initialisation */
  int largeur_sous_image = tab_coord[2] - tab_coord[0] + 1;
  int hauteur_sous_image = tab_coord[3] - tab_coord[1] + 1;

  Image sous_image = init_image(largeur_sous_image, hauteur_sous_image);

  /* Allocation mémoire des matrices RVB de la sous-image */
  int** sous_mat_rouge = (int**) malloc(largeur_sous_image*sizeof(int*));
  int** sous_mat_vert = (int**) malloc(largeur_sous_image*sizeof(int*));
  int** sous_mat_bleu = (int**) malloc(largeur_sous_image*sizeof(int*));
  for (int i=0 ; i<largeur_sous_image ; i++) {
    sous_mat_rouge[i] = (int*) malloc(hauteur_sous_image*sizeof(int));
    sous_mat_vert[i] = (int*) malloc(hauteur_sous_image*sizeof(int));
    sous_mat_bleu[i] = (int*) malloc(hauteur_sous_image*sizeof(int));
  }

  /* Remplit les matrices RGB de la sous-image */
  for (int i=0 ; i<largeur_sous_image ; i++) {
    for (int j=0 ; j<hauteur_sous_image ; j++) {
      sous_mat_rouge[i][j] = get_mat_rouge(image)[i+tab_coord[0]][j+tab_coord[1]];
      sous_mat_vert[i][j] = get_mat_vert(image)[i+tab_coord[0]][j+tab_coord[1]];
      sous_mat_bleu[i][j] = get_mat_bleu(image)[i+tab_coord[0]][j+tab_coord[1]];
    }
  }

  /* Affecte les nouvelles matrices à la sous-image */
  set_mat_rouge(sous_image, sous_mat_rouge);
  set_mat_vert(sous_image, sous_mat_vert);
  set_mat_bleu(sous_image, sous_mat_bleu);

  /* Retourne la sous-image */
  return sous_image;
}