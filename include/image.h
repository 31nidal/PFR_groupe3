#ifndef IMAGE_H
#define IMAGE_H

#define LARGEUR_MAX 300
#define HAUTEUR_MAX 300

typedef struct Image * Image;
typedef struct Histogramme * Histogramme;
typedef enum Couleur * Couleur;

int lire_image(Image image);
Image niveau_gris_image(Image image);
int quantifier_pixel(int pixel[3], int niveau_quantification);
Image quantifier_image(Image image);

Histogramme histogramme_image(Image image);

Couleur trouver_couleur_objet(Histogramme hist);
Couleur pixel_vers_couleur(int pixel[3], int seuil);

char* decimal_en_binaire(int decimal);
int binaire_en_decimal(char* binaire);

#endif