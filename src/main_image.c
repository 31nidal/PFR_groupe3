#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

int main() {

    Image image1 = init_image();
    lire_image(&image1);

    /* Test de binarisation */
    int seuil_sat = 60;  /* À ajuster  */
    int** img_bin = binariser_image(image1, seuil_sat);

    afficher_image_binaire(img_bin, get_largeur(image1), get_hauteur(image1));

    /* Libération mémoire */
    for (int i = 0; i < get_largeur(image1); i++) {
        free(img_bin[i]);
    }
    free(img_bin);
    
    printf("\n");

    return 0;
}
