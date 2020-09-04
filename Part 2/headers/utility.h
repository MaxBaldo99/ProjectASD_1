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

#endif //PROGETTO_UTILITY_H
