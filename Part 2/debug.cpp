#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include "chrono"
#include "headers/time.h"
#include "headers/tree.h"
#include "headers/tree.cpp"


int main() {   
    srand(time(NULL));
    cout << "Hello\n";
    vector<int> chiavi{};
    vector<struct tree*> nodi{};

    int n = 5 * pow(10, 6); //5000k
    int print = 5 * pow(10, 6); //500k

    struct tree* albero = nullptr;

    for (int i = 0; i < n; i++) {
        int rnd = rand();
        if(BSTfind(albero, rnd) == nullptr) {
            struct tree* nodo = create(rnd);
            chiavi.push_back(rnd);
            nodi.push_back(nodo);
            albero = BSTinsert(albero, nodi[i]);
            if (i % print == 0) cout << i << "\n";
        } else {
            i--;
        }
    }
    
    cout << "\n Finito di caricare i dati\n"; 
    int a = 0; 
    cin >> a;
    /*
    for (int i = 0; i < n; i++) {
        /*
        struct tree *nodo  = BSTfind(v[i], albero);
        if (nodo == NULL) cout << "\nERROR\n";
        else albero = BSTdelete(albero, nodo, true);
        //if (i % 200000 == 0) cout << i << " ";
        
        //delete t[i];
    }
    */
    int contaChiamateDelete = 0;
    albero = destroyTree(albero, contaChiamateDelete);

    nodi.clear();
    cout << "\nHo distrutto tutto: "<< contaChiamateDelete << endl;
    /*
    for (auto i : t) {
        if (i->key >= 20000) cout << "Error" << endl;
        //cout << i->key << " ";
    }
    cout << "\nFinito di controllare1\n";
    for (auto i : t) {
        delete i;
        //cout << i->key << " ";
    }
    cout << "\nFinito di eliminare vettore\n";
    for (auto i : t) {
        if (i->key >= 20000) cout << "Error" << endl;
        //cout << i->key << " ";
    }
    */
    cout << "\nFinito di controllare2\n";
}