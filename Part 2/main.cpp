#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include "chrono"
#include "headers/time.h"
#include "headers/tree.h"
#include "headers/tree.cpp"

using namespace chrono;

#define vdd vector<duration<double>>

void execution(vdd tinit, int type, struct tree *(*function)(struct tree *& root, struct tree *node));
void printToFile(vdd texec, vector<double> std, int type);
string getAlgorithmName(int type);

#define minLength 100
#define startingNumTimes 150
#define nExecSTD 20
int nOfArrays;

#define BST 0
#define RBT 1
#define AVL 2

duration<double> res;
#define RELATIVE_ERROR 0.01

string PATH = "Part 2/times/";

int main() {    
    nOfArrays = calcNumOfArrays(minLength);
    //cin >> vec;
    res = resolution();
    cout << "resolution: " << res.count() << "\n";
    ofstream myfile(PATH + "resolution.txt");
    if (myfile.is_open()) {
        myfile << "resolution:\n" << res.count();
    }
    myfile.close();
    cout << "eseguo\n";
    vdd tinit(nOfArrays);
    execution(tinit, BST, &BSTinsert);
    execution(tinit, RBT, &RBTinsert);
    execution(tinit, AVL, &AVLinsert);
    
    return 0;
}

void execution(vdd tinit, int type, struct tree *((*function)(struct tree *&, struct tree *))) {
    int nElements = minLength;
    int nTimes = startingNumTimes; //num of times we want to measure init time
    vdd texec(nOfArrays);
    vector<double> std(nOfArrays);
    vector<double> meanOfNumOfMake(nOfArrays);
    cout << getAlgorithmName(type) << endl;
    cout << "i    n° elem\texec time\tn° rip\tstandard dev\tstd/mean\tmean(n-m)\tm/n\n";
    steady_clock::time_point start, end;
    for(int i = 0; i < nOfArrays; i++) {
        vdd ttoti(nExecSTD); //vector contains 20 times estimated to calculate std
        for(int h = 0; h < nExecSTD; h++) {
            vector<double> nOfMake(nTimes);
            start = steady_clock::now();
            srand(time(NULL));
            for(int j = 0; j < nTimes; j++) {
                //algoritmo ricerca e inserimento
                struct tree *tree = NULL;
                for(int k = 0; k < nElements; k++) {
                    int random = rand();
                    if (tree == nullptr) tree = create(random);
                    else if (BSTfind(random, tree) == nullptr) { 
                        struct tree *node = create(random);
                        BSTinsert(tree, node);
                        nOfMake[j]++;
                    }
                }
                //bool ok = isBST(tree);
                destroyTree(tree);
                //tree = NULL;
            }
            end = steady_clock::now();
            ttoti[h] = (duration<double>)((end - start) / nTimes);
            meanOfNumOfMake[i] = mean(nOfMake);
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
            double perc_m = meanOfNumOfMake[i] / nElements;
            double ti = texec[i].count();
            double m_minus_n = nElements - meanOfNumOfMake[i];
            printf("%2d) %4d\t%e\t%3d\t%e\t%.6f\t%f\t%f\n", 
                    i, nElements, ti, nTimes, std[i], stdPerc, m_minus_n, perc_m);
            nTimes = updateNumOfTimes(nTimes);
            nElements = updateNumOfElem(i, nElements);
            /*
            if(i < 10) { cout << 0; }
            cout << i << ") ";
            if(nElements < 1000) { cout << 0; }
            cout << nElements << "\t" << texec[i].count() << "\t" << nTimes << "\t" << std[i] << "\t" << stdPerc << "\t" << nElements - meanOfNumOfMake[i] << "\t" << percNumOfMake << "\n";
            */
        }
    }
    printToFile(texec, std, type);
}

void printToFile(vdd texec, vector<double> std, int type) {

    ofstream myfile (PATH + getAlgorithmName(type) + " exec.txt");
    if (myfile.is_open()) {
        myfile << "n° elem\texec time\tstd\tn° rip\n";
        int nElements = minLength;
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