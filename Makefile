# ================= CONFIG =================

CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
SRC     = src/main.c src/commande_vocale.c
OBJ     = $(SRC:.c=.o)
BIN     = bin/prog

PYTHON  = python3
SIMU    = python/simulation.py

# ================= BUILD =================

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(BIN)

re: fclean all

# ================= EXECUTION =================

run: re
	@touch action.txt
	@$(BIN)

simulation:
	@echo "=== Simulation des actions ==="
	@$(PYTHON) $(SIMU)

.PHONY: all clean fclean re run simulation

bin/prog_principal.out: lib/main.o lib/commande_vocale.o lib/image.o lib/objet.o lib/config.o
	gcc lib/main.o lib/commande_vocale.o lib/image.o lib/objet.o lib/config.o -o bin/prog_principal.out -lm



lib/main.o: src/main.c
	gcc -c src/main.c -o lib/main.o -Wall -Iinclude -lm


lib/commande_vocale.o: src/commande_vocale.c include/commande_vocale.h
	gcc -c src/commande_vocale.c -o lib/commande_vocale.o -Wall -Iinclude -lm


bin/prog_image.out: lib/main_image.o lib/image.o lib/objet.o lib/config.o
	gcc lib/main_image.o lib/image.o  lib/objet.o lib/config.o -o bin/prog_image.out -lm

lib/main_image.o: src/main_image.c
	gcc -c src/main_image.c -o lib/main_image.o -Wall -lm

lib/image.o: src/image.c include/image.h
	gcc -c src/image.c -o lib/image.o -Wall -lm

lib/objet.o: src/objet.c include/objet.h
	gcc -c src/objet.c -o lib/objet.o -Wall -lm

lib/config.o: src/config.c include/config.h
	gcc -c src/config.c -o lib/config.o -Wall -lm

clean:
	rm -rf lib/*.o
