#ifndef PROJECTASD_1_TIME_H
#define PROJECTASD_1_TIME_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

//media
double mean (vector<duration<double>> vec);
//scarto quadratico medio
double meanSquaredError (vector<duration<double>> vec);
//scambia gli elementi
void swap(vector<duration<double>> vec, int start, int finish);
vector<duration<double>> resolutionVec(int n);
duration<double> initializeTime(int nElements, int repetitions);
duration<double> resolution();
vector<int> randomize(int nElements);

int updateNumOfElem(int i, int n);
int updateNumOfTimes(int n);
int calcNumOfArrays(int startingLength);

int minimum(vector<duration<double>> vec, int p, int q);
int median(vector<duration<double>> vec);


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
    return sum.count() / vec.size();
}

double meanSquaredError (vector<duration<double>> vec) {
    double sum;
    double m = mean(vec);
    for (duration<double> i : vec) {
        sum += pow(i.count()- m, 2);
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
        /*for(int j = 0; j < nElements; j++) {
            cout << j << "\t" << vec[j] << "\n";
        }*/
    }
    end = steady_clock::now();
    //delete vec;
    return (duration<double>)((end - start) / repetitions);
}

vector<int> randomize(int nElements) {
    srand(time(NULL));
    vector<int> vec = vector<int>(nElements);
    for (int i = 0; i < nElements; i++) {
        vec[i] = rand();
    }
    return vec;
}

int updateNumOfElem (int i, int n) {
    
    int k = i/9;
    k = pow(10, k);
    int increase = 100 * k;
    n += increase;
    if(n > 5 * pow(10, 6)) {
        return -1;
    } else {
        return n;
    }
}

int updateNumOfTimes (int n) { 
    return max(5, n - 7);
}

int calcNumOfArrays(int startingLength) {
    int i = 0;
    int length = startingLength;
    while(length != -1) {
        length = updateNumOfElem(i, length);
        i++;
    }
    return i;
}

//returns index of the minimum value in the array
int minimum(vector<duration<double>> vec, int p, int q) {
    int minIndex = p;
    for(int i = p + 1; i < q; i++) {
        if(vec[i] < vec[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

//returns index of the minimum value in the array
int median(vector<duration<double>> vec) {
    int medianIdx = 0;
    for(int i = 0; i < vec.size() / 2; i++) {
        int minIdx = minimum(vec, i, vec.size() - 1);
        swap(vec, i, minIdx);
        medianIdx++;
    }
    return medianIdx;
}

#endif //PROJECTASD_1_TIME_H