.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/commande_vocale.c
BIN = bin/prog_commande

# Cible par défaut : compile ET lance tout
all: $(BIN)


# Compilation
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN) action.txt commande.txt
