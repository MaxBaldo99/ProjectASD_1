#include "utility.h"
#include <assert.h>

#define BLOCK_SIZE 5

int quickSelect(int* vec, int p, int q, int k);
int heapSelect(MinHeap h1, MinHeap h2, int k);
int MOMSelect(int *array, int left, int right, int target);
int getMedianOfMedians(int *array, int left, int right);
int partitionPivot(int *vec, int p, int q, int pivot);
void quickSort(int* vec, int p, int q);
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
int quickSelect(int* vec, int p, int q, int k) {
    // we assume that k is in the interval of p and q
    assert (k > 0 && k <= q - p + 1);      
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
   while (p <= q) { 
        int index = partition(vec, p, q); 
        if (index == k - 1) {
            return vec[index]; 
        } else if (index > k - 1) {
            q = index - 1;
        } else {
            p = index + 1; 
        }
    } 
    return -1;
}

int heapSelect(MinHeap h1, MinHeap h2, int k) {
    h1.buildMinHeap();
    cout << h1.vec;
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

//Median of Medians Select: 
//T(n) = u(n) in best, median, worst case
int MOMSelect(int *array, int left, int right, int target) {
    int medianPos;
    bool search = true;
    while(search) {
        int median = getMedianOfMedians(array, left, right);
        //printArray(array, right, " ", "<<", ">>");
        //printf("partition on %d\n", median);
        medianPos = partitionPivot(array, left, right - 1, median);
        //printf("median: %d, median pos: %d\n", median, medianPos);
        //printArray(array, right, " ", "<<", ">>");
        int k = medianPos - left + 1;
        if (target < k) {
            right = medianPos;
        } else if (target > k) {
            left = medianPos + 1;
            target -= k;
        } else {
            search = false;
        }
    }
    return array[medianPos];
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