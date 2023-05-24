CC=gcc
CFLAGS=-c
FLAGS=-Wall -Werror -Wextra

all: main

main: graph

graph : graph.o notation.o output.o my_func.o
	$(CC) $(FLAGS) graph.o notation.o output.o my_func.o -o ../build/graph
	rm *.o

notation.o : notation.c notation.h
	$(CC) $(CFLAGS) $(FLAGS) notation.c

output.o : output.c output.h
	$(CC) $(CFLAGS) $(FLAGS) output.c

my_func.o : my_func.c my_func.h
	$(CC) $(CFLAGS) $(FLAGS) my_func.c

graph.o: graph.o
	$(CC) $(CFLAGS) $(FLAGS) graph.c

clean:
	rm -rf ../build/graph

rebuild: clean main