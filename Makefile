# Makefile - Simulador Artemis (Grupo 14)
# Uso:  make          -> compila el programa (./artemis)
#       make test     -> compila las pruebas de fisica (./test_fisica)
#       make clean    -> borra objetos y ejecutables

CC     = gcc
CFLAGS = -Wall -Iinclude
LIBS   = -lm

FUENTES = $(wildcard src/*.c)
OBJETOS = $(FUENTES:.c=.o)

artemis: $(OBJETOS)
	$(CC) $(OBJETOS) -o artemis $(LIBS)

# Regla para compilar cada .c en un .o (compilacion separada)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pruebas unitarias de fisica (tienen su propio main)
test: tests/test_fisica.c src/fisica.c
	$(CC) $(CFLAGS) tests/test_fisica.c src/fisica.c -o test_fisica $(LIBS)

clean:
	rm -f src/*.o artemis artemis.exe test_fisica test_fisica.exe

.PHONY: test clean
