#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "commande_vocale.h"

#define FICHIER_COMMANDE "commande.txt"

/* chemins vers les fichiers de langue */
#define FR_JSON "../python/fr.json"
#define EN_JSON "../python/en.json"
#define ES_JSON "../python/es.json"

#define TAILLE_MAX 4096


/* lire la commande écrite par Python                 */

int lire_commande(char *buffer, int taille) {
    FILE *f = fopen(FICHIER_COMMANDE, "r");
    if (!f) {
        printf("[ERREUR] Impossible d'ouvrir %s\n", FICHIER_COMMANDE);
        return 0;
    }

    if (fgets(buffer, taille, f) == NULL) {
        fclose(f);
        return 0;
    }
    fclose(f);

    buffer[strcspn(buffer, "\n")] = '\0';

    /* normalisation */
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower(buffer[i]);
    }

    printf("[TRACE] Commande reçue : %s\n", buffer);
    return 1;
}


/* lire un fichier json complet dans une chaîne       */

int charger_fichier(const char *chemin, char *contenu, int taille) {
    FILE *f = fopen(chemin, "r");
    if (!f) return 0;

    int lu = fread(contenu, 1, taille - 1, f);
    contenu[lu] = '\0';

    fclose(f);
    return 1;
}


/* vérifie si la commande est présente dans un json   */

int reconnaitre_dans_langue(const char *json, const char *commande) {
    return strstr(json, commande) != NULL;
}


/* exécuter l'action associée*/

void executer_action(const char *cmd) {
    if (strstr(cmd, "avance") || strstr(cmd, "forward") || strstr(cmd, "avanza")) {
        printf("[ACTION] Robot avance\n");
    }
    else if (strstr(cmd, "gauche") || strstr(cmd, "left") || strstr(cmd, "izquierda")) {
        printf("[ACTION] Robot tourne à gauche\n");
    }
    else if (strstr(cmd, "droite") || strstr(cmd, "right") || strstr(cmd, "derecha")) {
        printf("[ACTION] Robot tourne à droite\n");
    }
    else if (strstr(cmd, "stop") || strstr(cmd, "arrête") || strstr(cmd, "para")) {
        printf("[ACTION] Robot stop\n");
    }
    else {
        printf("[ACTION] Commande reconnue mais action non mappée\n");
    }
}


/* traitement principal de la commande*/

void traiter_commande(const char *cmd) {
    char json[TAILLE_MAX];

    /* français */
    if (charger_fichier(FR_JSON, json, TAILLE_MAX) &&
        reconnaitre_dans_langue(json, cmd)) {
        printf("[TRACE] Commande reconnue en français\n");
        executer_action(cmd);
        return;
    }

    /* anglais */
    if (charger_fichier(EN_JSON, json, TAILLE_MAX) &&
        reconnaitre_dans_langue(json, cmd)) {
        printf("[TRACE] Commande reconnue en anglais\n");
        executer_action(cmd);
        return;
    }

    /* espagnol */
    if (charger_fichier(ES_JSON, json, TAILLE_MAX) &&
        reconnaitre_dans_langue(json, cmd)) {
        printf("[TRACE] Commande reconnue en espagnol\n");
        executer_action(cmd);
        return;
    }

    /* aucune langue */
    printf("[ERREUR] Commande non reconnue dans aucune langue\n");
}
