#ifndef IMAGE_H
#define IMAGE_H

#define LARGEUR_MAX 300
#define HAUTEUR_MAX 300

typedef struct Image * Image;
typedef struct Histogramme * Histogramme;
typedef enum Couleur * Couleur;

/* Initialise une image (allocation mémoire) */
Image init_image(void);

/* Lit et remplit une variable de type Image */
void lire_image(Image *ptr_image);

/* Affiche une image par pixels (R,V,B) */
void afficher_image_pixels(Image image);

/* Affiche successivement les 3 matrices d'une image */
void afficher_image_matrices(Image image);

/* Transforme les 3 matrices d'une image pour les passer à un certain niveau de gris (passé en paramètre) */
Image niveau_gris_image(Image image, int niveau_gris);

/* Retourne la valeur décimal d'un pixel quantifié */
int quantifier_pixel(int pixel[3], int niveau_quantification);

/* Retourne la matrice des pixels quantifiés */
int** quantifier_image(Image image);

/* à coder */
Histogramme histogramme_image(Image image);

/* à coder */
Couleur trouver_couleur_objet(Histogramme hist);

/* à coder */
Couleur pixel_vers_couleur(int pixel[3], int seuil);

int get_largeur(Image image);
int get_hauteur(Image image);

/* Convertit un nombre décimal en binaire (sur 8 bits) */
char* decimal_en_binaire(int decimal);

/* Convertit un nombre binaire (sur 8 bits) en décimal  */
int binaire_en_decimal(char* binaire);

#endif