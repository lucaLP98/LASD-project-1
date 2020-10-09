#include "request_queue.h"

// Inizializza la coda
requestQueue initQueue() {
    requestQueue q;

	q = malloc(sizeof(struct TQueue));
    q->head = -1;
    q->tail = 0;

    return q;
}

// Ritorna 1 se la coda e' vuota, 0 altrimenti
int emptyQueue(requestQueue q){
    return q->head == -1;
}

// Ritorna 1 se la coda e' piena, 0 altrimenti
int fullQueue(requestQueue q){
    return q->head == q->tail;
}

// Accoda una nuova richiesta 'newRequest' data in ingresso
void enqueue(requestQueue q, request newRequest, int *error){

	if (!fullQueue(q)) {
        q->requests[q->tail] = newRequest; // Inserisci valore in coda

        if (emptyQueue(q)) {
            q->head = 0; // Se e' vuota, sposto la testa in prima posizione
        }

        q->tail = (q->tail == REQUEST_MAX-1) ? 0 : q->tail + 1;

        *error = 0;
    } else {
        *error = 5;
    }
}

// Toglie una richiesta dalla coda
request dequeue(requestQueue q, int *error){
    request tmp;

    if (!emptyQueue(q)) {
        tmp = q->requests[q->head]; // Prendo la richiesta in 'head' della coda

        q->head = (q->head == REQUEST_MAX - 1) ? -1 : q->head + 1;

        if (fullQueue(q)) {
            q->head = -1;
            q->tail = 0;
        }

        *error = 0;
    } else {
        *error = 6;
    }

    return tmp;
}

// Salva la coda in reverse
void reverseQueue(requestQueue q, int *error){
    request tmp;

    if (!emptyQueue(q)) {
        tmp = dequeue(q, error);
        reverseQueue(q, error);
        enqueue(q, tmp, error);
    } else {
        *error = 8;
    }
}

void printRequest(request req){
    (req.requestType == PRESTITO) ? printf(" Tipologia: Prestito\t\t") : printf(" Tipologia: Restituzione\t");
    printf("Studente: %s\tLibro: %s\n", req.student, req.book);
}

// Stampa la coda
void printQueueInc(requestQueue q, int *error){
    request tmp;

    if (!emptyQueue(q)) {
        tmp = dequeue(q, error);
        printRequest(tmp);
        printQueueInc(q, error);
        enqueue(q, tmp, error);
    } else {
        *error = 7;
    }
}

// Stampa la coda
void printQueue(requestQueue q, int *error){
    printQueueInc(q, error); // Stampa la coda
    reverseQueue(q, error); // Riordina la coda prima di uscire
}

void svuotaCoda(requestQueue q, int *error){
    while( !emptyQueue(q) ){
        dequeue(q, error);
    }
}
