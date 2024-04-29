#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes

all: generateur solveur-prototype

###

generateur: generateur.c
	$(CC) $(CFLAGS) $< -o $@

solveur: solveur-prototype.c  
	$(CC) $(CFLAGS) $^ -lm -o $@


#Nettoyage
clean: 
	rm -f *.o
	rm -f *.svg
	rm -f *~
	rm generateur solveur-prototype
