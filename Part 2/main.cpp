#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include "chrono"
#include "time.h"
#include "tree.h"

using namespace chrono;

#define vdd vector<duration<double>>

vdd initialization();
void execution(vdd tinit, int type, struct tree *(*function)(struct tree *root, struct tree *node));
void printToFile(vdd texec, vector<double> std, int type);
string getAlgorithmName(int type);
void callAlgorithm(int type, vector<int> vec, int left, int right, int k);

#define startingLength 100
#define startingNumTimes 150
#define nExecSTD 20
int nOfArrays;

#define BST 0
#define RBT 1
#define AVL 2

duration<double> res;
#define RELATIVE_ERROR 0.01

int main() {
    struct tree *test = NULL;
    struct tree *node = create(10);
    test = BSTinsert(test, node);
    cout << test->key;
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
    execution(tinit, BST, &BSTinsert);
    execution(tinit, RBT, &RBTinsert);
    execution(tinit, AVL, &AVLinsert);
    
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
        nElements = updateNumOfElem(i, nElements);
    }
    myfile.close();
    return tinit;
}

void execution(vdd tinit, int type, struct tree *((*function)(struct tree *, struct tree *))) {
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
        //vector to contain the 20 time to calculate std
        vdd ttoti(nExecSTD);
        for(int h = 0; h < nExecSTD; h++) {
            start = steady_clock::now();
            vector<int> vec;
            for(int j = 0; j < nTimes; j++) {
                vec.clear();
                vec = randomize(nElements);
                struct tree *tree = NULL;
                for(int k = 1; i < nElements; i++) {
                    cout << vec[i] << "\n";
                    if(BSTfind(vec[i], tree) == NULL) {
                        struct tree *node = create(vec[i]);
                        tree = std::__invoke(function, tree, node);
                    }
                    preOrder(tree);
                }
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
            nElements = updateNumOfElem(i, nElements);
        }
    }
    printToFile(texec, std, type);
}

void printToFile(vdd texec, vector<double> std, int type) {

    ofstream myfile ("tempi/" + getAlgorithmName(type) + " exec.txt");
    if (myfile.is_open()) {
        myfile << "n° elem\texec time\tstd\tn° rip\n";
        int nElements = startingLength;
        int nTimes = startingNumTimes;
        for(int i = 0; i < texec.size(); i++) {
            myfile << nElements << "\t" << texec[i].count() << "\t" << std[i] << "\t" << nTimes << "\n";
            nElements = updateNumOfElem(i, nElements);
            nTimes = updateNumOfTimes(nTimes);
        }
    }
    myfile.close();
}

string getAlgorithmName(int type) {
    if(type == BST) {
        return "BST";
    } else if(type == AVL) {
        return "AVL";
    } else if(type == RBT) {
        return "RBT";
    }
    return NULL;
}