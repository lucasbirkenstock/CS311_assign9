CC=g++
CFLAGS=-Wall -std=c++11

all: prog9

prog9: main.o graph.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp graph.h
	$(CC) $(CFLAGS) -c $<

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o prog9
