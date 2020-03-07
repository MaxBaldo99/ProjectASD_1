#include <assert.h>
#include "utility.h"

//PORCO DIO CE L'HO FATTA BALDO
//CE L'HO FATTA
//SI CAZZO DIO CAN
//HO IMPARATO A FARE COMMIT PUSH E PULL

//COSTANTS:
int BLOCK_SIZE = 5;

//SCOPES
void quickSort(int* vec, int p, int q);
int quickSelect(int* vec, int p, int q, int k);
int heapSelect(MinHeap h1, MinHeap h2, int k);
int select(int* array, int left, int right, int target);
void insertionSort(int* array, int p, int q);

//MAIN
int main() {
    MinHeap h1;
    MinHeap h2;
    cin >> h1.vec;
    int k;
    cin >> k;
    //cout << heapSelect(h1, h2, k) << endl;
    //come cazzo funziona c++?
    //cout << select(h1.vec, 0, k-1, k) << endl;
    return 0;
}

//METHODS
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
    // we assume that k is in the interval of p and q
    assert (k > 0 && k <= q - p + 1);       
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

//D => O(n) sia pessimo sia medio
int select(int* array, int left, int right, int target) {    
    if (left == right - 1) {
        return array[left];
    }    
    int blocks = 0;
    int j = left;
    int bLen = (right / BLOCK_SIZE);
    bLen = right % BLOCK_SIZE == 0 ? bLen : bLen + 1;
    int B[bLen];
    while (j < right) {
        
        int limit = j + BLOCK_SIZE - 1;
        limit = limit < right ? limit : right - 1;
        insertionSort(array, j, limit);
        B[blocks++] = array[(j + limit) / 2];
        j += BLOCK_SIZE;
    }
    int median = select(B, 0, blocks, blocks/2);
    swap(array, median, right-1);
    int medianPos = partition(array, left, right-1);
    int k = medianPos - left;
    if (target == k) {
        return array[medianPos];
    } else if (target < k) {
        return select
    (array, left, medianPos, target);
    } else {
        return select
    (array, medianPos+1, right, target-k-1);
    }
}

void insertionSort(int* array, int p, int q) {
    for (int j = p+1; j < q+1; j++) {
        int key = array[j];
        int i = j - 1;
        while (i >= p && array[i] > key) {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

