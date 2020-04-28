#include <assert.h>
#include <fstream>
#include "utility.h"
#include "time.h"
#include "chrono"
#include "select.h"

using namespace chrono;

#define vdd vector<duration<double>>

vdd initialization();
void execution(vdd tinit);
double tExecution(vdd *ttoti, vdd *tinit, vdd *texec, int i);
void printToFile(vdd texec, vector<double> std);

#define startingLength 100
#define startingNumTimes 200
#define nExecSTD 20
int nOfArrays;

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
    cout << "n° elem\tinit time\tn° rip\n";
    for(int i = 0; i < nOfArrays; i++) {
        tinit[i] = initializeTime(nElements, nTimes);

        cout << nElements << "\t" << tinit[i].count() << "\t" << nTimes << "\n";
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
    
    cout << "i  n° elem\ttot time\tn° rip\tstandard dev\tstd/mean\n";
    steady_clock::time_point start, end;
    srand(time(NULL));
    for(int i = 0; i < nOfArrays; i++) {
        //vector to contain the 20 time to calulate std
        vdd ttoti(nExecSTD);
        for(int h = 0; h < nExecSTD; h++) {
            int k = rand() % nElements + 1;
            start = steady_clock::now();
            vector<int> vec;
            for(int j = 0; j < nTimes; j++) {
                vec.clear();
                vec = randomize(nElements);
                //choose select algorithm
                //quickSelect(&vec[0], 0, vec.size() - 1, k);
                int val = MOMSelect(&vec[0], 0, vec.size(), k);
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
        
        double stdPerc = std[i] / mean(ttoti);
        if(i < 10) {
            cout << 0;
        }
        cout << i << ") ";
        if(nElements < 1000) {
            cout << 0;
        }
        cout << nElements << "\t" << texec[i].count() << "\t" << nTimes << "\t" << std[i] << "\t" << stdPerc << "\n";

        nTimes = updateNumOfTimes(nTimes, i);
        nElements = updateNumOfElem(nElements);
    }

    //printToFile(texec, std);
}

void printToFile(vdd texec, vector<double> std) {

    ofstream myfile ("exec.txt");
    if (myfile.is_open()) {
        myfile << "n° elem\texec time\tstd\tn° rip\n";
    }
    int nElements = startingLength;
    int nTimes = startingNumTimes;
    for(int i = 0; i < texec.size(); i++) {
        myfile << nElements << "\t" << texec[i].count() << "\t" << std[i] << "\t" << nTimes << "\n";
        nElements = updateNumOfElem(nElements);
        nTimes = updateNumOfTimes(nTimes, i);
    }
    myfile.close();
}
