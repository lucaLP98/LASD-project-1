#include "book_tree.h"

int emptyBookTree(bookTree t){
    return (t == NULL);
}

bookTree allocateNewNodeBook(char newBook[]){
    bookTree tmp;

    tmp = (bookTree)malloc(sizeof(ABRbook));
    strcpy(tmp->book, newBook);
    tmp->available = DISPONIBILE;
    tmp->sx = NULL;
    tmp->dx = NULL;

    return tmp;
}

bookTree insertNewBook(bookTree t, char newBook[]){
    if( !emptyBookTree(t) ){
        if( strcmp(newBook, t->book) < 0 )
            t->sx = insertNewBook(t->sx, newBook);
        else if( strcmp(newBook, t->book) > 0 )
            t->dx = insertNewBook(t->dx, newBook);
    }else{
        t = allocateNewNodeBook(newBook);
    }

    return t;
}

void inOrderViewBook(bookTree t, unsigned int entitaChiamante){
    if( !emptyBookTree(t) ){
        inOrderViewBook(t->sx, entitaChiamante);

        if( entitaChiamante == BIBLIOTECA ){
            printf(" Disponibilita' : ");
            (t->available == DISPONIBILE) ? printf(" si ->\t") : printf(" no ->\t");
        }
        printf(" %s\n", t->book);

        inOrderViewBook(t->dx, entitaChiamante);
    }
}

bookTree searchBookInABR(bookTree t, char bookToSearch[]){
    if( !emptyBookTree(t) ){
        if( strcmp( bookToSearch, t->book ) < 0 )
            return searchBookInABR( t->sx, bookToSearch );

        if( strcmp( bookToSearch, t->book ) > 0 )
            return searchBookInABR( t->dx, bookToSearch );
    }

    return t;
}

bookTree deleteBook(bookTree t, char bookToDelete[], int *error){
    bookTree detachMinimum(bookTree t, bookTree p){
        if( !emptyBookTree(t) ){
            if( t->sx != NULL )
                return detachMinimum( t->sx, t );

            if( p->sx == t)
                p->sx = t->dx;
            else
                p->dx = t->dx;
        }

        return t;
    }

    bookTree deleteRoot(bookTree t){
        bookTree tmp;

        if(t != NULL){
            if( t->sx == NULL  || t->dx == NULL ){
                tmp = t;

                if(t->sx != NULL)
                    t = t->sx;
                else
                    t = t->dx;
            }else{
                tmp = detachMinimum( t->dx, t );
                strcpy(tmp->book, t->book);
            }

            free(tmp);
        }

        return t;

    }

    if( t != NULL){
        if( strcmp(bookToDelete, t->book) == 0 )
            t = deleteRoot( t );
        else if( strcmp(bookToDelete, t->book) < 0 )
            t->dx = deleteBook( t->dx, bookToDelete, error );
        else
            t->sx = deleteBook( t->sx, bookToDelete, error );
    }else{
        *error = 1;
    }

    return t;
}
