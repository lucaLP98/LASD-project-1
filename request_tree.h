#ifndef REQUEST_TREE_H_INCLUDED
#define REQUEST_TREE_H_INCLUDED

#include "request_queue.h"
#include <string.h>

struct TabrRequest{
    request studentRequest;
    struct TabrRequest* dx;
    struct TabrRequest* sx;
};
typedef struct TabrRequest requestABR;
typedef requestABR* requestTree;

requestTree initRequestTree(); //inizializza un albero di richieste
int emptyRequestTree(requestTree t); //restituisce 1 se l'albero di richeste è vuoto, 0 altrimenti
void inOrderViewRequest(requestTree t, int *error); //stampa le richieste dell'albero utilizzando un algoritmo inOrder
requestTree searchRequestInRequestTree(requestTree t, char book[]); /*cercha una richiesta nell'albero mediante il libro richiesto passato come perametro
                                                                      e restituisce il sottoalbero avente per radice la richiesta cercata
                                                                      o NULL se la richiesta non è presente nell'albero*/
requestTree deleteRequest(requestTree t, char book[]); //elimina una richiesta dall'albero e restituisce l'albero modificato
requestTree allocateNewNodeRequest(request newRequest); //alloca un nuovo nodo richiesta
requestTree insertNewRequestIntoTree(requestTree t, request newRequest); //inserisce una nuova richiesta nell'albero

#endif // REQUEST_TREE_H_INCLUDED
