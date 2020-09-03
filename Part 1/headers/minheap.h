#ifndef PROGETTO_MINHEAP_H
#define PROGETTO_MINHEAP_H

#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;


template <typename T>
ostream &operator << (ostream &out, const vector<T> &vec) {
    for (long i = 0; i < vec.size(); i++) {
        out << vec[i] << " ";
    }
    out << endl;
    return out;
}

template <typename T>
istream &operator >> (istream &in, vector<T> &vec) {
    string line;
    getline(in, line);
    istringstream sin(line);

    int value;
    vec.clear();
    while (sin >> value) {
        vec.push_back(value);
    }
    return in;
}

void swap(int* vec, int start, int finish) {
    int aux = vec[start];
    vec[start] = vec[finish];
    vec[finish] = aux;
}

void swapVecPair(pair<int,int>* vec, int start, int finish ) {
    pair<int,int> aux = vec[start];
    vec[start] = vec[finish];
    vec[finish] = aux;
}


struct MinHeap {
    vector<int> vec = vector<int>(0);
    int heapsize = 0; //heapsize rappresenta l'ultima posizione nella quale è presente l'utimo elemento della minheap

    MinHeap() = default;

    MinHeap(vector<int> v, int hp) {
        vec = std::move(v);
        heapsize = hp;
    }

    int leftSon(int position) {
        return 2*position+1;
    }

    int rightSon(int position) {
        return 2*position+2;
    }

    int parent(int sonPosition) {
        return (sonPosition % 2 == 1 ? sonPosition/2 : sonPosition/2 - 1);
    }

    int getRoot() {
        return vec.front();
    }

    void minHeapify(int position) {
        int l = 2*position + 1;
        int r = 2*position + 2;
        int m;
        if ((l <= heapsize) && (vec[l] < vec[position])) {
            m = l;
        } else {
            m = position;
        }
        if ((r <= heapsize) && (vec[r] < vec[m])) {
            m = r;
        }
        if (m != position) {
            swap(&vec[0], position, m);
            minHeapify(m);
        }
    }

    void buildMinHeap() {
        for (int i = parent(heapsize); i >= 0; i=i-1) {
            minHeapify(i);
        }
    }

    int extract() {
        int exRoot = getRoot();
        swap(&vec.front(), 0, heapsize);
        vec.pop_back();
        if (!vec.empty())
            heapsize--;
        minHeapify(0);
        return exRoot;
    }

    /**
     *
     * @param k
     */
    void insert(int k) {
        if (!vec.empty())
            heapsize++;
        vec.push_back(k);
        int pos = heapsize;
        while ((pos > 0) && (vec[pos] < vec[parent(pos)])) {
            swap(&vec[0], pos, parent(pos));
            pos = parent(pos);
        }
    }

    /**
     * Ritorna la posizione della chiave k all'interno della MinHeap
     * @param k
     * @return
     */
    int findKey (int k) {
        int position = 0,i = 0;
        while (i <= heapsize) {
            if (vec[i] == k) {
                position = i;
            }
            i++;
        }
        return position;
    }


};

//////////////////////////////////////////////////////////

struct supportMeanHeap {

    vector<pair<int, int>> nodePos;
    int heapsize = 0;

    int leftSon(int position) {
        return 2*position+1;
    }

    int rightSon(int position) {
        return 2*position+2;
    }


    int parent(int sonPosition) {
        return (sonPosition % 2 == 1 ? sonPosition/2 : sonPosition/2 - 1);
    }

    void minHeapify(int position) {
        int l = 2*position + 1;
        int r = 2*position + 2;
        int m;
        if ((l <= heapsize) && (nodePos[l] < nodePos[position])) {
            m = l;
        } else {
            m = position;
        }
        if ((r <= heapsize) && (nodePos[r] < nodePos[m])) {
            m = r;
        }
        if (m != position) {
            swapVecPair(&nodePos[0], position, m);
            minHeapify(m);
        }
    }


    int extractPos() {
        int pos = nodePos[0].second;
        swapVecPair(&nodePos.front(), 0, heapsize);
        nodePos.pop_back();
        if (!nodePos.empty())
            heapsize--;
        minHeapify(0);
        return pos;
    }

    /**
     *
     * @param k
     */
    void insert(int k, int pos) {
        if (!nodePos.empty())
            heapsize++;
        pair<int, int> newNode (k, pos);
        nodePos.push_back(newNode);
        int hp = heapsize;
        while ((hp > 0) && (nodePos[hp] < nodePos[parent(hp)])) {
            swapVecPair(&nodePos[0], hp, parent(hp));
            hp = parent(hp);
        }
    }

};












ostream &operator << (ostream &out, MinHeap minHeap) {
    for (long i = 0; i <= minHeap.heapsize; i++) {
        out << minHeap.vec[i] << " ";
    }
    out << endl;
    return out;
}

bool isMinHeap(MinHeap* minHeap) {
    bool isValid = true;
    for (int i = 0; i <= (minHeap->heapsize/2)-1; i++) {
        if ((minHeap->vec[minHeap->leftSon(i)] < minHeap->vec[i]) || (minHeap->vec[minHeap->rightSon(i)] < minHeap->vec[i])) {
            isValid = false;
        }
    }
    return isValid;
}


bool isMinHeapSupport(supportMeanHeap* minHeap) {
    bool isValid = true;
    for (int i = 0; i <= (minHeap->heapsize/2)-1; i++) {
        if ((minHeap->nodePos[minHeap->leftSon(i)].first < minHeap->nodePos[i].first) || (minHeap->nodePos[minHeap->rightSon(i)].first < minHeap->nodePos[i].first)) {
            isValid = false;
        }
    }
    return isValid;
}


#endif //PROGETTO_MINHEAP_H
