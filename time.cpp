#include "chrono"
#include "math.h"
#include <iostream>
#include "vector"
#include <cstdlib>
using namespace std;
using namespace chrono;

//media
double mean (vector<duration<double>> vec);
//scarto quadratico medio
double meanSquaredError (vector<duration<double>> vec, double mean);
void swap(vector<duration<double>> vec, int start, int finish);

int main () {

    //Risoluzione
    int n = 101;
    vector<duration<double>> res = vector<duration<double>>(n);
    steady_clock::time_point start, end;
    duration<double> resolution;
    for (int i = 0; i < n; i++ ) {
        start = steady_clock::now();
        do {
            end = steady_clock::now();
        } while (end == start);
        resolution = duration_cast<duration<double>>(end - start);
        //cout << resolution.count() << endl;
        res[i] = resolution;
    }
    //simple sort lol ahahahaha
    //todo: use select(res, n/2 + 1) instead of this shit
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j<n; j++) {
            if (res[i] > res[j]) {
                swap(res, i, j);
            }
        }
    }
    //cout << "med merda: "<< endl;
    resolution = res[n/2 + 1];
    //cout << resolution.count() << endl;

    //Inizializzazione

    vector<duration<double>> tinit = vector<duration<double>>(n);
    //steady_clock::time_point start, end;
    duration<double> ti;
    start = steady_clock::now();
    srand(time(NULL));
    for (int i = 0; i < n; i++ ) {
        vector<int> vec = vector<int>((i+1)*n); //(i+1)*n
        for (int j : vec) {
            double x = rand()*(i+1)*n*5;
            j = x;
        }
    }
    end = steady_clock::now();
    ti = end - start;
    cout <<  ti.count()/n << endl;

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

    return 0;
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