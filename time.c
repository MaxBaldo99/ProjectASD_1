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

    //2) ε = 1%
    //prima devo prendere ti = tempo inizializzaione vettore
    //==> tempo totale >= resolution * (1/ε + 1)
    int count = 0;
    clock_t start = clock;
    /*do {
        inizializza(); //meglio cambiare array disordinato ogni volta
        esegui();
        end = clock();
        count++;
    } while (end - start <= resolution * (1/e + 1));*/
    int tinit = 0;
    int t = (end - start) / count;
    int t2 = t - tinit;

    //3) scomputo inizializzazione

    //4) robustezza rumore (esterno all'algoritmo)
}