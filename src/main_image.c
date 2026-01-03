#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

int main() {
    int taille;
    float valeur;

    Image image1 = init_image();
    lire_image(&image1);

    printf("\n===== Affichage de l'image par pixels =====\n");
    afficher_image_pixels(image1);

    int** matrice_quantifiee = quantifier_image(image1);

    /* Affichage de la matrice des pixels quantifiés */
    printf("\n==== Affichage de la matrice quantifiée ====\n");
    for (int i=0 ; i<get_largeur(image1) ; i++) {
        for (int j=0 ; j<get_hauteur(image1) ; j++) {
            printf("%d ", matrice_quantifiee[i][j]);
        }
        printf("\n");
    }

    /* Calcul de l'histogramme */
    Histogramme hist = histogramme_image(image1);
    
    /* Affichage de l'histogramme */
    printf("\n==== Affichage du tableau de l'histogramme ====\n- ");
    for (int i=0 ; i<64 ; i++) {
        printf("%d - ", hist[i]);
    }
    printf("\n");

    /* Affichage en pourcentage */
    printf("\n==== Affichage de l'histogramme avec pourcentages ====\n");
    taille = get_hauteur(image1) * get_largeur(image1);
    for (int i=0 ; i<64 ; i++) {
        if (hist[i] != 0) {
            valeur = (hist[i]/ (float) taille) * 100;
            printf("* %d -> %.2f%%\n", i, valeur);
        }
    }
    printf("\n");

    return 0;
}
