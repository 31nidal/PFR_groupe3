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

clean:
	rm -f src/*.o

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
