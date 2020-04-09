#include "chrono"
#include "math.h"
#include <iostream>
#include "vector"
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

#define max(x, y) (((x) > (y)) ? (x) : (y))
//media
double mean (vector<duration<double>> vec);
//scarto quadratico medio
double meanSquaredError (vector<duration<double>> vec, double mean);
void swap(vector<duration<double>> vec, int start, int finish);
vector<duration<double>> resVector(int n);
duration<double> initializeTime(int nElements, int repetitons);

int main () {

    //1) prendere risoluzione
    int n = 101;
    vector<duration<double>> res = vector<duration<double>>(n);
    res = resVector(n);
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
    cout << "resolution: " << resolution.count() << endl;

    //2) valutare errore relativo

    //Inizializzazione

    //steady_clock::time_point start, end;
    /*
        nElements in array:
        100, 200, 300, ... , 1.000 (+ 100 each time) (10 array dimensions)
        1.000, 2.000, 3.000, ... , 10.000 (+ 1.000 each time) (9 array dimensions)
        10k, 20k, 30k, ... , 1mln (+ 10.000 each time) (99 array dimensions)
    */
    int nElements = 100;
    int rep = 118; //num total of array initialized: 10 + 9 + 99
    int nTimes = 100; //num of times we want to measure init time
    vector<duration<double>> tinit = vector<duration<double>>(rep);

    //output to file.txt
    ofstream myfile ("data.txt");
    if (myfile.is_open())
    {
        myfile << "n° elem\tinit time\tn° rip\n";
    }
    for(int i = 0; i < rep; i++) {
        tinit[i] = initializeTime(nElements, nTimes);
        //cout << (i+1) << ") n° elementi: " << nElements;
        //cout << " => init time " << tinit[i].count() / nTimes << endl;

        myfile << nElements << "\t" << tinit[i].count() << "\t" << nTimes << "\n";

        //0 <= i <= 9 ==> nElements += 100
        //10 <= i <= 17 0 ==> nElements += 1.000
        //i > 17 ==> nElements += 10.000
        nTimes = i % 1 == 0 ? max(2, nTimes - 1) : nTimes;
        if(i < 18) {
            nElements += 100 * max(1, (i+1)/10*10);
            //nTimes -= 5;
        } else {
            nElements += 10000;
            //nTimes-- every two iterations, till when is equal to 2
            //nTimes = i % 2 == 0 ? max(2, nTimes - 1) : nTimes;
        }
    }

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

//n = 101 good
vector<duration<double>> resVector(int n) {
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
duration<double> initializeTime(int nElements, int repetitons) {
    srand(time(NULL));
    steady_clock::time_point start, end;
    start = steady_clock::now();
    for (int i = 0; i < repetitons; i++) {
        vector<int> vec = vector<int>(nElements);
        for (int j : vec) {
            double x = rand();//*(i+1)*n*5;
            j = x;
        }
    }
    end = steady_clock::now();
    //delete vec;
    return (duration<double>)((end - start) / repetitons);

}