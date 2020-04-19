#include <assert.h>
#include "utility.h"
#include "time.h"
#include "chrono"
#include <fstream>
using namespace chrono;

#define vdd vector<duration<double>>

void quickSort(int* vec, int p, int q);
int quickSelect(int* vec, int p, int q, int k);
int heapSelect(MinHeap h1, MinHeap h2, int k);
vdd initialization();
void execution(vdd tinit);
double tExecution(vdd *ttoti, vdd *tinit, vdd *texec, int i);
void printToFile(vdd texec, int nElements, int nTimes, vector<double> std);

int nOfArrays;
int startingLength = 100;
int startingNumTimes = 200;
int nExecSTD = 20;

/*
    IMPARA:
    '\n' >>>>>>>>>>>>>>> endl
*/

int main() {
    nOfArrays = calcNumOfArrays(startingLength);
    //cin >> vec;
    duration<double> res = resolution();
    cout << "resolution: " << res.count() << "\n";
    cout << "inizializzo\n";
    vdd tinit = initialization();
    cout << "eseguo\n";
    execution(tinit);
    
    //cout << quickSelect(&vec[0], 0, vec.size()-1, k) << endl;
    return 0;
    
}

vdd initialization() {
    /*
        nElements in array:
        100, 200, 300, ... , 1.000 (+ 100 each time) (10 array dimensions)
        1.000, 2.000, 3.000, ... , 10.000 (+ 1.000 each time) (9 array dimensions)
        10k, 20k, 30k, ... , 1mln (+ 10.000 each time) (99 array dimensions)
    */
    int nElements = startingLength;
    int nTimes = startingNumTimes; //num of times we want to measure init time
    vdd tinit = vdd(nOfArrays);

    //output to file
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

        nTimes = updateNumOfTimes(nTimes, i);
        nElements = updateNumOfElem(nElements);
    }
    myfile.close();
    return tinit;
}

void execution(vdd tinit) {
    /*
        nElements in array:
        100, 200, 300, ... , 1.000 (+ 100 each time) (10 array dimensions)
        1.000, 2.000, 3.000, ... , 10.000 (+ 1.000 each time) (9 array dimensions)
        10k, 20k, 30k, ... , 1mln (+ 10.000 each time) (99 array dimensions)
    */
    int nElements = startingLength;
    int nTimes = startingNumTimes; //num of times we want to measure init time
    vdd texec(nOfArrays);
    vector<double> std(nOfArrays);
    
    cout << "i  n° elem\ttot time\tn° rip\tvariation\n";
    steady_clock::time_point start, end;
    srand(time(NULL));
    for(int i = 0; i < nOfArrays; i++) {
        //vector to contain the 20 time to calulate std
        vdd ttoti(nExecSTD);
        for(int h = 0; h < nExecSTD; h++) {
            int k = rand();
            while(k >= nElements) {
                k = k/2;
            }
            start = steady_clock::now();
            vector<int> vec;
            for(int j = 0; j < nTimes; j++) {
                vec.clear();
                vec = randomize(nElements);
                //scegliere metodo
                quickSelect(&vec[0], 0, vec.size() - 1, k);
            }
            end = steady_clock::now();
            ttoti[h] = (duration<double>)((end - start) / nTimes);
        }
        for(int j = 0; j < nExecSTD; j++) {
            ttoti[j] -= tinit[i];
        }
        texec[i] = ttoti[minimum(ttoti)];
        std[i] = meanSquaredError(ttoti);
        
        //std[i] = tExecution(&ttoti, &tinit, &texec, i);
        double stdPerc = std[i] / mean(ttoti);
        cout << i << ") " << nElements << "\t" << texec[i].count() << "\t" << nTimes << "\t" << std[i] << "\t" << stdPerc << "\n";

        nTimes = updateNumOfTimes(nTimes, i);
        nElements = updateNumOfElem(nElements);
    }

    printToFile(texec, nElements, nTimes, std);
}

double tExecution(vdd *ttoti, vdd *tinit, vdd *texec, int i) {
    
    for(int j = 0; j < (*ttoti).size(); j++) {
        (*ttoti)[j] = (*ttoti)[j] - (*tinit)[i];
    }
    (*texec)[i] = (*ttoti)[minimum(*ttoti)];
    return meanSquaredError(*ttoti);
}

void printToFile(vdd texec, int nElements, int nTimes, vector<double> std) {

    ofstream myfile ("exec.txt");
    if (myfile.is_open()) {
        myfile << "exec time\n";
    }
    for(int i = 0; i < texec.size(); i++) {
        myfile << nElements << "\t" << texec[i].count() << "\t" << nTimes << "\t" << std[i] << "\n";
    }
    myfile.close();
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
    /*
    int index = partition(vec, p, q);
    if (index - p == k - 1) {
        return vec[index];
    }
    if (index - p > k - 1) {
        return quickSelect(vec, p, index - 1, k);
    }
    return quickSelect(vec, index + 1, q, k - index + p - 1);
    */
   while (p <= q) { 
        int index = partition(vec, p, q); 
        if (index == k - 1) {
            return vec[index]; 
        } else if (index > k - 1) {
            q = index - 1;
        } else {
            p = index + 1; 
        }
    } 
    return -1;
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

