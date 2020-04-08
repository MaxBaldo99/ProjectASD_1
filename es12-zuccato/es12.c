#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
//#include "useful.h"
//#include "minHeap.h"

int selectionSort(int *array, int size, int target);
int quickSelect(int *array, int left, int right, int target);
int heapSelect(int *array, int size, int target);
int selection(int *array, int left, int right, int target);
int partition(int *array, int p, int q, int val);
int partitionOriginal(int *array, int p, int q);
void insertionSort(int *array, int p, int q);
int getMinimum(int *array, int i, int j);

//int LENGTH = 2000;
int size = 0;
int BLOCK_SIZE = 5;

int main() {
    
    srand(time(NULL));

    //int array[LENGTH];
    /*
    for(int i = 0; i < size; i++) {
        array[i] = rand() / 100000000;
    }
    printArrayBasic(array, size);
    */
    //size = getArrayFromStdin(array, LENGTH);
    int *array = getArrayFromStdinDynamic(&size);
    int pos = size/2;
    scanf("%d", &pos);
    //printArray(array, size, ", ", "<", ">");
    //printf("...executing...\n");

    int val;
    val = selection(array, 0, size, pos);
    //val = heapSelect(array, size, pos);
    //val = quickSelect(array, 0, size - 1, pos);
    //val = selectionSort(array, size, pos);
    //int index = partition(array, 0, size-1, pos);

    //printArray(array, size, ", ", "<", ">");
    //val = pos;
    //printf("the position of %d in array (if it is present) is: %d\n", val, index);
    printf("%d\n", val);

    //check if it is right
    /*
    bool errors = false;
    for(int i = 0; i < size; i++) {
        if(errors = !((array[i] <= val && i <= pos) || ((array[i] >= val && i > pos))))
            printf("ERROR %d\n", i);
    }
    if(!errors) {
        printf("ok\n");
    }
    */
    return 0; 
}

//A => O(n k) sia pessimo sia medio
int selectionSort(int *array, int size, int target) {
    for(int i = 0; i < target; i++) {
        getMinimum(array, i, size - 1);
    }
    return array[target - 1];
}

//B ==> O(n2) pessimo, O(n) medio
int quickSelect(int *array, int left, int right, int target) {
    if(left > right) {
        return -1;
    } 
    int pos = partition(array, left, right, array[left]);
    if(target - 1 == pos) {
        return array[target - 1];
    } else if(target <= pos) {
        return quickSelect(array, left, pos - 1, target);
    } else {
        return quickSelect(array, pos + 1, right, target);
    }
}

//C => O(k log k + n) sia pessimo sia medio
int heapSelect(int *array, int size, int target) { 
    buildMinHeap(array, size);
    //printArrayBasic(array, size);
    int bIndexes[size];
    int bValues[size];
    int bSize = 1;
    bIndexes[minKey()] = minKey();
    bValues[minKey()] = array[minKey()];
    int count = 0;
    for(int i = 0; i < target - 1; i++) {
        int minIndex = extractMinHeap2(bValues, &bSize, bIndexes); //bSize-- inside
        int pos = left(minIndex);
        if(pos < size) {
            insert2(bValues, bSize, size, array[pos], bIndexes, pos); 
            bSize++;
            pos++; //now get right
            if(pos < size) {
                insert2(bValues, bSize, size, array[pos], bIndexes, pos); 
                bSize++;
            }
        } else {
            count++;
            //printf("  %d:\t%d\t%d\t%d\n", i, bValues[minKey()], pos, count);
        }
        
        printf("%d:\t%d\n", i, bValues[minKey()]);
        /*printf("indici: ");
        printArrayBasic(bIndexes, bSize);
        printf("valori: ");
        printArrayBasic(bValues, bSize);
        printf("\n");*/
    }
    //int minIndex = extractMinHeap2(bValues, &bSize, bIndexes); //bSize-- in function
    return bValues[minKey()];
}

//D => O(n) sia pessimo sia medio
int selection(int *array, int left, int right, int target) {    
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
    //printArray(array, size, ", ", "<", ">");
    int median = selection(B, 0, blocks, blocks/2);
    //printArray(array, right, " ", "<<", ">>");
    //printf("partition on %d\n", median);
    int medianPos = partition(array, left, right-1, median);
    //printf("median pos: %d\n", medianPos);
    //printArray(array, right, " ", "<<", ">>");
    int k = medianPos - left + 1;
    if (target == k) {
        return array[medianPos];
    } else if (target < k) {
        return selection(array, left, medianPos, target);
    } else {
        return selection(array, medianPos+1, right, target-k);
    }
}

/**
 *  takes parameter value as pivot and places:
 *   - elements <= pivot to his left [p, i]
 *   - elements > pivots to his right [i+1, q-1]
 * @param array the array to edit
 * @param p the min index in the array REQUIRE 0 <= i < q <= array.length (p is included)
 * @param q the max index in the array REQUIRE 0 <= i < q < array.length (q is included)
 * @param pivot the value (not need to be in the array)
 * @return the index of the last element <= val
 */
int partition(int *array, int p, int q, int pivot) {
    int i = p;
    int j = q;
    int valIndex = -1;
    while(i <= j) {
        if(array[i] <= pivot) {
            valIndex = array[i] == pivot ? i : valIndex;
            i++;
        } else {
            swap(array, j, i);
            j--;
        }
    }
    if(valIndex >= 0) {
        swap(array, j, valIndex);
    }
    return j;
}

int partitionOriginal(int *array, int p, int q) {
    int x = array[q];
    int i = p;
    for(int j = p; j < q; j++) {
        if(array[j] <= x) {
            swap(array, i++, j);
        }
    }
    return i;
}

void insertionSort(int *array, int p, int q) {
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

//i, j compresi nell'array
int getMinimum(int *array, int i, int j) {
    int index = i;
    for(int k = i+1; k <= j; k++) {
        if(array[k] < array[index]) {
            index = k;
        }
    }
    if(index != i) {
        swap(array, index, i);
    }
    return index;
}

//FROM USEFUL.C
/*
void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int getArrayFromStdin(int *array, int length) {
    int size = 0;
    char num[length];
    num[0] = '\0';
    int i = 0;
    int befC = 0;
    int c = getchar();
    bool end = false;
    while(!end) {
        if(c == ' ' || (end = (c == '\n' || c == EOF || c == '\0'))) {
            if(i > 0 && befC != ' ') {
                array[size] = atoi(num);
                size++;
            }
            i = 0;
        } else {
            num[i] = c;
            i++;
        }
        if(!end) {
            num[i] = '\0';
            befC = c;
            c = getchar();
        }
    }
    return size;
}
*/