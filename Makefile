################################################################################
### Université de Nantes - Licence Informatique
###
### Algorithmique et Structures de Données (2)
################################################################################

CC = g++
CFLAGS  = -g -Wall -std=c++14

INCLUDES = -I.
LFLAGS = -lm

OBJ = procession.o couleur.o group.o demonstration.o person.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(TARGET)

main.o: main.cpp procession.hpp couleur.hpp group.hpp demonstration.hpp person.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

procession.o: procession.cpp procession.hpp person.hpp group.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c procession.cpp -o procession.o

couleur.o: couleur.cpp couleur.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c couleur.cpp -o couleur.o

group.o: group.cpp group.hpp person.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c group.cpp -o group.o

demonstration.o: demonstration.cpp demonstration.hpp procession.hpp person.hpp group.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c demonstration.cpp -o demonstration.o

person.o: person.cpp person.hpp group.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c person.cpp -o person.o

clean:
		rm -f *~ *.o main
