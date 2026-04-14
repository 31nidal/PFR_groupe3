/* FICHIER: main.c
*  AUTEURS: GRELET Thomas, YAHYAOUI Nidal
*  RÔLE: Point d'entrée du programme principal (intégration)
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/commande_vocale.h"
#include "../include/config.h"
#include "../include/image.h"
#include "../include/objet.h"
#include "../include/utils.h"

#define PYTHON_CMD_VOC "python python/assistant_vocal.py"
#define PYTHON_SIMU "python3 python/simulation.py"
#define PYTHON_PILOTE "python3 python/pilote_robot.py"

int main(void) {
    int choix = 0;
    int en_cours = 1;

    /* ================= RESET action.txt AU DÉMARRAGE ================= */
    FILE *f = fopen("data/action.txt", "w");
    if (f) fclose(f);
    /* ================================================================= */

    /* Charger la configuration */
    if (!charger_config("config/config.json")) {
        return 1;
    }

    printf("\n===== CHOIX DE L'IMAGE A TRAITER =====\n");
    Image image = lire_image();
    trouver_informations_balles(image);

    printf("\n===== SYSTEME DE COMMANDE ROBOT =====\n");

    while (en_cours) {

        printf("\n-----  Menu  des commandes  -----\n");
        printf("1- Ecrire une commande (clavier)\n");
        printf("2- Parler (commande vocale)\n");
        printf("3- Lancer la simulation (turtle)\n");
        printf("4- Lancer le robot\n");
        printf("5- Arreter le programme\n");
        printf("-> Choix : ");

        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar(); // consomme \n

        switch (choix) {

            case 1:
                saisir_clavier();
                traiter_commande();   // écrit dans action.txt
                break;

            case 2:
                system(PYTHON_CMD_VOC);
                traiter_commande();   // écrit dans action.txt
                break;
            
            case 3:
                system(PYTHON_SIMU);
                break;

            case 4:
                system(PYTHON_PILOTE);
                break;

            case 5:
                en_cours = 0;
                break;

            default:
                printf("Choix invalide.\n");
        }
    }

    printf("\nFin de la saisie des commandes.\n");

    return 0;
}
