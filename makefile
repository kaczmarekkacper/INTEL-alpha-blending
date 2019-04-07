CC = g++
CFLAGS = -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.o
	$(CC) main.o -o main $(CLAGFS) $(LIBS) 

main.o: main.cpp
	$(CC) -c main.cpp $(CLFAGS) $(LIBS) 

clean:
	rm -f *.o main
