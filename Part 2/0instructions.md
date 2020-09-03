

Di seguito sono riportate le consegne per la seconda parte del progetto di laboratorio, da consegnare necessariamente prima dell'iscrizione all'esame finale di teoria.

La **seconda parte del progetto** richiede l'implementazione e l'analisi dei tempi di l'esecuzione di operazioni di inserimento e di ricerca in alberi binari di ricerca. Nello specifico, si richiede di implementare le operazioni di ricerca e inserimento per tre tipi diversi di alberi binari di ricerca: alberi binari di ricerca semplici, di tipo AVL e di tipo Red-Black. Si assuma che ogni nodo di un albero binario di ricerca contenga una chiave numerica (di tipo intero) e un valore alfanumerico (di tipo stringa). Non è richiesta l'implementazione dell'operazione di rimozione di un nodo (i test automatici di auto-valutazione sono preparati in modo da non eseguire mai l'istruzione di rimozione).


**Alberi binari di ricerca semplici**

Si ricorda che un albero binario di ricerca semplice deve soddisfare la seguente proprietà: per ogni nodo x
che non sia una foglia e per ogni nodo y nel sotto-albero sinistro (rispettivamente, destro) di x, la chiave associata a x è strettamente maggiore (rispettivamente, minore) della chiave associata a y. Si faccia riferimento all'Esercizio 16 per la descrizione delle operazioni di inserimento e ricerca di un nodo.


**Alberi binari di ricerca di tipo AVL**

Si ricorda che un albero binario di ricerca di tipo AVL, oltre a soddisfare la proprietà di un albero di ricerca semplice, deve soddisfare anche la seguente proprietà: per ogni nodo x
, le altezze dei sotto-alberi di sinistra e di destra nel nodo x differiscono al più di 1. Si faccia riferimento all'Esercizio 18 per la descrizione delle operazioni di ribilanciamento in seguito a inserimento di un nodo.


**Alberi binari di ricerca di tipo Red-Black**

Si ricorda che in un albero binario di ricerca di tipo Red-Black, ogni nodo ha associato un colore associato, che può essere rosso o nero. L'altezza nera del sottoalbero radicato in un nodo x
è definita come il massimo numero di nodi neri lungo un possibile cammino da x a una foglia. Un albero binario di ricerca Rosso-Nero deve soddisfare anche la seguente proprietà: per ogni nodo x, le altezze nere dei sotto-alberi di sinistra e di destra nel nodo x coincidono. 



**Complessità media ammortizzata**

Si richiede una stima dei tempi medi e ammortizzati per l'esecuzione di n operazioni di inserimento e ricerca nei tre tipi di alberi binari di ricerca sopra descritti. Per tale stima si potrà procedere nel modo seguente. Al variare del parametro n, ad esempio, fra 1000 e 1000000, si eseguono n volte le seguenti operazioni su un albero di ricerca inizialmente vuoto: si genera in modo pseudo-casuale un valore intero k, si ricerca un nodo con chiave k nell'albero e, qualora il nodo non esistesse, si inserisce un nuovo nodo con chiave k nell'albero. Si noti che al termine di tale procedura saranno state eseguite esattamente n operazioni di ricerca e m operazioni di inserimento, per un opportuno m≤n (l'albero binario di ricerca conterrà quindi al più n nodi). Nell'ipotesi che i numeri generati in modo pseudo-casuale varino in un dominio sufficientemente grande, il valore di m sarà probabilmente simile a quello di n e potrà quindi essere sostituito con n.

Il tempo ammortizzato per l'esecuzione di tali operazioni è dato dal tempo totale diviso il numero di operazioni di ricerca ed eventuale inserimento, ovvero:

    tempo ammortizzato = tempo totale / n.

Si richiede di stimare il tempo ammortizzato al variare di n con un errore relativo limitato superiormente da 0.01 (1%).



**Modalità di consegna**

Si richiede:

1) L'implementazione in un linguaggio a scelta (ad esempio, C, C++, Java) dei tre tipi di alberi binari di ricerca, in modo che le operazioni di inserimento e ricerca siano formalmente corrette. Per semplificare la valutazione di correttezza sono stati predisposti tre moduli "Virtual Programming Laboratory" (VPL) da utilizzare per caricare l'implementazione delle varie strutture dati. Una condizione necessaria alla valutazione dell'elaborato è il superamento di tutti i test previsti, per tutti e tre i tipi di alberi binari di ricerca. 

2) La stima dei tempi medi e ammortizzati di esecuzione per le tre strutture dati, al variare del parametro n (numero di iterazioni di ricerca ed eventuale inserimento di un nodo in un albero). Non essendovi particolari operazioni computazionalmente onerose per l'inizializzazione di un albero vuoto, non sarà necessario scomputare i tempi di inizializzazione. Gli algoritmi valutati in questa parte dovranno essere gli stessi di quelli presentati al punto 1) (ad esclusione, ovviamente, delle parti di codice che gestiscono l'input e l'output). I tempi ammortizzati di esecuzione devono essere misurati con un errore relativo massimo pari a 0.01 (1%), utilizzando un orologio di sistema monotono di tipo "stopwatch" e calcolandone preliminarmente la risoluzione. Dal momento che i tempi di esecuzione dipenderanno dalla particolare sequenza di chiavi generate, si richiede la stima del tempo medio ammortizzato e della sua deviazione standard. Anche per questa parte è stato predisposto un modulo VPL da utilizzare per caricare il programma che raccoglie i tempi medi e ammortizzati di esecuzione e le deviazioni standard per ciascuna delle tre strutture dati (in questo caso non sarà predisposto alcun test automatico, e per ovvie ragioni si sconsiglia l'esecuzione del programma lato server...). Tale programma dovrà produrre in output una sequenza di record nel formato "N T1 D1 T2 D2 T3 D3", dove N rappresenta il numero iterazioni di ricerca ed eventuale inserimento, Ti (per i=1,2,3) è una stima del tempo medio e ammortizzato di ciascuna operazione e Di una stima della relativa deviazione standard. Si consiglia di generare un centinaio di campioni della dimensione N che variano indicativamente fra 1000 e 100000, con una distribuzione esponenziale o geometrica (ovvero, i campioni di N tenderanno a essere più "densi" negli intervalli di valori bassi).

3) I dati raccolti al punto 2) devono essere presentati e discussi in una relazione, da caricare sul server in formato PDF. La valutazione della relazione contribuirà in modo significativo al voto finale del progetto di laboratorio. Non è necessario inviare una relazione con molte pagine: qualche decina di pagine è largamente sufficiente a discutere gli aspetti importanti dell'implementazione e dell'analisi dei tempi di esecuzione. Si consiglia l'uso di grafici comparativi, sia in scale lineari - N vs t(N) - che doppiamente logaritmiche - log(N) vs log(t(N)).