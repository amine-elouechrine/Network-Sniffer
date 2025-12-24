CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/raw_socket.c src/packet_parser.c
OBJ = $(SRC:.c=.o)

# Cible principale
sniffer: $(OBJ)
	$(CC) $(CFLAGS) -o sniffer $(OBJ)

# Cible de test
test: src/packet_parser.c tests/test_parser.c
	$(CC) $(CFLAGS) -o run_tests src/packet_parser.c tests/test_parser.c
	./run_tests

# Générer la documentation
doc:
	doxygen Doxyfile

clean:
	rm -f sniffer run_tests src/*.o