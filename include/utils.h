#ifndef UTILS_H
#define UTILS_H

#define CMD_FILE "commande.txt"

void saisir_clavier(void);

char* decimal_en_binaire(int decimal);

int binaire_en_decimal(char* binaire);

int max_tableau(int* tableau, int taille);

int max_matrice(int** matrice, int largeur, int hauteur);

#endif