#ifndef PROJECTASD_1_TIME_H
#define PROJECTASD_1_TIME_H

#include "chrono"
#include "math.h"
#include <iostream>
#include "vector"
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

#define max(x, y) (((x) > (y)) ? (x) : (y))

/*
//ritorna altezza nodo, 0 se nodo è null
#define h(x) ((x == NULL) ? 0 : x->height)
//ritorna la altezza nodo->left - altezza nodo right. se nodo è null ritorna 0
#define hDiff(x) (x == NULL ? 0 : (h(x->left) - h(x->right)))
*/

//media
double mean (vector<duration<double>> vec);
//scarto quadratico medio
double meanSquaredError (vector<duration<double>> vec, double mean);
void swap(vector<duration<double>> vec, int start, int finish);
vector<duration<double>> resolutionVec(int n);
duration<double> initializeTime(int nElements, int repetitons);
duration<double> resolution ();


void time () {

    //1) prendere risoluzione

    //2) valutare errore relativo

    //Inizializzazione

    //steady_clock::time_point start, end;



    /*
    int count = 0;
    steady_clock::time_point t1, t2;
    vector<steady_clock> tinit = new vector<steady_clock>(100); //


    do {
        t1 = steady_clock::now(); //t1 tempo di inizo inzializzazione
        inizializa...
        t2 = steady_clock::now(); //t2 tempo di fine inizializzazione
        quickselect(...);
        steady_clock::time_point end = steady_clock::now();
        tinit[count] = t2-t1;
        count++;
    } while (end-start <= 101);

    steady_clock::time_point t2 = steady_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    cout << "It took me " << time_span.count() << " seconds.";
    cout << std::endl;*/

}

duration<double> resolution () {
    
    int n = 101;
    vector<duration<double>> res = vector<duration<double>>(n);
    res = resolutionVec(n);
    duration<double> resolution;

    //simple sort lol ahahahaha
    //todo: use select(res, n/2 + 1) instead of this shit
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (res[i] > res[j]) {
                swap(res, i, j);
            }
        }
    }
    resolution = res[n/2 + 1];
    //cout << "resolution: " << resolution.count() << endl;
    return resolution;
}

double mean (vector<duration<double>> vec) {
    duration<double> sum;
    for (auto i : vec) {
        sum += i;
    }
    return sum.count()/vec.size();
}

double meanSquaredError (vector<duration<double>> vec, double mean) {
    double sum;
    for (duration<double> i : vec) {
        sum += pow(i.count()- mean, 2);
    }
    return sqrt(sum/vec.size());
}

void swap(vector<duration<double>> vec, int start, int finish) {
    duration<double> aux = vec[start];
    vec[start] = vec[finish];
    vec[finish] = aux;
}

//n = 101 good
vector<duration<double>> resolutionVec(int n) {
    vector<duration<double>> res = vector<duration<double>>(n);
    steady_clock::time_point start, end;
    for (int i = 0; i < n; i++ ) {
        start = steady_clock::now();
        do {
            end = steady_clock::now();
        } while (end == start);
        res[i] = duration_cast<duration<double>>(end - start);
        //cout << res[i].count() << endl;
    }
    return res;
}

//measure medium time needed to allocate a nElements vector randomly, repetitions times
duration<double> initializeTime(int nElements, int repetitions) {
    steady_clock::time_point start, end;
    start = steady_clock::now();
    vector<int> vec;
    for (int i = 0; i < repetitions; i++) {
        vec = randomize(nElements);
    }
    end = steady_clock::now();
    //delete vec;
    return (duration<double>)((end - start) / repetitions);
}

vector<int> randomize(int nElements) {
    srand(time(NULL));
    vector<int> vec = vector<int>(nElements);
    for (int j : vec) {
        double x = rand();//*(i+1)*n*5;
        j = x;
    }
    return vec;
}

int updateNumOfElem (int nElements, int i) {
    //0 <= i <= 9 ==> nElements += 100
    //10 <= i <= 17 0 ==> nElements += 1.000
    //i > 17 ==> nElements += 10.000
    if(i < 18) {
        nElements += 100 * max(1, (i+1)/10*10);
        //nTimes -= 5;
    } else {
        nElements += 10000;
        //nTimes-- every two iterations, till when is equal to 2
        //nTimes = i % 2 == 0 ? max(2, nTimes - 1) : nTimes;
    }
    return nElements;
}

#endif //PROJECTASD_1_TIME_H
