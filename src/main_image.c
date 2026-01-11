#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/forme.h"
#include "../include/config.h"

int main() {
    /* 1. Charger la configuration */
    if (!charger_config("config/config_base.json")) {
        return 1;
    }
    
    /* 2. Lire les paramètres nécessaires */
    int bits = lire_valeur_json("quantification_bits", config_json);
    int seuil_couleur = lire_valeur_json("seuil_couleur", config_json);
    
    printf(" -> Configuration : %d bits de quantification, seuil de couleur (saturation)=%d\n", bits, seuil_couleur);
    
    /* 3. Test avec binarisation d'une image et histogramme */
    Image image1 = init_image();
    Histogramme hist1;
    lire_image(&image1);
    
    printf("\n===== Binarisation d'une image de test =====\n");
    int** img_bin = binariser_image(image1);
    afficher_image_binaire(img_bin, get_largeur(image1), get_hauteur(image1));

    printf("\n===== Histogramme de l'image de test =====\n");
    hist1 = histogramme_image(image1);
    afficher_pourcentages_histogramme(hist1, get_largeur(image1)*get_hauteur(image1));
    
    /* 4. Libération */
    for (int i = 0; i < get_largeur(image1); i++) {
        free(img_bin[i]);
    }
    free(img_bin);
    free(image1);
    
    liberer_config();
    return 0;
}