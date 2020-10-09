#ifndef Library_request_queue_h
#define Library_request_queue_h

#include <stdio.h>
#include <stdlib.h>

#define REQUEST_MAX 100

#define PRESTITO 1
#define RESTITUZIONE 0

struct Trequest{
    int requestType;
    char student[20];
    char book[100];
};
typedef struct Trequest request;

struct TQueue {
	int head;
	int tail;
    request requests[REQUEST_MAX];
};
typedef struct TQueue* requestQueue;

requestQueue initQueue(); // Inizializza una nuova coda e ritorna un puntatore ad una struct di tipo requestQueue
int emptyQueue(requestQueue q); // Ritorna 1 se la coda e' vuota, altrimenti torna 0
int fullQueue(requestQueue q); // Ritorna 1 se la coda e' piena, altrimenti torna 0

/* Accoda una richiesta nella coda
   "error", passato per riferimetno dall'esterno restera' 0 se non ci sono errori,
   altrimenti se l'accodamento non va a buon fine poiche' la coda e' piena, err sara' uguale a 5 */
void enqueue(requestQueue q, request newRequest, int* error);

/* Toglie un elemento dalla struttura
   "error", passato per riferimetno dall'esterno restera' 0 se non ci sono errori
   altrimenti se il decodamento non va a buon fine poiche' la coda e' vuota, err sara' uguale a 6 */
request dequeue(requestQueue q, int* error);

void printRequest(request req); //stampa una singola richiesta
void printQueue(requestQueue q, int* error); // Stampa la coda di richeste
void svuotaCoda(requestQueue q, int *error); //elimina tutti gli elementi presenti nella coda

#endif
