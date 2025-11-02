# Progetto Java: Gestione di una Biblioteca

## Descrizione del progetto
Crea un'applicazione Java per gestire una biblioteca. Il sistema deve permettere di gestire libri, utenti e prestiti di libri.

## Requisiti funzionali

### 1. Classi principali
- **Libro**: rappresenta un libro nella biblioteca. Attributi:
  - `titolo` (String)
  - `autore` (String)
  - `ISBN` (String)
  - `numeroCopieDisponibili` (int)
  
- **Utente**: rappresenta un utente registrato nel sistema. Attributi:
  - `nome` (String)
  - `cognome` (String)
  - `idUtente` (String)
  - `numeroLibriInPrestito` (int)
  
- **Prestito**: rappresenta un prestito di un libro da parte di un utente. Attributi:
  - `idPrestito` (String)
  - `idUtente` (String)
  - `isbnLibro` (String)
  - `dataInizioPrestito` (LocalDate)
  - `dataScadenzaPrestito` (LocalDate)

### 2. Funzionalità principali
- **Aggiungi un libro**: Il sistema deve permettere di aggiungere nuovi libri alla biblioteca.
- **Registra un nuovo utente**: Il sistema deve permettere di registrare nuovi utenti.
- **Effettua un prestito**: Il sistema deve permettere di effettuare un prestito se ci sono copie disponibili del libro richiesto e l'utente non ha superato il limite massimo di prestiti (ad esempio, 3 libri).
- **Restituisci un libro**: Il sistema deve permettere la restituzione di un libro e aggiornare il numero di copie disponibili.
- **Visualizza tutti i libri**: Il sistema deve mostrare una lista di tutti i libri con il numero di copie disponibili.
- **Visualizza i prestiti attivi**: Il sistema deve mostrare tutti i prestiti attivi, con i dettagli del libro e dell'utente.
- **Ricerca di un libro**: Il sistema deve permettere di cercare un libro per titolo o autore.

### 3. Gestione delle eccezioni
- Gestione di errori come il tentativo di prendere in prestito un libro non disponibile o la registrazione di un utente con un ID già esistente.

### 4. Persistenza dei dati
- Implementa la possibilità di salvare i dati (libri, utenti, prestiti) su file e di caricarli all'avvio del programma, in modo che le informazioni persistano tra diverse esecuzioni del programma.

## Possibile estensione
- **Interfaccia grafica (facoltativa)**: Implementa una semplice GUI usando JavaFX per rendere l'applicazione più interattiva e user-friendly.
- **Notifiche**: Aggiungi un sistema di notifica per avvisare gli utenti quando devono restituire un libro.

## Struttura del codice
Il progetto potrebbe essere strutturato in pacchetti come segue:

- `biblioteca.models` - per le classi di modello come `Libro`, `Utente`, `Prestito`.
- `biblioteca.services` - per i servizi che gestiscono la logica di business come `GestioneLibri`, `GestioneUtenti`, `GestionePrestiti`.
- `biblioteca.utils` - per eventuali utilità come la gestione dei file per la persistenza.
- `biblioteca.main` - per la classe principale con il metodo `main` che avvia l'applicazione.

## Conclusione
Questo progetto ti permetterà di esercitarti su molti concetti chiave di Java e, se implementato correttamente, potrebbe anche costituire un ottimo esempio da presentare all'esame.

