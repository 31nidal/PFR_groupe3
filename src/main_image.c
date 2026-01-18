#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/forme.h"
#include "../include/objet.h"
#include "../include/config.h"

int main() {
    /* Charger la configuration */
    if (!charger_config("config/config_base.json")) {
        return 1;
    }
    
    /* Test d'une labellisation d'une sous-image */
    Image image1 = lire_image();
    Image sous_image;
    int** mat_bin;
    int nb_objets = nombre_objets_image(image1);

    for (int i=1 ; i<nb_objets+1 ; i++) {
        printf("\n===== Objet %d =====\n\n", i);
        sous_image = sous_image_objet(image1, i, 3);
        mat_bin = binariser_image(sous_image);
        afficher_image_binaire(mat_bin, get_largeur(sous_image), get_hauteur(sous_image));
        printf("\n\n");
    }
    
    /* Libération */    
    liberer_config();

    return 0;
}