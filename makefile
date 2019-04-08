CC = g++
CFLAGS = -m64 -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.o fun.o
	$(CC) main.o fun.o -o main $(CFLAGS) $(LIBS) 

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS) $(LIBS)
fun.o: fun.s
	nasm -f elf64 fun.s -o fun.o

clean:
	rm -f *.o
	rm -f out.bmp
	rm -f main
open:
	./main black.bmp white.bmp
