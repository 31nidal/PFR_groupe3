#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commande_vocale.h"

#define CMD_FILE "commande.txt"
#define PYTHON_CMD_VOC "python3 python/assistant_vocal.py"
#define PYTHON_SIMU "python3 python/simulation.py"

static void saisir_clavier(void)
{
    char buffer[512];

    printf("Entrez votre commande :\n> ");
    fgets(buffer, sizeof(buffer), stdin);

    FILE *f = fopen(CMD_FILE, "w");
    if (!f) {
        perror("commande.txt");
        return;
    }

    fputs(buffer, f);
    fclose(f);
}

int main(void)
{
    int choix = 0;
    int en_cours = 1;

    /* ================= RESET action.txt AU DÉMARRAGE ================= */
    FILE *f = fopen("action.txt", "w");
    if (f) fclose(f);
    /* ================================================================= */

    printf("=== SYSTEME DE COMMANDE ROBOT ===\n");

    while (en_cours) {

        printf("\n--------  Menu  des actions  --------\n");
        printf("1- Ecrire une commande (clavier)\n");
        printf("2- Parler (commande vocale)\n");
        printf("3- Lancer la simulation (turtle)\n");
        printf("4- Arreter le programme\n");
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
                en_cours = 0;
                break;

            default:
                printf("Choix invalide.\n");
        }
    }

    printf("\nFin de la saisie des commandes.\n");

    return 0;
}
