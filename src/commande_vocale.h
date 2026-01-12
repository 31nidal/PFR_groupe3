#ifndef COMMANDE_VOCALE_H
#define COMMANDE_VOCALE_H

/* Lit la commande écrite par le module Python */
int lire_commande(char *buffer, int taille);

/* Traite la commande vocale (lecture + interprétation) */
void traiter_commande(void);

#endif
