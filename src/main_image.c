#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

int main() {
    Image image5389 = init_image();
    lire_image(&image5389);

    printf("===== Affichage de l'image =====\n");
    afficher_image_pixels(image5389);

    niveau_gris_image(image5389, 8);

    printf("\n===== Affichage de l'image après la mise en niveaux de gris =====\n");
    afficher_image_pixels(image5389);
    return 0;
}
