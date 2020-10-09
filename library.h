#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "book_tree.h"
#include <ctype.h>

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7
#define H 8
#define I 9
#define J 10
#define K 11
#define L 12
#define M 13
#define N 14
#define O 15
#define P 16
#define Q 17
#define R 18
#define S 19
#define T 20
#define U 21
#define V 22
#define W 23
#define X 24
#define Y 25
#define Z 26
#define SPECIAL_CHARACTER 27
#define NUMBER 0

struct arrayOfTree{
    bookTree books[28];
};
typedef struct arrayOfTree library;

library initLibrary(library lib);   //inizializza la libreria (ponendo a NULL ogni elemento di lib)
library createLibrary(library lib, const char file[]); //inserisce i libri presenti su file in un array di ABR (library), predisponendoli in base all'ordinamento alfabetico
int checkAvailability( bookTree book ); //restituisce 1 se il libro cercato è disponibile, 0 altrimenti
bookTree searchBookInLibrary(library lib, char bookToSearch[]); //effettua la ricerca di un libro nell'intera biblioteca (utilizza searchBookInABR, selezionando l'ABR giusto in base all'iniziale del libro da cercare)
void printAllBooksOfLibrary(library lib);   //stampa tutti i libri presenti nella biblioteca in ordine alfabetico (utilizza inOrderView)

#endif // LIBRARY_H_INCLUDED
