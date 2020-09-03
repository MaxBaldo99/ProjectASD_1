#include "headers/minheap.h"
#include <assert.h>

#define BLOCK_SIZE 5

int quickSelect(vector<int> vec, int left, int right, int k);
int callHeapSelect(vector<int> vec, int left, int right, int k);
int MOMSelect(vector<int> vec, int left, int right, int k);
int heapSelect(MinHeap* h1, supportMeanHeap* h2, int k);
int getMedianOfMedians(int *array, int left, int right);
int partitionPivot(int *vec, int p, int q, int pivot);
void quickSort(int* vec, int p, int q);
int partition(int* vec, int p, int q);
void insertionSort(int *vec, int p, int q);
bool checkSelect(int *vec, int size, int k, int val);

/**
 * The procedure return the k-esim element (in k position) in the array vec.
 * WE ASSUME THAT K IS A VALID INDEX OF THE ARRAY
 * @param vec is the vec to select the element
 * @param p is the index where to start searching in the array vec
 * @param q is th index where to finish searching the array vec
 * @param k is the position which is the element to return. REQUIRED is major or equal 0 and minus or equals vec.length -1
 * @return the element in the k position
 */
int quickSelect(vector<int> vec, int left, int right, int k) {
    // we assume that k is in the interval of p and q
    //assert (k > 0 && k <= right - left);      
    /*
    int index = partition(vec, p, q);
    if (index - p == k - 1) {
        return vec[index];
    }
    if (index - p > k - 1) {
        return quickSelect(vec, p, index - 1, k);
    }
    return quickSelect(vec, index + 1, q, k - index + p - 1);
    */
   while (left < right) { 
        int index = partition(&vec[0], left, right - 1); 
        if (index == k - 1) {
            return vec[index]; 
        } else if (index > k - 1) {
            right = index;
        } else {
            left = index + 1; 
        }
    } 
    return -1;
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

//left is a totally useless parameter
//it's there just to have all same par types foreach select method
//so we can use the functional invoke 
int callHeapSelect(vector<int> vec, int left, int right, int k) {
    MinHeap h1 = MinHeap(vec, right - 1);
    supportMeanHeap h2;
    h1.buildMinHeap();
    return heapSelect(&h1, &h2, k);
}

//Median of Medians Select: 
//T(n) = u(n) in best, median, worst case
int MOMSelect(vector<int> vec, int left, int right, int k) {
    int medianPos;
    bool search = true;
    while(search) {
        int median = getMedianOfMedians(&vec[0], left, right);
        //printArray(array, right, " ", "<<", ">>");
        //printf("partition on %d\n", median);
        medianPos = partitionPivot(&vec[0], left, right - 1, median);
        //printf("median: %d, median pos: %d\n", median, medianPos);
        //printArray(array, right, " ", "<<", ">>");
        int target = medianPos - left + 1;
        if (k < target) {
            right = medianPos;
        } else if (k > target) {
            left = medianPos + 1;
            k -= target;
        } else {
            search = false;
        }
    }
    return vec[medianPos];
}

//support for MOM select
int getMedianOfMedians(int *array, int left, int right) {
    if(left >= right - 1) {
        return array[left];
    } else {
        int interval = right - left;
        int bLen = (interval / BLOCK_SIZE) + min(1, interval % BLOCK_SIZE);
        int blocks = 0;
        int B[bLen];
        for(int i = left; i < right; i += BLOCK_SIZE) {
            int limit = min(i + BLOCK_SIZE - 1, right - 1);
            insertionSort(array, i, limit);
            B[blocks++] = array[(i + limit) / 2];
        }
        return getMedianOfMedians(B, 0, bLen);
    }
}

/**
 *  algorithm places:
 *   - elements <= pivot to his left [p, i]
 *   - elements > pivots to his right [i+1, q-1]
 * @param array the array to edit
 * @param p the min index in the array REQUIRE 0 <= i < q <= array.length (p is included)
 * @param q the max index in the array REQUIRE 0 <= i < q < array.length (q is included)
 * @param pivot the value (not need to be in the array)
 * @return the index of the last element <= pivot
 */
int partitionPivot(int *vec, int p, int q, int pivot) {
    int i = p;
    int j = q;
    int valIndex = -1;
    while(i <= j) {
        if(vec[i] <= pivot) {
            valIndex = vec[i] == pivot ? i : valIndex;
            i++;
        } else {
            swap(vec, j, i);
            j--;
        }
    }
    if(valIndex >= 0) {
        swap(vec, j, valIndex);
    }
    return j;
}

void quickSort(int* vec, int p, int q) {
    if (p < q) {
        int r = partition(vec, p, q);
        quickSort(vec, p , r - 1);
        quickSort(vec, r + 1, q);
    }
}

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

void insertionSort(int *vec, int p, int q) {
    for (int j = p + 1; j < q + 1; j++) {
        int key = vec[j];
        int i = j - 1;
        while (i >= p && vec[i] > key) {
            vec[i+1] = vec[i];
            i--;
        }
        vec[i+1] = key;
    }
}

//checks if select output is correct
bool checkSelect(int *vec, int size, int k, int val) {
    int minors = 0;
    int valIdx = 0;
    for(int i = 0; i < size; i++) {
        if(vec[i] <= val) {
            minors++;
            if(vec[i] > vec[valIdx]) {
                valIdx = i;
            }
        }
    }
    return minors == k && val == vec[valIdx];
}