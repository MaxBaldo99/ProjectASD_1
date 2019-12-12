#include <iostream>
#include <vector>
#include <sstream>
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
    int l = 2*position;
    int r = 2*position + 1;
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

void minHeapify(int* vec, int length, int position) {
    int l, r;
    if (position == 0) {
        l = 2*position + 1;
        r = 2*position + 2;
    } else {
        l = 2*position;
        r = 2*position + 1;
    }
    int m;
    if ((l < length) && (vec[l] < vec[position])) {
        m = l;
    } else {
        m = position;
    }
    if ((r < length) && (vec[r] < vec[m])) {
        m = r;
    }
    if (m != position) {
        swap(vec, position, m);
        minHeapify(vec, length, m);
    }
}

class MinHeap {

public:
    vector<int> vec;

public:

    void buildMinHeap() {
        for (int i = (vec.size() - 1) / 2; i >= 0; i--) {
            minHeapify(&vec[0], vec.size(), i);
        }
    }

    int getMin() {
        return vec[0];
    }

    void length() {
        cout << vec.size() << endl;
    }

    int extract() {
        swap(&vec[0], 0, vec.size()-1);
        int last = vec[vec.size()-1];
        vec.pop_back();
        minHeapify(&vec[0], vec.size(), 0);
        return last;
    }

    void insert(int k) {
        vec.push_back(k);
        int pos = vec.size()-1;
        while (pos > 0) {
            if (pos == 1) {
                int parent = pos/2;
                if (vec[pos] < vec[parent]) {
                    swap(&vec[0], pos, parent);
                }
                pos = pos/2;
            } else {
                int parent = pos/2 - 1;
                if (vec[pos] < vec[parent]) {
                    swap(&vec[0], pos, parent);
                }
                pos = pos/2 - 1;
            }
        }
    }

    void change(int pos, int k) {
        vec[pos] = k;
        while (pos > 0) {
            if (pos == 1) {
                int parent = pos/2;
                if (vec[pos] < vec[parent]) {
                    swap(&vec[0], pos, parent);
                }
                pos = pos/2;
            } else {
                int parent = pos/2 - 1;
                if (vec[pos] < vec[parent]) {
                    swap(&vec[0], pos, parent);
                }
                pos = pos/2 - 1;
            }
        }
    }



};



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
