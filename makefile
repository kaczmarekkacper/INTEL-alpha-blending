CC = g++
CFLAGS = -m64 -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

all: main.o f.o
	$(CC) main.o f.o -o main $(CFLAGS) $(LIBS) 

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS) $(LIBS)
f.o: f.s
	nasm -f elf64 f.s -o f.o
clean:
	rm -f *.o
	rm -f out1.bmp out2.bmp
	rm -f main
open:
	./main black.bmp white.bmp
