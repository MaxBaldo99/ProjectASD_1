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
    cout << "creo albero\n";
    //vector<int> chiavi{};
    //vector<struct tree*> nodi{};

    int n = 10 * pow(10, 6); //5000k
    int print = 1 * pow(10, 6); //500k

    struct tree *albero = nullptr;
    
    for (int i = 0; i < n; i++) {
        int rnd = rand();
        if(BSTfind(albero, rnd) == nullptr) {
            //struct tree* nodo = create(rnd);
            //chiavi.push_back(rnd);
            //nodi.push_back(nodo);
            BSTinserta(albero, rnd);
            if (i % print == 0) cout << i << "\n";
        } else {
            i--;
        }
    }
    
    cout << "Finito di caricare i dati\n";
    cout << "premere per svuotare la memoria\n";
    char c = 0; 
    cin >> c;
    cout << "distruggo albero\n";
    
    for (int i = 0; i < n; i++) {
        /*
        struct tree *nodo  = BSTfind(albero, chiavi[i]);
        if (nodo == NULL) cout << "\nERROR\n";
        else albero = BSTdelete(albero, nodo, true);
        */
        
        //delete nodi[i];
        //if (i % print == 0) cout << i << "\n";
        
    }
    
    int contaChiamateDelete = 0;
    albero = destroyTreeRasera(albero, contaChiamateDelete);
    cout << "eseguito " << contaChiamateDelete << " chiamate a destroy" << endl;
    
    //delete albero;
    
    cout << "Ho distrutto tutto\n";

    //nodi.clear();
   
    
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
    //cout << "Finito di controllare2\n";
    cout << "ora eseguo while(true)\n";
    while(true);
}