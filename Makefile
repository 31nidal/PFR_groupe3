# ================= CONFIG =================
CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude -lm

# ================= EXECUTION =================

# Lance le programme principal
run: bin/prog_principal.out
	./bin/prog_principal.out

# Lance le programme de traitement d'image
image: bin/prog_image.out
	./bin/prog_image.out

# ================= LINKING (Création des exécutables) =================

bin/prog_principal.out: lib/main.o lib/commande_vocale.o lib/image.o lib/objet.o lib/config.o lib/utils.o
	@mkdir -p bin
	$(CC) lib/main.o lib/commande_vocale.o lib/image.o lib/objet.o lib/config.o lib/utils.o -o bin/prog_principal.out $(CFLAGS)

bin/prog_image.out: lib/main_image.o lib/image.o lib/objet.o lib/config.o lib/utils.o
	@mkdir -p bin
	$(CC) lib/main_image.o lib/image.o lib/objet.o lib/config.o lib/utils.o -o bin/prog_image.out $(CFLAGS)

# ================= COMPILATION (Création des objets) =================

lib/main.o: src/main.c
	@mkdir -p lib
	$(CC) -c src/main.c -o lib/main.o $(CFLAGS)

lib/main_image.o: src/main_image.c
	@mkdir -p lib
	$(CC) -c src/main_image.c -o lib/main_image.o $(CFLAGS)

lib/commande_vocale.o: src/commande_vocale.c
	@mkdir -p lib
	$(CC) -c src/commande_vocale.c -o lib/commande_vocale.o $(CFLAGS)

lib/image.o: src/image.c
	@mkdir -p lib
	$(CC) -c src/image.c -o lib/image.o $(CFLAGS)

lib/objet.o: src/objet.c
	@mkdir -p lib
	$(CC) -c src/objet.c -o lib/objet.o $(CFLAGS)

lib/config.o: src/config.c
	@mkdir -p lib
	$(CC) -c src/config.c -o lib/config.o $(CFLAGS)

lib/utils.o: src/utils.c
	@mkdir -p lib
	$(CC) -c src/utils.c -o lib/utils.o $(CFLAGS)

# ================= NETTOYAGE =================

clean:
	rm -f lib/*.o

fclean: clean
	rm -f bin/*.out

re: fclean run