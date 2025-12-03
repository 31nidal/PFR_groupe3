#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/image.h"

struct Image {
    int largeur;
    int hauteur;
    int mat_rouge[LARGEUR_MAX][HAUTEUR_MAX];
    int mat_vert[LARGEUR_MAX][HAUTEUR_MAX];
    int mat_bleu[LARGEUR_MAX][HAUTEUR_MAX];
};

struct Histogramme {
    int tab_rouge[256];
    int tab_vert[256];
    int tab_bleu[256];
}; 

enum Couleur {ROUGE, VERT, BLEU, JAUNE};


Image init_image(void) {
    Image image = malloc(sizeof(struct Image));
    image->largeur = 0;
    image->hauteur = 0;
    return image;
}

void lire_image(Image *ptr_image) {
    int largeur, hauteur, tmp, valeur_pixel;

    /* Récupération de la hauteur et de la largeur */
    scanf("%d%d%d", &largeur, &hauteur, &tmp);
    (*ptr_image)->largeur = largeur;
    (*ptr_image)->hauteur = hauteur;

    for (int k=0 ; k<3 ; k++) {
        for (int i=0 ; i<largeur ; i++) {
            for (int j=0 ; j<hauteur ; j++) {
                /* Récupération de la valeur du pixel */
                scanf("%d", &valeur_pixel);

                /* Remplit la matrice rouge */
                if (k == 0) (*ptr_image)->mat_rouge[i][j] = valeur_pixel;

                /* Remplit la matrice bleue */
                if (k == 1) (*ptr_image)->mat_bleu[i][j] = valeur_pixel;

                /* Remplit la matrice verte */
                if (k == 2) (*ptr_image)->mat_vert[i][j] = valeur_pixel;
            }
        }
    }
}

void afficher_image_pixels(Image image) {
    for (int i=0 ; i<image->largeur ; i++) {
        for (int j=0 ; j<image->hauteur ; j++) {
            printf("(%d,%d,%d) ", image->mat_rouge[i][j], image->mat_bleu[i][j], image->mat_vert[i][j]);
        }
        printf("\n");
    }
}

void afficher_image_matrices(Image image) {
    for (int k=0 ; k<3 ; k++) {

        if (k == 0) printf("\n--- Matrice Rouge ---\n");
        if (k == 1) printf("\n--- Matrice Bleue ---\n");
        if (k == 2) printf("\n--- Matrice Verte ---\n");

        for (int i=0 ; i<image->largeur ; i++) {
            for (int j=0 ; j<image->hauteur ; j++) {
                if (k == 0) printf("%d ", image->mat_rouge[i][j]);
                if (k == 1) printf("%d ", image->mat_bleu[i][j]);
                if (k == 2) printf("%d ", image->mat_vert[i][j]);
            }
            printf("\n");
        }
    }
}

Image niveau_gris_image(Image image, int niveau_gris) {
    /* Vérification du niveau de gris */
    if ((niveau_gris < 1) || (niveau_gris > 255)) {
        fprintf(stderr, "Erreur : le niveau de gris n’est pas valide\n");
    } else if (log2(niveau_gris) != (int)log2(niveau_gris)) {
        fprintf(stderr, "Erreur : le niveau de gris n’est pas une puissance de 2\n");
    } else {
        /* Transformation des 3 matrices de l'image en niveau de gris */
        for (int k=0 ; k<3 ; k++) {
            for (int i=0 ; i<image->largeur ; i++) {
                for (int j=0 ; j<image->hauteur ; j++) {
                    if (k==0) image->mat_rouge[i][j] = (int) (image->mat_rouge[i][j] / (256 / (float) niveau_gris));
                    if (k==1) image->mat_bleu[i][j] = (int) (image->mat_bleu[i][j] / (256 / (float) niveau_gris));
                    if (k==2) image->mat_vert[i][j] = (int) (image->mat_vert[i][j] / (256 / (float) niveau_gris));
                }
            }
        }
    }
    return image;
}

/* Convertir un nombre décimal en binaire */
char* decimal_en_binaire(int decimal) {
    char* binaire = (char*)malloc(33 * sizeof(char));
    int index = 0;
    int num = decimal;
    char temp;
    
    if (decimal == 0) {
        strcpy(binaire, "0");
        return binaire;
    }
    
    /* Extraire les bits */
    while (num > 0) {
        binaire[index++] = (num % 2) + '0';
        num /= 2;
    }
    binaire[index] = '\0';
    
    /* Inverser la chaîne */
    int debut = 0;
    int fin = index - 1;
    while (debut < fin) {
        temp = binaire[debut];
        binaire[debut] = binaire[fin];
        binaire[fin] = temp;
        debut++;
        fin--;
    }
    
    return binaire;
}

/* Convertir un nombre binaire en décimal */
int binaire_en_decimal(char* binaire) {
    int decimal = 0;
    int puissance = 0;
    int longueur = strlen(binaire);
    
    /* Lire de droite à gauche */
    for (int i = longueur-1; i >= 0; i--) {
        if (binaire[i] == '1') {
            decimal = decimal + (int)pow(2, puissance);
        }
        puissance++;
    }
    
    return decimal;
}
