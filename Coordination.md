# Progetto Non-Gravitar
*(Internal coordination for the Non-Gravitar project, written in italian.)*

### Requisiti di codice
L'implementazione del progetto si divide in una fase di design e in una
implementativa. La struttura sarà fortemente modularizzata (suddivisa in
blocchetti) la cui implementazione viene assegnata individualmente.
La parte di design è invece a carico di Oscar principalmente, ma chiunque potrà
offrire critiche e suggerimenti, a patto che apportino beneficio alla qualità
o performance del codice.

Regole e convenzioni di progetto possiedono una natura "emergente", nel senso
di essere introdotte in fase di lavorazione, e solo se ritenute necessarie. Ciò
esclude regole a priori o che non abbiano una vera motivazione.

Tra le regole e convenzioni attuali sono comprese:
1. Scrittura di codice sorgente che non superi i `79` caratteri (inclusi file
`.md`, `.cpp`, `.hpp`, ...).
2. Nomenclatura: classi in
[UpperCamelCase](https://en.wikipedia.org/wiki/Camel_case); variabili, funzioni
e metodi in `lowerCamelCase` (o meglio `snake_case`? TODO decidi). Spaziatura
e cose meno importanti discusse oralmente.
3. Testare il proprio codice. Verranno fornite piccole suite di test da
   eseguire prima di revisionare il proprio codice. (TODO aggiorna il punto
   quando avrai dettagli più precisi.)
4. Segnare con un commento `TODO` quelle parti di codice su cui ritornare in
   futuro (motivazione: facile ricercare tutti i punti da ritoccare in un
   secondo momento).

### Obiettivi medio termine
1. Prendere familiarità con la
[libreria grafica SFML](https://www.sfml-dev.org/).
2. Ottenere padronanza con un nucleo di funzionalità del C++ e della sua
   libreria standard minimale ma necessario: tipi base, puntatori e *soft
   references*; strutture, unioni ed enumerazioni; gestione delle eccezioni e
   *namespaces*; sviluppo in classi: costruttori e distruttori; costruzione per
   copia e per riferimento (*move construction*); templates; libreria base ed
   espressioni regolari; ... .
3. *(Soddisfa il punto 1.)* Sviluppare individualmente uno o più dei seguenti
progetti (in ordine sparso di difficoltà) utilizzando SFML:
	1. Generatore di frattali, a scelta tra: il frattale di Sierpinski, [il
	   frattale di Koch](https://en.wikipedia.org/wiki/Koch_snowflake), o
	   quelli contenuti in
	   [List of fractals ...](https://en.wikipedia.org/wiki/List_of_fractals_by_Hausdorff_dimension).
	2. Freccia (stile navicella spaziale) liberamente spostabile all'interno
	   della visuale di una finestra: sono presenti i comandi per accelerare e
	   ruotare il veicolo. Quando la particella raggiunge uno dei bordi della
	   visuale, decidere se lasciar rimbalzare i veivolo o farlo ricomparire
	   nel lato opposto.
	3. Prototipo *minimale* di
	   [Osmos](https://play.google.com/store/apps/details?id=com.hemispheregames.osmosdemo):
	   tante particelle più o meno piccole distribuite sulla visuale della
	   finestra. Quella in movimento e comandata dal giocatore *assorbe* le
	   particelle più piccole e *viene assorbita* da quelle più grandi. (Non è
	   necessario implementare animazioni, transizioni ed effetti speciali di
	   qualunque genere.)
4. *(Per gli incaricati al design.)* Definire una struttura provvisoria dei
   moduli di progetto.
