#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"

/* Convertir un nombre décimal en binaire */
char* decimalEnBinaire(int decimal) {
    char* binaire = (char*)malloc(33 * sizeof(char));
    int index = 0;
    int num = decimal;
    int i;
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
int binaireEnDecimal(char* binaire) {
    int decimal = 0;
    int puissance = 0;
    int longueur = strlen(binaire);
    int i;
    
    /* Lire de droite à gauche */
    for (i = longueur - 1; i >= 0; i--) {
        if (binaire[i] == '1') {
            decimal = decimal + (int)pow(2, puissance);
        }
        puissance++;
    }
    
    return decimal;
}
