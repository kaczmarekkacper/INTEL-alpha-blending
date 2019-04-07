CC = g++
CFLAGS = -m32 -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.o
	$(CC) $(CLAGFS) $(LIBS) main.o -o main

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.o test
