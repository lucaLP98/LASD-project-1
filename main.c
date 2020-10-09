/*
    Primo progetto: BIBLIOTECA

    Author : Pastore Luca - N86002599
    Traget : Università degli studi di napoli - Federico II
    Course : Laboratorio di Algoritmi e Strutture Dati
    Verison : 1.01  10 / 05 / 2020
*/

#include "library.h"
#include "student_requests.h"

int main(){
    library biblioteca;
    unsigned int operazioneDaSvolgere;
    requestQueue richiesteAttive;
    requestTree richiesteSospese;
    studentTree studenti;

    biblioteca = createLibrary(biblioteca, "libri_biblioteca.txt");
    richiesteAttive = initQueue();
    richiesteSospese = initRequestTree();
    studenti = initStudentTree();

    printf("\n BENVENUTO NELL'APPLICATIVO PER LA GESTIONE DELLA BIBLIOTECA");
    while(1){
        operazioneDaSvolgere = menu();
        operations(operazioneDaSvolgere, richiesteAttive, &richiesteSospese, &studenti, biblioteca);
        printf("\n\n ");
        system("PAUSE");
    }

    return 0;
}
