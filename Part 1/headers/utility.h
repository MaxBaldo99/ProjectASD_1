#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

#ifndef PROGETTO_UTILITY_H
#define PROGETTO_UTILITY_H

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

/*--------------------------------------------------------- MAXHEAP -----------------------------------------------------------------------------*/

void heapify(int* vec, int length, int position) {
    int l = (position != 0 ? 2*position : 2*position+1);
    int r = (position != 0 ? 2*position + 1 : 2*position+2);
    int m;
    if ((l <= length) && (vec[l] > vec[position])) {
        m = l;
    } else {
        m = position;
    }
    if ((r <= length) && (vec[r] > vec[m])) {
        m = r;
    }
    if (m != position) {
        swap(vec, position, m);
        heapify(vec, length, m);
    }
}

void buildMaxHeap(int* vec, int length) {
    for (int i = length/2; i >= 0; i--) {
        heapify(vec, length, i);
    }
}

/*--------------------------------------------------------- MINHEAP -----------------------------------------------------------------------------*/

struct MinHeap {
    vector<int> vec = vector<int>(0);
    int heapsize = 0; //heapsize rappresenta l'ultima posizione nella quale è presente l'utimo elemento della minheap

    MinHeap() = default;

    MinHeap(vector<int> v, int hp) {
        vec = std::move(v);
        heapsize = hp;
    }

    static int leftSon(int position) {
        return 2*position+1;
    }

    static int rightSon(int position) {
        return 2*position+2;
    }

    static int parent(int sonPosition) {
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
            swap(&vec.front(), position, m);
            minHeapify(m);
        }
    }

    void buildMinHeap() {
        for (int i = (heapsize/2)-1; i >= 0; i=i-1) {
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
        while ((pos > 1) && (vec[pos] < vec[parent(pos)])) {
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

ostream &operator << (ostream &out, MinHeap minHeap) {
    for (long i = 0; i <= minHeap.heapsize; i++) {
        out << minHeap.vec[i] << " ";
    }
    out << endl;
    return out;
}





/*--------------------------------------------------------- QUICKSORT -----------------------------------------------------------------------------*/

int partition(int* vec, int p, int q) {
    int x = vec[q];
    int i = p - 1;
    for (int j = p; j <= q; ++j) {
        if (vec[j] <= x) {
            i++;
            swap(vec, i, j);
        }
    }
    return i;
}









#endif //PROGETTO_UTILITY_H
