#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commande_vocale.h"

#define CMD_FILE     "commande.txt"
#define ACTION_FILE  "action.txt"
#define LOIS_FILE    "lois.txt"

#define PYTHON_CMD "venv/bin/python python/assistant_vocal.py"

/* ================== SAISIE CLAVIER ================== */

void saisir_clavier(void) {
    char buffer[512];

    printf("Entrez votre commande :\n> ");
    fgets(buffer, sizeof(buffer), stdin);

    FILE *f = fopen(CMD_FILE, "w");
    if (!f) {
        printf("[ERREUR] Impossible d'ecrire commande.txt\n");
        return;
    }
    fputs(buffer, f);
    fclose(f);
}

/* ================== GESTION DES ACTIONS ================== */

void copier_actions_dans_lois(void) {
    FILE *src = fopen(ACTION_FILE, "r");
    if (!src) return;

    FILE *dst = fopen(LOIS_FILE, "a");
    if (!dst) {
        fclose(src);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), src)) {
        fprintf(dst, "%s", buffer);
    }

    fclose(src);
    fclose(dst);

    /* vider action.txt */
    src = fopen(ACTION_FILE, "w");
    if (src) fclose(src);
}

/* ================== AFFICHAGE PROPRE ================== */

void afficher_lois(void) {
    FILE *f = fopen(LOIS_FILE, "r");
    if (!f) {
        printf("Aucune action en memoire.\n");
        return;
    }

    printf("\n=== Historique des actions ===\n");

    char action[64];
    int index = 1;

    /* lecture mot par mot */
    while (fscanf(f, "%63s", action) == 1) {
        printf("%d) %s\n", index++, action);
    }

    if (index == 1) {
        printf("(vide)\n");
    }

    printf("==============================\n\n");
    fclose(f);
}

/* ================== MAIN ================== */

int main(void) {
    int choix = 0;
    int en_cours = 1;

    printf("=== Systeme de Commande Robot ===\n");

    while (en_cours) {
        printf("\nMenu :\n");
        printf("1) Parler (reconnaissance vocale)\n");
        printf("2) Ecrire (clavier)\n");
        printf("3) Arreter le programme\n");
        printf("4) Afficher l'historique des actions\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            getchar(); /* nettoyage entrée */
            continue;
        }
        getchar(); /* consomme le \n */

        switch (choix) {

            case 1:
                printf("=== Reconnaissance vocale ===\n");
                system(PYTHON_CMD);
                traiter_commande();
                copier_actions_dans_lois();
                break;

            case 2:
                saisir_clavier();
                traiter_commande();
                copier_actions_dans_lois();
                break;

            case 3:
                printf("Arret du programme.\n");
                en_cours = 0;
                break;

            case 4:
                afficher_lois();
                break;

            default:
                printf("Choix invalide.\n");
                break;
        }
    }

    return 0;
}
