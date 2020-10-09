#include "library.h"

library initLibrary(library lib){
    int i;

    for(i=0;i<28;i++){
        lib.books[i] = NULL;
    }

    return lib;
}

char *stringLower(char *str){
    int i = -1;
    char *newStr = (char *)malloc((strlen(str)+1)*sizeof(char));

    while(str[++i] != '\0')
        newStr[i] = (char)tolower(str[i]);

    newStr[i] = '\0';

    return newStr;
}

int selectSection( const char book[] ){
    unsigned int section;

    switch(book[0]){
        case 'a': case 'A': section = A; break;
        case 'b': case 'B': section = B; break;
        case 'c': case 'C': section = C; break;
        case 'd': case 'D': section = D; break;
        case 'e': case 'E': section = E; break;
        case 'f': case 'F': section = F; break;
        case 'g': case 'G': section = G; break;
        case 'h': case 'H': section = H; break;
        case 'i': case 'I': section = I; break;
        case 'j': case 'J': section = J; break;
        case 'k': case 'K': section = K; break;
        case 'l': case 'L': section = L; break;
        case 'm': case 'M': section = M; break;
        case 'n': case 'N': section = N; break;
        case 'o': case 'O': section = O; break;
        case 'p': case 'P': section = P; break;
        case 'q': case 'Q': section = Q; break;
        case 'r': case 'R': section = R; break;
        case 's': case 'S': section = R; break;
        case 't': case 'T': section = T; break;
        case 'u': case 'U': section = U; break;
        case 'v': case 'V': section = V; break;
        case 'w': case 'W': section = W; break;
        case 'x': case 'X': section = X; break;
        case 'y': case 'Y': section = Y; break;
        case 'z': case 'Z': section = Z; break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            section = NUMBER;
        break;
        default: section = SPECIAL_CHARACTER; break;
    }

    return section;
}

library createLibrary(library lib, const char file[]){
	FILE *filePtr;
	char book[MAX_BOOK_TITLE];
	unsigned int section;

	if((filePtr = fopen(file, "r")) == NULL){
		printf("\n ERRORE APERTURA FILE\n");
		exit(-1);
	}else{
        lib = initLibrary(lib);

		while( fgets(book, MAX_BOOK_TITLE, filePtr) != NULL ){
            if(book[strlen(book)-1] == '\n')
                book[strlen(book)-1] = '\0';

            section = selectSection( book );
            lib.books[section] = insertNewBook(lib.books[section], stringLower(book));
		}

		fclose(filePtr);
	}

	return lib;
}

void printAllBooksOfLibrary(library lib){
    int i;

    printf("\n I libri presenti nella biblioteca in ordine alfabetico sono:\n\n");
    for(i=0;i<28;i++){
        inOrderViewBook(lib.books[i], BIBLIOTECA);
        if(lib.books[i] != NULL)
            printf("\n");
    }
}

int checkAvailability( bookTree book ){
    return book->available;
}

bookTree searchBookInLibrary(library lib, char bookToSearch[]){
    int section = selectSection( bookToSearch );

    return searchBookInABR(lib.books[section], stringLower(bookToSearch));
}
