#include <assert.h>
#include "utility.h"

int heapSelect(MinHeap h1, MinHeap h2, int k) {
    int root = h1.getRoot();
    h2.insert(root);       //inserisco la radice della prima MinHeap nella seconda MinHeap
    for (int i = 0; i < k-1; ++i) {
        int newKey = h2.extract();
        int newKeyPosition = h1.findKey(newKey);
        h2.insert(h1.vec[h1.leftSon(newKeyPosition)]);
        h2.insert(h1.vec[h1.rightSon(newKeyPosition)]);
        //int removeKey = h1.extract();
    }
    int last = h2.getRoot();
    return last;
}

//9 5 2 6 3

int main() {
    vector<int> keys;
    int key;
    cin >> keys;
    cin >> key;
    MinHeap h1 = MinHeap(keys, keys.size()-1);
    MinHeap h2;
    h1.buildMinHeap();
    cout << heapSelect(h1, h2, key) << endl;
    return 0;
}