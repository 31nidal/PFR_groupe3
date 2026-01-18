.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/commande_vocale.c
BIN = bin/prog_commande

# Cible par défaut : compile ET lance tout
all: $(BIN)
	@echo "=== Lancement de la simulation ==="
	python python/simulation.py & \
	sleep 1 && \
	echo "=== Lancement de la commande vocale ===" && \
	./$(BIN)

# Compilation
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN) action.txt commande.txt
