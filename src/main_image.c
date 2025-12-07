#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

int main() {
    int pixel[3] = {255, 128, 64};
    int valeur_quantif_2 = quantifier_pixel(pixel, 2);
    int valeur_quantif_3 = quantifier_pixel(pixel, 3);
    Image image1 = init_image();
    lire_image(&image1);

    printf("===== Quantification d'un pixel avec le seuil à 2 =====\n");
    printf("Pixel (%d, %d, %d) ---> %d\n", pixel[0], pixel[1], pixel[2], valeur_quantif_2);

    printf("\n===== Quantification d'un pixel avec le seuil à 3 =====\n");
    printf("Pixel (%d, %d, %d) ---> %d\n", pixel[0], pixel[1], pixel[2], valeur_quantif_3);

    printf("\n===== Affichage de l'image par pixels =====\n");
    afficher_image_pixels(image1);

    int** matrice_quantifiee = quantifier_image(image1);

    /*Affichage de la matrice des pixels quantifiés */
    printf("\n==== Affichage de la matrice quantifiée ====\n");
    for (int i=0 ; i<get_largeur(image1) ; i++) {
        for (int j=0 ; j<get_hauteur(image1) ; j++) {
            printf("%d ", matrice_quantifiee[i][j]);
        }
        printf("\n");
    }

    return 0;
}
