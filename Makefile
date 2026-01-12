all:
	gcc -Wall -Wextra -std=c99 -Iinclude \
	src/main.c src/commande_vocale.c \
	-o bin/prog_commande

clean:
	rm -f bin/prog_commande
