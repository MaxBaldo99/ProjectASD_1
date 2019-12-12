#include <assert.h>
#include "utility.h"

void quickSort(int* vec, int p, int q) {
    if (p < q) {
        int r = partition(vec, p, q);
        quickSort(vec, p , r - 1);
        quickSort(vec, r + 1, q);
    }
}

/**
 * The procedure return the k-esim element (in k position) in the array vec.
 * WE ASSUME THAT K IS A VALID INDEX OF THE ARRAY
 * @param vec is the vec to select the element
 * @param p is the index where to start searching in the array vec
 * @param q is th index where to finish searching the array vec
 * @param k is the position which is the element to return. REQUIRED is major or equal 0 and minus or equals vec.length -1
 * @return the element in the k position
 */
int quickSelect(int* vec, int p, int q, int k) {

    assert (k > 0 && k <= q - p + 1);       // we assume that k is in the interval of p and q

    int index = partition(vec, p, q);

    if (index - p == k - 1) {
        return vec[index];
    }

    if (index - p > k - 1) {
        return quickSelect(vec, p, index - 1, k);
    }

    return quickSelect(vec, index + 1, q, k - index + p - 1);
}

int heapSelect(MinHeap h1, MinHeap h2, int k) {
    h1.buildMinHeap();
    cout << h1.vec << endl;
    h2.insert(0);       //inserisco la posizione nella seconda miHeap
    for (int i = 0; i < k-1; ++i) {
        int nodePosition = h2.extract();
        if (nodePosition == 0) {
            h2.insert(2 * nodePosition + 1);
            h2.insert(2 * nodePosition + 2);
        } else {
            h2.insert(2 * nodePosition);
            h2.insert(2 * nodePosition + 1);
        }
    }
    int last = h2.extract();
    return h1.vec[last];
}



int main() {
    MinHeap h1;
    MinHeap h2;
    cin >> h1.vec;
    int k;
    cin >> k;
    cout << heapSelect(h1, h2, k) << endl;
    return 0;
}
