#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
//#include "useful.h"

void buildMinHeap(int *array, int length);
void insert(int *array, int size, int length, int val);
void heapifyFromLeft(int *array, int size, int i);
void heapifyFromRight(int *array, int i);
int extractMinHeap(int *array, int size);
void clearHeap(int *array, int size);
int left(int i);
int right(int i);
int minKey();
int parent(int i);
int heapsize();
int heaplength();

void insert2(int *array, int size, int length, int val, int *indexes, int pos);
void heapifyFromLeft2(int *values, int size, int i, int *indexes);
int extractMinHeap2(int *values, int *size, int *indexes);
void heapifyFromRight2(int *array, int i, int *indexes);
#endif