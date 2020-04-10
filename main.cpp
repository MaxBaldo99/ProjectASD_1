#include <assert.h>
#include "utility.h"
#include "time.h"
#include "chrono"
#include <fstream>
using namespace chrono;

void quickSort(int* vec, int p, int q);
int quickSelect(int* vec, int p, int q, int k);
int heapSelect(MinHeap h1, MinHeap h2, int k);
vector<duration<double>> initialization();
vector<duration<double>> execution(vector<int> vec, int k);

int nOfArrays = 118; //num total of array initialized: 10 + 9 + 99

/*
    IMPARA:
    '\n' >>>>>>>>>>>>>>> endl
*/

int main() {
    vector<int> vec;
    //cin >> vec;
    int k;
    cin >> k;
    duration<double> res = resolution();
    cout << "inizializzo\n";
    vector<duration<double>> tinit = initialization();
    cout << "eseguo\n";
    vector<duration<double>> ttot = execution(vec, k);
    vector<duration<double>> texec(nOfArrays);
    ofstream myfile ("exec.txt");
    cout << "scrivo su file\n";
    if (myfile.is_open())
    {
        myfile << "exec time\n";
    }
    for(int i = 0; i < nOfArrays; i++) {
        texec[i] = ttot[i] - tinit[i];
        myfile << texec[i].count() << "\n";
    }
    //cout << quickSelect(&vec[0], 0, vec.size()-1, k) << endl;
    return 0;
}

void quickSort(int* vec, int p, int q) {
    if (p < q) {
        int r = partition(vec, p, q);
        quickSort(vec, p , r - 1);
        quickSort(vec, r + 1, q);
    }
}

/**
 * The procedure return the k-esim element (in k position) in the array vec.
 * WE ASSUME THAT K IS A VALID INDEX OF THE ARRAY
 * @param vec is the vec to select the element
 * @param p is the index where to start searching in the array vec
 * @param q is th index where to finish searching the array vec
 * @param k is the position which is the element to return. REQUIRED is major or equal 0 and minus or equals vec.length -1
 * @return the element in the k position
 */
int quickSelect(int* vec, int p, int q, int k) {

    assert (k > 0 && k <= q - p + 1);       // we assume that k is in the interval of p and q

    int index = partition(vec, p, q);

    if (index - p == k - 1) {
        return vec[index];
    }

    if (index - p > k - 1) {
        return quickSelect(vec, p, index - 1, k);
    }

    return quickSelect(vec, index + 1, q, k - index + p - 1);
}

int heapSelect(MinHeap h1, MinHeap h2, int k) {
    h1.buildMinHeap();
    cout << h1.vec;
    h2.insert(0);       //inserisco la posizione nella seconda miHeap
    for (int i = 0; i < k-1; ++i) {
        int nodePosition = h2.extract();
        if (nodePosition == 0) {
            h2.insert(2 * nodePosition + 1);
            h2.insert(2 * nodePosition + 2);
        } else {
            h2.insert(2 * nodePosition);
            h2.insert(2 * nodePosition + 1);
        }
    }
    int last = h2.extract();
    return h1.vec[last];
}

vector<duration<double>> initialization() {
    /*
        nElements in array:
        100, 200, 300, ... , 1.000 (+ 100 each time) (10 array dimensions)
        1.000, 2.000, 3.000, ... , 10.000 (+ 1.000 each time) (9 array dimensions)
        10k, 20k, 30k, ... , 1mln (+ 10.000 each time) (99 array dimensions)
    */
    int nElements = 100;
    int nTimes = 100; //num of times we want to measure init time
    vector<duration<double>> tinit = vector<duration<double>>(nOfArrays);

    //output to file.txt
    ofstream myfile ("init.txt");
    if (myfile.is_open())
    {
        myfile << "n° elem\tinit time\tn° rip\n";
    }
    for(int i = 0; i < nOfArrays; i++) {
        tinit[i] = initializeTime(nElements, nTimes);
        //cout << (i+1) << ") n° elementi: " << nElements;
        //cout << " => init time " << tinit[i].count() / nTimes << endl;

        myfile << nElements << "\t" << tinit[i].count() << "\t" << nTimes << "\n";

        nTimes = i % 1 == 0 ? max(2, nTimes - 1) : nTimes;
        nElements = updateNumOfElem(nElements, i);
    }
    return tinit;
}

vector<duration<double>> execution(vector<int> vec, int k) {
    /*
        nElements in array:
        100, 200, 300, ... , 1.000 (+ 100 each time) (10 array dimensions)
        1.000, 2.000, 3.000, ... , 10.000 (+ 1.000 each time) (9 array dimensions)
        10k, 20k, 30k, ... , 1mln (+ 10.000 each time) (99 array dimensions)
    */
    int nElements = 100;
    int nTimes = 80; //num of times we want to measure init time
    vector<duration<double>> ttot = vector<duration<double>>(nOfArrays);

    //output to file.txt
    ofstream myfile ("tot.txt");
    if (myfile.is_open())
    {
        myfile << "n° elem\ttot time\tn° rip\n";
    }
    steady_clock::time_point start, end;
    for(int i = 0; i < nOfArrays; i++) {
        cout << i << ") quickselect on array dim: " << nElements;
        vec.clear();
        vec = randomize(nElements);
        //todo passare metodo come par?
        start = steady_clock::now();
        for(i = 0; i < nTimes; i++) {
            quickSelect(&vec[0], 0, vec.size() - 1, k);
        }
        end = steady_clock::now();
        ttot[i] = (duration<double>)((end - start) / nTimes);
        //cout << (i+1) << ") n° elementi: " << nElements;
        //cout << " => init time " << tinit[i].count() / nTimes << endl;

        myfile << nElements << "\t" << ttot[i].count() << "\t" << nTimes << "\n";

        nTimes = i % 1 == 0 ? max(2, nTimes - 5) : nTimes;
        nElements = updateNumOfElem(nElements, i);
    }

    return ttot;
}
