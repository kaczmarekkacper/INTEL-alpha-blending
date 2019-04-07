CC = g++
CFLAGS = -m32 -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.o f.o
	$(CC) main.o -o main $(CLAGFS) $(LIBS) 

main.o: main.cpp
	$(CC) -c main.cpp $(CLFAGS) $(LIBS)
f.o: f.s
	nasm -f elf f.s

clean:
	rm -f *.o main out.bmp
