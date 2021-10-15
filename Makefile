CC=gcc
CFLAGS=-Wall

all: main.c maze.o
	$(CC) $(CFLAGS) main.c maze.o -o main -lgraph

maze.o :
	$(CC) $(CFLAGS) maze.c -c -lgraph