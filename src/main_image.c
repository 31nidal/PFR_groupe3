#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/forme.h"
#include "../include/config.h"

int main() {
    /* Charger la configuration */
    if (!charger_config("config/config_base.json")) {
        return 1;
    }
    
    /* Test d'une labellisation d'une image */
    Image image1 = init_image();
    lire_image(&image1);
    
    /* Affichage des boîtes englobantes */    
    afficher_image_boites_englobantes(image1, 5);
    
    /* Libération */    
    liberer_config();

    return 0;
}