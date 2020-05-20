#include <assert.h>
#include "minheap.h"
//#include "support_minheap.h"

//9 5 2 6 3

int heapSelect(MinHeap* h1, supportMeanHeap* h2, int k);

int main() {
    vector<int> keys;
    int key;
    cin >> keys;
    cin >> key;
    MinHeap h1 = MinHeap(keys, keys.size()-1);
    supportMeanHeap h2;
    h1.buildMinHeap();
    cout << heapSelect(&h1, &h2, key);
    return 0;
}

int heapSelect(MinHeap* h1, supportMeanHeap* h2, int k) {
    int root = h1->getRoot();
    h2->insert(root,0);       //inserisco la radice della prima MinHeap nella seconda MinHeap
    for (int i = 0; i < k-1; ++i) {
        int newKeyPosition = h2->extractPos();
        //if (newKeyPosition <= (h1->heapsize/2)-1) {
        if(h1->leftSon(newKeyPosition) <= h1->heapsize) {
            h2->insert(h1->vec[h1->leftSon(newKeyPosition)], h1->leftSon(newKeyPosition));
            if(h1->rightSon(newKeyPosition) <= h1->heapsize) {
                h2->insert(h1->vec[h1->rightSon(newKeyPosition)], h1->rightSon(newKeyPosition));
            }
        }
        //assert(isMinHeap(h1));
        //assert(isMinHeapSupport(h2));
    }
    int last = h2->nodePos[0].first;
    return last;
}
