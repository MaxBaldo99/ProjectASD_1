#include <iostream>
#include "select.h"
#include "minheap.h"

int main() {
    vector<int> vec;
    int k;
    cin >> vec;
    cin >> k;
    MinHeap h1 = MinHeap(vec, vec.size()-1);
    supportMeanHeap h2;
    h1.buildMinHeap();
    cout << heapSelect(&h1, &h2, k) << endl;
    return 0;
}