#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/image.h"

struct Image {
    int largeur;
    int hauteur;
    int mat_rouge[LARGEUR_MAX][HAUTEUR_MAX];
    int mat_vert[LARGEUR_MAX][HAUTEUR_MAX];
    int mat_bleu[LARGEUR_MAX][HAUTEUR_MAX];
};

struct Histogramme {
    int tab_rouge[256];
    int tab_vert[256];
    int tab_bleu[256];
};

enum Couleur {ROUGE, VERT, BLEU, JAUNE };

/* Convertir un nombre décimal en binaire */
char* decimal_en_binaire(int decimal) {
    char* binaire = (char*)malloc(33 * sizeof(char));
    int index = 0;
    int num = decimal;
    char temp;
    
    if (decimal == 0) {
        strcpy(binaire, "0");
        return binaire;
    }
    
    /* Extraire les bits */
    while (num > 0) {
        binaire[index++] = (num % 2) + '0';
        num /= 2;
    }
    binaire[index] = '\0';
    
    /* Inverser la chaîne */
    int debut = 0;
    int fin = index - 1;
    while (debut < fin) {
        temp = binaire[debut];
        binaire[debut] = binaire[fin];
        binaire[fin] = temp;
        debut++;
        fin--;
    }
    
    return binaire;
}

/* Convertir un nombre binaire en décimal */
int binaire_en_decimal(char* binaire) {
    int decimal = 0;
    int puissance = 0;
    int longueur = strlen(binaire);
    
    /* Lire de droite à gauche */
    for (int i = longueur-1; i >= 0; i--) {
        if (binaire[i] == '1') {
            decimal = decimal + (int)pow(2, puissance);
        }
        puissance++;
    }
    
    return decimal;
}
