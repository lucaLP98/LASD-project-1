#ifndef BOOK_TREE_H_INCLUDED
#define BOOK_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOK_TITLE 100

#define DISPONIBILE 1
#define INDISPONIBILE 0

#define STUDENTE 1
#define BIBLIOTECA 0

struct TabrBook{
    char book[MAX_BOOK_TITLE];
    int available;
    struct TabrBook* dx;
    struct TabrBook* sx;
};
typedef struct TabrBook ABRbook;
typedef ABRbook* bookTree;

int emptyBookTree(bookTree t);  //restituisce 1 se l' ABR è vuoto, 0 altrimenti
bookTree allocateNewNodeBook(char newBook[]);   //alloca e restituisce un nuovo nodo per un ABR
bookTree insertNewBook(bookTree t, char newBook[]);     //inserisce un nuovo libro nell'ABR t
bookTree searchBookInABR(bookTree t, char bookToSearch[]); //restituisce il sottoalbero radicato nel nodo avente valore book uguale al libro cercato (passato come parametro) se presente, altrimenti restituisce NULL
void inOrderViewBook(bookTree t, unsigned int entitaChiamante); //stampa il libri presenti nell'albero t (se entitaChiamante == BIBLIOTECA viene stampata anche la disponibilità)
bookTree deleteBook(bookTree t, char bookToDelete[], int *error); //elimina il libro avente titolo indicato come parametro

#endif // BOOK_TREE_H_INCLUDED
