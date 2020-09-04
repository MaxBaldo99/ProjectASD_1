#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include "headers/time.h"
#include "chrono"
#include "headers/select.h"

using namespace chrono;

#define vdd vector<duration<double>>

vdd initialization();
void execution(vdd tinit, int type, int (*function)(vector<int> vec, int left, int right, int k));
void printToFile(vdd texec, vector<double> std, int type);
string getAlgorithmName(int type);
void callAlgorithm(int type, vector<int> vec, int left, int right, int k);

#define startingLength 100
#define startingNumTimes 150
#define nExecSTD 20
int nOfArrays;

#define HEAP 0
#define QUICK 1
#define MOM 2

duration<double> res;
#define RELATIVE_ERROR 0.01

int main() {
    nOfArrays = calcNumOfArrays(startingLength);
    //cin >> vec;
    res = resolution();
    cout << "resolution: " << res.count() << "\n";
    ofstream myfile ("tempi/resolution.txt");
    if (myfile.is_open()) {
        myfile << "resolution:\n" << res.count();
    }
    myfile.close();
    cout << "inizializzo\n";
    vdd tinit = initialization();
    cout << "eseguo\n";
    execution(tinit, QUICK, &quickSelect);
    execution(tinit, MOM, &MOMSelect);
    execution(tinit, HEAP, &callHeapSelect);
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
    ofstream myfile ("tempi/init.txt");
    if (myfile.is_open())
    {
        myfile << "n° elem\tinit time\tn° rip\n";
    }
    cout << "n° elem\tinit time\tn° rip\n";
    for(int i = 0; i < nOfArrays; i++) {
        tinit[i] = initializeTime(nElements, nTimes);

        cout << nElements << "\t" << tinit[i].count() << "\t" << nTimes << "\n";
        myfile << nElements << "\t" << tinit[i].count() << "\t" << nTimes << "\n";

        nTimes = updateNumOfTimes(nTimes);
        nElements = updateNumOfElem(nElements);
    }
    myfile.close();
    return tinit;
}

void execution(vdd tinit, int type, int (*function)(vector<int>, int, int, int)) {
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
    cout << getAlgorithmName(type) << endl;
    cout << "i  n° elem\ttot time\tn° rip\tstandard dev\tstd/mean\n";
    steady_clock::time_point start, end;
    srand(time(NULL));
    for(int i = 0; i < nOfArrays; i++) {
        //vector to contain the 20 time to calulate std
        vdd ttoti(nExecSTD);
        for(int h = 0; h < nExecSTD; h++) {
            int k = type == HEAP ? nElements / 4 : rand() % nElements + 1;
            start = steady_clock::now();
            vector<int> vec;
            for(int j = 0; j < nTimes; j++) {
                vec.clear();
                vec = randomize(nElements);
                //choose select algorithm
                //quickSelect(vec, 0, vec.size(), k);
                //MOMSelect(vec, 0, vec.size(), k);
                //callHeapSelect(vec, 0, vec.size(), k);
                //callAlgorithm(type, vec, 0, nElements, k);
                std::__invoke(function, vec, 0, nElements, k);
            }
            end = steady_clock::now();
            ttoti[h] = (duration<double>)((end - start) / nTimes);
        }
        for(int j = 0; j < nExecSTD; j++) {
            //ttoti becomes texeci: substracted init time
            ttoti[j] -= tinit[i]; 
        }
        texec[i] = (duration<double>) mean(ttoti);
        std[i] = meanSquaredError(ttoti);
        double measuredError = texec[i].count() * nTimes;
        double relativeError = res.count() / RELATIVE_ERROR + res.count();
        if(measuredError < relativeError) {
            //DO IT AGAIN ERROR IS NOT RESPECTED
            i--;
            cout << "time is lower than relative error -----------------------------------\n";
        } else {
            //TIME IS OK SAVE RESULTS
            double stdPerc = std[i] / mean(ttoti);
            if(i < 10) {
                cout << 0;
            }
            cout << i << ") ";
            if(nElements < 1000) {
                cout << 0;
            }
            cout << nElements << "\t" << texec[i].count() << "\t" << nTimes << "\t" << std[i] << "\t" << stdPerc << "\n";

            nTimes = updateNumOfTimes(nTimes);
            nElements = updateNumOfElem(nElements);
        }
    }
    printToFile(texec, std, type);
}

void callAlgorithm(int type, vector<int> vec, int left, int right, int k) {
    if(type == HEAP) {
        callHeapSelect(vec, left, right, k);
    } else if(type == QUICK) {
        quickSelect(vec, left, right, k);
    } else if(type == MOM) {
        MOMSelect(vec, left, right, k);
    }
}

void printToFile(vdd texec, vector<double> std, int type) {

    ofstream myfile ("tempi/" + getAlgorithmName(type) + " exec.txt");
    if (myfile.is_open()) {
        myfile << "n° elem\texec time\tstd\tn° rip\n";
        int nElements = startingLength;
        int nTimes = startingNumTimes;
        for(int i = 0; i < texec.size(); i++) {
            myfile << nElements << "\t" << texec[i].count() << "\t" << std[i] << "\t" << nTimes << "\n";
            nElements = updateNumOfElem(nElements);
            nTimes = updateNumOfTimes(nTimes);
        }
    }
    myfile.close();
}

string getAlgorithmName(int type) {
    if(type == HEAP) {
        return "heap";
    } else if(type == QUICK) {
        return "quick";
    } else if(type == MOM) {
        return "mom";
    }
    return NULL;
}