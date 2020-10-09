#include "request_tree.h"

requestTree initRequestTree(){
    return NULL;
}

int emptyRequestTree(requestTree t){
    return (t == NULL);
}

void inOrderViewRequest(requestTree t, int *error){
    if( !emptyRequestTree(t) ){
        inOrderViewRequest(t->sx, error);
        printRequest(t->studentRequest);
        inOrderViewRequest(t->dx, error);
        *error = 0;
    }else{
        *error = 1;
    }
}

requestTree allocateNewNodeRequest(request newRequest){
    requestTree tmp;

    tmp = (requestTree)malloc(sizeof(requestABR));
    tmp->studentRequest = newRequest;
    tmp->sx = NULL;
    tmp->dx = NULL;

    return tmp;
}

requestTree insertNewRequestIntoTree(requestTree t, request newRequest){
    if( !emptyRequestTree(t) ){
        if( strcmp(newRequest.book, t->studentRequest.book) <= 0 )
            t->sx = insertNewRequestIntoTree(t->sx, newRequest);
        else if( strcmp(newRequest.book, t->studentRequest.book) > 0 )
            t->dx = insertNewRequestIntoTree(t->dx, newRequest);
    }else{
        t = allocateNewNodeRequest(newRequest);
    }

    return t;
}

requestTree searchRequestInRequestTree(requestTree t, char book[]){
    if( !emptyRequestTree(t) ){
        if( strcmp(book, t->studentRequest.book) < 0 )
            return searchRequestInRequestTree( t->sx, book );

        if( strcmp(book, t->studentRequest.book) > 0 )
            return searchRequestInRequestTree( t->dx, book );
    }

    return t;
}

requestTree deleteRequest(requestTree t, char book[]){
    requestTree detachMinimum(requestTree t, requestTree node){
        if( !emptyRequestTree(t) ){
            if( t->sx != NULL )
                return detachMinimum( t->sx, t );

            if( node->sx == t)
                node->sx = t->dx;
            else
                node->dx = t->dx;
        }

        return t;
    }

    requestTree deleteRoot(requestTree t){
        requestTree tmp;

        if( !emptyRequestTree(t)){
            if( t->sx == NULL  || t->dx == NULL ){
                tmp = t;

                if(t->sx != NULL)
                    t = t->sx;
                else
                    t = t->dx;
            }else{
                tmp = detachMinimum( t->dx, t );
                t->studentRequest = tmp->studentRequest;
            }

            free(tmp);
        }

        return t;
    }

    if( !emptyRequestTree(t) ){
        if( strcmp(book, t->studentRequest.book) == 0 )
            t = deleteRoot( t );
        else if( strcmp(book, t->studentRequest.book) > 0 )
            t->dx = deleteRequest( t->dx, book );
        else
            t->sx = deleteRequest( t->sx, book );
    }

    return t;
}
