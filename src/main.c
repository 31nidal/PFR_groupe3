#include <stdio.h>
#include "commande_vocale.h"

int main(void)
{
    char commande[256];

    if (lire_commande(commande, 256)) {
        traiter_commande(commande);
    }

    return 0;
}
