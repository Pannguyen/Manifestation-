################################################################################
### Université de Nantes - Licence Informatique
###
### Algorithmique et Structures de Données (2)
################################################################################

CC = g++
CFLAGS  = -g -Wall -std=c++14

INCLUDES = -I.
LFLAGS = -lm

OBJ = cortege.o couleur.o groupe.o manif.o personne.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(TARGET)

main.o: main.cpp cortege.hpp couleur.hpp groupe.hpp manif.hpp personne.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

cortege.o: cortege.cpp cortege.hpp personne.hpp groupe.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c cortege.cpp -o cortege.o

couleur.o: couleur.cpp couleur.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c couleur.cpp -o couleur.o

groupe.o: groupe.cpp groupe.hpp personne.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c groupe.cpp -o groupe.o

manif.o: manif.cpp manif.hpp cortege.hpp personne.hpp groupe.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c manif.cpp -o manif.o

personne.o: personne.cpp personne.hpp groupe.hpp
		$(CC) $(CFLAGS) $(INCLUDES) -c personne.cpp -o personne.o

clean:
		rm -f *~ *.o main
