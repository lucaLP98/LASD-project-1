#ifndef STUDENT_TREE_H_INCLUDED
#define STUDENT_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_tree.h"

struct Tstudent{
    char matricola[20];
    bookTree books;
};
typedef struct Tstudent Student;

struct TabrStudent{
    Student student;

    struct TabrStudent* dx;
    struct TabrStudent* sx;
};
typedef struct TabrStudent ABRstudent;
typedef ABRstudent* studentTree;

studentTree initStudentTree(); //inizializza un albero di studenti
int emptyStudentTree(studentTree t); //restituisce 1 se l'albero degli studenti è vuoto, 0 altrimenti
void printStudent(Student s); //stampa uno studente (matricola e lista dei libri attualmente presi in prestito)
void inOrderViewStudent(studentTree t); //stampa l'albnero degli studenti mediante un algoritmo del tipo inOrder (stampando quindi in ordine alfabetico)
studentTree allocateNewNodeStudent(char newStudent[]); //crea un nuovo nodo Studente e lo restituisce al chiamante
studentTree insertNewStudent(studentTree t, char newStudent[], studentTree* newStudentNode); //inserisce un nuovo studente nell'albero e restituisce l'albero modificato
studentTree searchStudent(studentTree t, char studentToSearch[]); /*cerca uno studente nell'albero tramite il campo matricola
                                                                  e restituisce il sottoalbero avente come radice il nodo dello studente cercato.
                                                                  Restituisce NULL se non c'è nessuno studente associato alla matricola data in input*/

#endif // STUDENT_TREE_H_INCLUDED
