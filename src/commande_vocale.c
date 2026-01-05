#include <stdio.h>
#include <string.h>

int lire_commande(char *buffer, int taille) {
    FILE *f = fopen("commande.txt", "r");
    if (!f) {
        printf("[ERREUR] Impossible d'ouvrir commande.txt\n");
        return 0;
    }

    fgets(buffer, taille, f);
    fclose(f);

    buffer[strcspn(buffer, "\n")] = 0; // enlever le \n

    printf("[TRACE] Commande lue : %s\n", buffer);
    return 1;
}

void traiter_commande(const char *cmd) {
    if (strstr(cmd, "avance")) {
        printf("[ACTION] Robot avance\n");
        // executer_avance();
    }
    else if (strstr(cmd, "recule")) {
        printf("[ACTION] Robot recule\n");
    }
    else if (strstr(cmd, "droite")) {
        printf("[ACTION] Robot tourne à droite\n");
    }
    else if (strstr(cmd, "gauche")) {
        printf("[ACTION] Robot tourne à gauche\n");
    }
    else {
        printf("[ERREUR] Commande inconnue\n");
    }
}

