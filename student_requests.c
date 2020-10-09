#include "student_requests.h"

int menu(){
    int task;

    printf("\n\n _____________________________________________________________________");
    printf("\n\n Inserire il numero dell'operazione da eseguire e premere INVIO:\n\n  1. Aggiungere richiesta studente;\n  2. Prendere in carico una richiesta\n  3. Visualizza libri disponibili\n");
    printf("  4. Visualizza coda richieste attive\n  5. visualizza richieste sospese\n  6. Visualizza studenti e relativi prestiti attivi\n  0. Terminare\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &task);
        if(task < 0 || task > 6)
            printf("\n ERRORE ! Scelta non valida...\n\n Riprovare");
    }while(task < 0 || task > 6);

    return task;
}

request insertNewRequest(){
    request tmp;
    int tipoRichiesta;
    char buff[10];

    printf("\n  - Inserire tipologia richiesta e premere INVIO:\n\n    1. Prestito di un libro\n    2. Restituzione di un libro\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &tipoRichiesta);
        if(tipoRichiesta < 1 || tipoRichiesta > 2)
            printf("\n ERRORE ! Inserire una tipologia valida...\n\n Riprovare");
    }while(tipoRichiesta < 1 || tipoRichiesta > 2);

    tmp.requestType = (tipoRichiesta == PRESTITO) ? PRESTITO : RESTITUZIONE;

    gets(buff);

    printf("\n  - Inserire il libro >>> ");
    gets(tmp.book);
    printf("\n  - Inserire la matricola dello studente che ha effettuato la richiesta >>> ");
    gets(tmp.student);

    return tmp;
}

requestTree addToSuspendedRequest( requestTree suspendedRequests, request newSuspendedRequest ){
    int scelta;

    printf("\n\n Il libro non e' al momento disponibile\n\n Seleziona l'opzione che desideri eseguire e premere INVIO:\n\n  1. Annulla richiesta\n  2. Aggiungi a richieste sospese, la richiesta verra' completata appena il libro verrà restituito\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &scelta);
        if(scelta < 1 || scelta > 2)
            printf("\n\n ERRORE! Scelta non valida, inserire un'opzione valida...\n Riprovare");
    }while(scelta < 1 || scelta > 2);

    if(scelta == 2){
        suspendedRequests = insertNewRequestIntoTree(suspendedRequests, newSuspendedRequest);
        printf("\n\n La richiesta e' stata aggiunta alle richieste sospese\n appena possibile verra' soddisfatta.\n\n");
    }else{
        printf("\n\n RICHIESTA ANNULLATA CON SUCCESSO !\n\n Ci dispiace per il disagio.");
    }

    return suspendedRequests;
}

studentTree assignBookToStudent(studentTree studenti, request richiesta){
    studentTree studenteRichiedente = NULL;

    studenteRichiedente = searchStudent( studenti, richiesta.student );

    if( studenteRichiedente == NULL ){
        studenti = insertNewStudent(studenti, richiesta.student, &studenteRichiedente);
    }

    studenteRichiedente->student.books = insertNewBook(studenteRichiedente->student.books, richiesta.book);

    return studenti;
}

void gestisciPrestito(studentTree* studenti, request richiesta, requestTree* richiesteSospese, library biblioteca){
    bookTree requiredBook = searchBookInLibrary(biblioteca, richiesta.book); //verifico se la biblioteca possiede il libro

    if( requiredBook != NULL ){
        if( checkAvailability(requiredBook) == DISPONIBILE ){ //la biblioteca possiede il libro, controllo la disponibilità
            //IL LIBRO E' DISPONIBILE E VIENE ASSEGNATO ALLO STUDENTE CHE NE FA RICHIESTA
            requiredBook->available = INDISPONIBILE;
            *studenti = assignBookToStudent(*studenti, richiesta);
            printf("\n\n LA RICHIESTA DI PRESTITO E' STATA APPROVATA !\n\n");
        }else{
            //IL LIBRO E' STATO GIA PRESO IN PRESTITO DA QUALCHE ALTRO STUDENTE
            //aggiungo il libro alle richieste sospese o annullo la richiesta (a discrezione del utente)
            *richiesteSospese = addToSuspendedRequest( *richiesteSospese, richiesta );
        }
    }else
        //LA BIBLIOTECA NON POSSIEDE IL LIBRO CERCATO
        printf("\n\n La biblioteca non dispone di questo libro\n\n");
}

void gestisciRestituzione( studentTree* studenti, request richiesta, requestTree* richiesteSospese, library biblioteca ){
    bookTree tmp;
    studentTree studente;
    requestTree richiestaPrestito;
    int error = 0;

    studente = searchStudent(*studenti, richiesta.student);
    if(studente == NULL){
        printf("\n Lo studente non ha mai richiesto alcun libro.\n\n");
    }else{
        studente->student.books = deleteBook(studente->student.books, richiesta.book, &error);
        if(error > 0){
            //LO STUDENTE CERCA DI RESTITUIRE UN LIBRO CHE NON HA MAI PRESO IN PRESTITO
            printf("\n Lo studente non ha mai preso in prestito questo libro.\n\n");
        }else{
            //LO STUDENTE RESTITUSCE IL LIBRO
            //cerco se c'è qualche richiesta sospesa che aspettava il libro restituito
            richiestaPrestito = searchRequestInRequestTree(*richiesteSospese, richiesta.book);
            if(richiestaPrestito != NULL){
                //esiste almeno una richiesta sospesa che attendeva il libro, assegno il libro allo studente titolare di tale richiesta
                *studenti = assignBookToStudent(*studenti, richiestaPrestito->studentRequest);
                printf("\n IL LIBRO E' STATO RESTITUITO E ASSEGNATO ALLO STUDENTE %s CHE NE HA FATTO PRECEDENTEMENTE RICHIESTA\n\n", richiestaPrestito->studentRequest.student);
            }else{
                //non c'è nessuna richiesta sospesa che attende il libro, imposto tale libro come di nuovo disponibile nella biblioteca
                tmp = searchBookInLibrary(biblioteca, richiesta.book);
                tmp->available = DISPONIBILE;
                printf("\n LA RESTITUZIONE DEL LIBRO E' AVVENUTA CON SUCCESSO\n\n");
            }
            *richiesteSospese = deleteRequest(*richiesteSospese, richiesta.book); //elimino la richiesta sospesa
        }
    }
}

void operations(const unsigned int task, requestQueue richiesteAttive, requestTree* richiesteSospese, studentTree* studenti, library biblioteca){
    request tmp;
    int error;

    switch(task){

    //AGGIUNTA DI UNA NUOVA RICHIESTA
    case 1:
        tmp = insertNewRequest();
        enqueue(richiesteAttive, tmp, &error);
        if(error > 0)
            printf("\n\n ERRORE! Operazione non eseguita...\n\n");
        else
            printf("\n\n OPERAZIONE COMPLETATA CON SUCCESSO !");
    break;

    //PRENDERE IN CARICO UNA RICHIESTA
    case 2:
        tmp = dequeue(richiesteAttive, &error); //estrazione richiesta da prendere in carico

        if( error == 0 ){
            printf("\n Richiesta presa in carico:\n\n");
            printRequest(tmp);

            if(tmp.requestType == PRESTITO){
                /*ESAUDISCO UNA RICHIESTA DI PRESTITO SE IL LIBRO RICHIESTO E' DISPONIBILE
                  ALTRIMENTI, A DISCREZIONE DELL'UTENTE POSSO: AGGIUNGO LA RICHIESTA ALL'INSIEME
                  DELLE RICHIESTE SOSPESE O ANNULLARE LA RICHIESTA */
                gestisciPrestito(studenti, tmp, richiesteSospese, biblioteca);
            }else{
                /*ESAUDISCO UNA RICHIESTA DI RESTITUZIONE
                  se l'utente che effettua la richiesta non ha mai preso in prestito il libro, la richiesta viene annullata;
                  se il libro restituito dall'utente è richiesto anche da un altro studente (la cui richiesta sta tra le richieste sospese),
                  allora il libro viene prestato al primo studente che ne ha fatto richiesta;
                  se nessun'altro studente ha richiesto tale libro, allora viene restituito alla biblioteca*/
                gestisciRestituzione(studenti, tmp, richiesteSospese, biblioteca);
            }
        }else{
            printf("\n\n Non ci sono richieste da esaudire\n\n");
        }
    break;

    case 3:
        //VISUALIZZAZIONE A VIDEO DEI LIBRI (CON RELATIVA DISPONIBILITA') PRESENTI NELLA BIBLIOTECA
        printAllBooksOfLibrary(biblioteca);
    break;

    case 4:
        //VISUALIZZO LA CODA DELLE RICHIESTE ATTIVE, cioè le richieste che devono ancora essere prese in carico
        printf("\n\n Le richieste attive sono:\n\n");
        printQueue(richiesteAttive, &error);
        if(error > 0)
            printf(" Non ci sono richieste attive\n\n");
    break;

    case 5:
        //VISUALIZZO LE RICHIESTE SOSPESE
        printf("\n\n Le richieste sospese sono:\n\n");
        inOrderViewRequest(*richiesteSospese, &error);
        if(error > 0)
            printf(" Non ci sono richieste sospese\n\n");
        //inserire la possibilita di cancellare richieste sospese (se non è vuoto l'abr)
    break;

    case 6:
        //VISUALIZZO TUTTI GLI STUDENTI PRESENTI NEL SISTEMA CON I RELATIVI PRESTITI ATTIVI
        if(*studenti != NULL){
            printf("\n\n Studenti con relativi prestiti attivi presenti nel sistema :\n");
            inOrderViewStudent(*studenti);
        }else{
            printf("\n\n Ancora nessuno studente iscritto nel sistema\n\n");
        }
    break;

    case 0:
        //TERMINAZIONE DELL'APPLICATIVO
        if(emptyQueue(richiesteAttive) && emptyRequestTree(*richiesteSospese)){ //controllo se non ci sono più richieste attive o sospese
            printf("\n\n\n _____________________________________________________________________\n\n GRAZIE PER AVER UTILIZZATO LA NOSTRA APPLICAZIONE !\n\n Develop By Luca Pastore - N86/2599\n\n\n");
            system("PAUSE");
            exit(0);
        }else{
            //l'applicativo non può essere terminato perchè sono ancora presenti richieste da esaudire
            printf("\n Impossibile terminare il programma perche' ci sono ancora richieste da soddisfare e/o sospese\n\n");
        }
    break;
    }
}
