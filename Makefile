# ================== COMPILATION C ==================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
INCLUDE = -Iinclude

SRC     = src/main.c src/commande_vocale.c
BIN     = bin/commande_vocale

# ================== PYTHON ==================

PYTHON  = venv/bin/python
VOICE   = python/assistant_vocal.py
SIMU    = python/simulation_controller.py

# ================== CIBLES ==================

all: run

bin:
	mkdir -p bin

$(BIN): bin $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(BIN)

# -------- Programme principal (menu infini) --------
run: $(BIN)
	@echo "=== Lancement du programme ==="
	./$(BIN)

# -------- Simulation Turtle --------
simu:
	@echo "=== Lancement de la simulation ==="
	$(PYTHON) $(SIMU)

# -------- Nettoyage --------
clean:
	rm -rf bin action.txt

clean-all:
	rm -rf bin action.txt lois.txt

.PHONY: all run simu clean clean-all
