#include <stdio.h>

int main()
{
    char commande[256];

    if (lire_commande(commande, 256)) {
        traiter_commande(commande);
    }

    return 0;
}