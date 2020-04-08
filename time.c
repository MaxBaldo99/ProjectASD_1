#include <stdio.h>
#include <time.h>


int main() {

    //1) resolution
    //eseguirlo 100 volte e fare minimo o mediana NO media
    clock_t start = clock;
    clock_t end;
    do {
        end = clock;
    } while (end == start);
    clock_t resolution = end - start;
    int e = 0;

    //2) ε = e = errore relativo = 1%
    /*
        x = tempo reale esecuzione select vettore N elementi
        N = numero elementi vettore
        se N < 10000 ==> x < res ==> non riesce a otterne il tempo
        x^ = tempo misurato di esecuzione (x +- res)
        x - res <= x^ <= x + res 
        ε = (x^ - x) / x
        - res/x <= ε <= + res/x
        obbiettivo: ε <= 1/100 = 0.01
        quindi: x^ >= 100 * res + res = res * (100 + 1) = 101 * res
    */
    //prima devo prendere ti = tempo inizializzaione vettore
    //==> tempo totale >= resolution * (1/e + 1)
    int count = 0;
    clock_t start = clock;
    do {
        inizializza(); //meglio cambiare array disordinato ogni volta
        esegui();
        end = clock();
        count++;
    } while (end - start <= resolution * (1/e + 1));
    int tInizializzazione = 0;
    int tTotale = (end - start) / count;
    int tEsecuzione = tTotale - tInizializzazione;

    //3) scomputo inizializzazione

    //4) robustezza rumore (esterno all'algoritmo)
}