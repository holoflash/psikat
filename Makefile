CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

main: main.c
	$(CC) main.c -o ./build/psikat $(CFLAGS)

run:
	./build/psikat