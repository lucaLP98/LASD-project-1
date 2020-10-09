# LASD-project-1
First laboratory project of algorithms and data structures

<H1>Specifiche :</H1>
Si progetti un programma per la gestione di una biblioteca per studenti. Gli attori principali sono:
  • La biblioteca, un insieme di libri identificati da un titolo univoco;
  • Gli studenti, identificati da una matricola univoca.
  
Ogni studente può effettuare una richiesta, che può essere di due tipi:
  • Prendere in prestito un libro;
  • Restituire un libro (preso in prestito precedentemente).

Le richieste vanno soddisfatte seguendo l’ordine in cui esse vengono effettuate.

Si richiede di scegliere opportunamente le strutture dati per organizzare sia la biblioteca che le richieste degli studenti.

Prima dell’avvio del programma, si richiede di popolare la biblioteca con 15 libri.

All’avvio del programma, si richiede che l’utente possa eseguire le seguenti operazioni:
  1. Aggiungere una richiesta di uno studente;
  2. Prendere in carico una richiesta, ovvero:
    a. Soddisfare la richiesta oppure
    b. Sospendere la richiesta (se il libro richiesto è momentaneamente non disponibile)
  3. Terminare, solo se tutte le richieste sono state soddisfatte.

Implementare, inoltre, un criterio per evitare deadlock dovuti a richieste sospese, che non possono effettivamente essere soddisfatte.
