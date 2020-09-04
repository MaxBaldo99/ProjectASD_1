#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct tree
{
    int key;
    int height;
    int color;
    char *details;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
};

/*
finds if exist a node with that key 
if true   --> return node
if false  --> return NULL
*/
struct tree *find(struct tree *node, int key);

/*
given a key
allocate memory for a node with that key
return the node
*/
struct tree *createNewNode(int key);

/*
insert the node in the tree
REQUIRE not exist another node with same key in the tree
*/
void insert(struct tree **root, struct tree *node);

/*
remove the node from the tree
free the memory of the node 
*/
void remove(struct tree **root, struct tree *node);

#pragma region balancedTree
//following methods needed only for BST with height <= log(n)

/*
do a right rotation of the node
*/
void rightRotate(struct tree **root, struct tree *node);

/*
do a left rotation of the node
*/
void *leftRotate(struct tree **root, struct tree *node);

/*
rebalance tree after insert
*/
void fixUpOnInsert(struct tree **root, struct tree *node);

/*
rebalance tree after delete
*/
void fixUpOnDelete(struct tree **root, struct tree *node);

#pragma endregion

#endif