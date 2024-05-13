#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes

all: solveur

###

solveur: solveur.c median.c median.h
	$(CC) $(CFLAGS) $^ -lSDL2 -lm -o  $@


#Nettoyage
clean: 
	rm -f *.o
	rm -f *.svg
	rm -f *~
	rm solveur
