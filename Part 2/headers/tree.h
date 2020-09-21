#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct tree
{
    int key;
    int height;
    int color;
    //char *details;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
};

//generic binary tree
//return in node is a left or right son
#define isLeftSon(x) (x->parent->left == x ? true : false)
struct tree *create(int key);
struct tree *add(int key, bool left, char *details, struct tree *parent);
void preOrder(struct tree *node);
void inOrder(struct tree *node);
void postOrder(struct tree *node);
//void destroyTree(struct tree *& node);
struct tree *destroyTree(struct tree *&root);
void polishOrder(struct tree *node);
struct tree *goDeepOneDirection(struct tree *node, bool left);

//BST Tree
struct tree *BSTinsert(struct tree *&root, struct tree *node);
struct tree *BSTfind(struct tree *root, int key);
struct tree *BSTdelete(struct tree *root, struct tree *node, bool successor);
struct tree *BSTpredecessor(struct tree *node);
struct tree *BSTsuccessor(struct tree *node);
struct tree *BSTmin(struct tree *node);
struct tree *BSTmax(struct tree *node);

//metodi per bilanciamento
struct tree *rightRotate(struct tree *root, struct tree *node);
struct tree *leftRotate(struct tree *root, struct tree *node);
struct tree *doubleRotateLeftRight(struct tree *root, struct tree *node);
struct tree *doubleRotateRightLeft(struct tree *root, struct tree *node);

//AVL Tree
//ritorna altezza nodo, 0 se nodo è null
#define h(x) ((x == NULL) ? 0 : x->height)
//ritorna la altezza nodo->left - altezza nodo right. se nodo è null ritorna 0
#define hDiff(x) (x == NULL ? 0 : (h(x->left) - h(x->right)))
void AVLupdateHeight(struct tree *node);
void AVLchangeHeight(struct tree *node);
struct tree *AVLdelete(struct tree *root, struct tree *node);
struct tree *AVLinsert(struct tree *&root, struct tree *node);
struct tree *AVLbalanceIfNeeded(struct tree *root, struct tree *node);
struct tree *AVLfixUp(struct tree *root, struct tree *node);

//RB Tree
//color to string
#define color(x) (x == 0 ? "red" : x == 1 ? "black" : "colorError")
#define red 0
#define black 1
struct tree *RBTinsert(struct tree *&root, struct tree *node);
struct tree *RBTjoinPublic(struct tree *T1, struct tree *T2, int key);
struct tree *RBTjoinPrivate(struct tree *T1, struct tree *T2, struct tree *x);
int RBTblackHeight(struct tree *node);
struct tree *RBTfixUpOnInsert(struct tree *root, struct tree *node);
struct tree *RBTdelete(struct tree *root, struct tree *node);
struct tree *RBTfixUpOnDelete(struct tree *root, struct tree *node, struct tree *dad, bool nodeLeft);
struct tree *RBToppositeRedSon(struct tree *node, bool *isOpposite);

//useful
void print(struct tree *node);
void printTreeNice(struct tree *root, struct tree *node, int i, int level, int printed, bool left);
struct tree *nextNode(struct tree *node, bool left);
struct tree *brother(struct tree *node);
struct tree *uncle(struct tree *node, bool *isOpposite);
int height(const struct tree *node);
int power(int base, int exp);
bool isBST(struct tree *bt);
bool isBSTPrivate(struct tree *bt, int l, int r);

#endif