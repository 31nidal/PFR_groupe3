#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

int main() {
    int i;
    char* binaire;
    int decimal;
    
    printf("===== TESTS DE CONVERSION =====\n\n");
    
    /* Test 1: Décimal vers Binaire */
    printf("Test 1: Décimal vers Binaire\n");
    printf("-----------------------------\n");
    printf("10 en binaire: %s\n", decimal_en_binaire(10));
    printf("255 en binaire: %s\n", decimal_en_binaire(255));
    printf("42 en binaire: %s\n", decimal_en_binaire(42));
    
    /* Test 2: Binaire vers Décimal */
    printf("\nTest 2: Binaire vers Décimal\n");
    printf("-----------------------------\n");
    printf("1010 en décimal: %d\n", binaire_en_decimal("1010"));
    printf("11111111 en décimal: %d\n", binaire_en_decimal("11111111"));
    printf("101010 en décimal: %d\n", binaire_en_decimal("101010"));
    
    /* Test 3: Vérification (aller-retour) */
    printf("\nTest 3: Vérification (Décimal -> Binaire -> Décimal)\n");
    printf("-----------------------------------------------------\n");
    int nombres[] = {15, 64, 100};
    
    for (i = 0; i < 3; i++) {
        binaire = decimal_en_binaire(nombres[i]);
        decimal = binaire_en_decimal(binaire);
        printf("%d -> %s -> %d [%s]\n", 
               nombres[i], binaire, decimal,
               nombres[i] == decimal ? "OK" : "ERREUR");
        free(binaire);
    }
    
    return 0;
}
