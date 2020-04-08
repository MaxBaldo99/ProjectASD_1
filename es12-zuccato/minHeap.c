//#include "minHeap.h"

int HEAP_LENGTH = 100;
int HEAP_SIZE = 0;

int heapsize() {
    return HEAP_SIZE;
}

int heaplength() {
    return HEAP_LENGTH;
}

void insert(int *array, int size, int length, int val) {
    if(size < length) {
        array[size] = val;
        size++;
        heapifyFromRight(array, size - 1);
    }    
}
void heapifyFromRight(int *array, int i) {
    while(i > 0 && array[i] < array[parent(i)]) {
        swap(array, i, parent(i));
        i = parent(i);
    }
}

void heapifyFromLeft(int *array, int size, int i) {
    int l = left(i);
    int r = right(i);
    int minor = 0;
    if(l < size && array[l] < array[i]) {
        minor = l;
    } else {
        minor = i;
    }
    if(r < size && array[r] < array[minor]) {
        minor = r;
    }
    if(minor != i) {
        swap(array, i, minor);
        heapifyFromLeft(array, size, minor);
    }
}

int left(int i) {
    return 2*i + 1;
}

int right(int i) {
    return 2*i + 2;
}

int minKey() {
    return 0;
}

int parent(int i) {
    if(i % 2 == 0) {
        i--;
    }
    return i/2;
}

void buildMinHeap(int *array, int length) {
    HEAP_SIZE = length;
    for(int i = HEAP_SIZE/2; i >= 0; i--) {
        heapifyFromLeft(array, HEAP_SIZE, i);
    }
}

int extractMinHeap(int *array, int size) {
    size--;
    swap(array, 0, size);
    heapifyFromLeft(array, size, 0);
    return array[size];
}

void clearHeap(int *array, int size) {
    initializeArray(array, size);
    size = 0;
}

int extractMinHeap2(int *values, int *size, int *indexes) {
    *size = *size - 1;
    swap(values, 0, *size);
    swap(indexes, 0, *size);
    //printArrayBasic(indexes, *size);
    //printArrayBasic(values, *size);
    heapifyFromLeft2(values, *size, 0, indexes);
    return indexes[*size];
}

void heapifyFromLeft2(int *values, int size, int i, int *indexes) {
    int l = left(i);
    int r = right(i);
    int minor = 0;
    if(l < size && values[l] < values[i]) {
        minor = l;
    } else {
        minor = i;
    }
    if(r < size && values[r] < values[minor]) {
        minor = r;
    }
    if(minor != i) {
        swap(indexes, i, minor);
        swap(values, i, minor);
        heapifyFromLeft2(values, size, minor, indexes);
    }
}

void insert2(int *array, int size, int length, int val, int *indexes, int pos) {
    if(size < length) {
        array[size] = val;
        indexes[size] = pos;
        heapifyFromRight2(array, size, indexes);
        size++;
    }    
}

void heapifyFromRight2(int *array, int i, int *indexes) {
    while(i > 0 && array[i] < array[parent(i)]) {
        swap(indexes, i, parent(i));
        swap(array, i, parent(i));
        i = parent(i);
    }
}