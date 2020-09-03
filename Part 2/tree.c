#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "tree.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

struct tree *buildFromPolish(char *inputTree, size_t size) {
    struct tree *bt = NULL;
    buildFromPolishWriting(inputTree, size, &bt);
    return bt;
}

char *buildFromPolishWriting(char *inputTree, size_t size, struct tree **bt) {
    char *num[10]; //actual number (or NULL) found
    char *rest = malloc(size); //the rest of the input to read
    //copy in num chars rest till find space
    //substring rest from the first space (cut before)
    rest = nextWord(inputTree, size, num); 
    int n = atoi(num); //the number to add as int

    if(*bt == NULL) { //first time create the binary tree
        if(strcmp(num, "NULL") != 0) {
            *bt = create(n, NULL);
            rest = buildFromPolishWriting(rest, size, bt);
        } else {
            return NULL; //input is NULL
        }
    } else { //add son to the tree
        bool notNull = strcmp(num, "NULL") != 0;
        if(notNull) { 
            //if !NULL add num to bt->left
            //bt now point to bt->left
            add(n, true, NULL, *bt);
            //recursively add to bt->left
            rest = buildFromPolishWriting(rest, size, &(*bt)->left);
        }
        //left side done, now do right
        rest = nextWord(rest, size, num); 
        notNull = strcmp(num, "NULL") != 0; 
        if(notNull) {
            n = atoi(num);
            add(n, false, NULL, *bt); 
            //recursively add to bt->right
            //bt now point to bt->right
            rest = buildFromPolishWriting(rest, size, &(*bt)->right);
        }
    }
    return rest;
}

struct tree *create(int key, char *details) {
    struct tree *x = malloc(sizeof(struct tree));
    char *detail = malloc(sizeof(NULL));
    x->details = NULL;
    if(details != NULL) {
        detail = realloc(detail, strlen(details) * sizeof(char));
        strcpy(detail, details);
        x->details = detail;
    } else {
        free(detail);
    }
    x->key = key;
    x->parent = x->left = x->right = NULL;
    x->height = -1;
    x->color = -1;
    return x;
}

struct tree *add(int key, bool left, char *details, struct tree *parent) {
    struct tree *x = malloc(sizeof(struct tree));
    x->key = key;
    x->left = x->right = NULL;
    x->details = NULL;
    x->height = -1;
    x->color = -1;
    if(left && parent->left == NULL) {
        parent->left = x;
        x->parent = parent;
    } else if (!left && parent->right == NULL) {
        parent->right = x;
        x->parent = parent;
    } else {
        printf("error: cannot add if NOT NULL");
    }
    return x;
}

int height(const struct tree *node) {
    return node == NULL ? 0 : node->height;
}

void preOrder(struct tree *node) {
    if(node != NULL) {
        print(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(struct tree *node) {
    if(node != NULL) {
        inOrder(node->left);
        print(node);
        inOrder(node->right);
    }
}

void postOrder(struct tree *node) {
    if(node != NULL) {
        print(node);
        postOrder(node->left);
        postOrder(node->right);
    }
}


//polish is same as pre order but with nulls printed too
void polishOrder(struct tree *node) {
    print(node);
    if(node != NULL) {
        polishOrder(node->left);
        polishOrder(node->right);
    }
}

void print(struct tree *node) {
    if(node != NULL) {
        printf("%d", node->key);
        if(node->details != NULL) {
            printf(":%s", node->details);
        }
        if(node->height >= 0) {
            printf(":%d", node->height);
        }
        if(node->color >= 0) {
            printf(":%s", color(node->color));
        }
    } else {
        printf("NULL");
    }
    printf(" ");
}

struct tree *BSTinsert(struct tree *root, struct tree *node) {
    struct tree *y = NULL;
    y = malloc(sizeof(struct tree));
    struct tree *x = NULL;
    x = malloc(sizeof(struct tree));

    y = NULL;
    x = root;
    while(x != NULL) {
        y = x;
        if(x->key > node->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    //x = y;
    if(y == NULL) {
        root = node;
    } else {
        node->parent = y;
        if(node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }
    }
    free(x);
    return root;
}

struct tree *BSTfind(int key, const struct tree *root) {
    if(root == NULL || root->key == key) {
        return root;
    } else if(key > root->key) {
        BSTfind(key, root->right);
    } else {
        BSTfind(key, root->left);
    }
}

/*
    algoritmo per cancellazione:
        - se 
            almeno uno dei due figli è NULL allora posso cancellare il nodo
        - altrimenti
            devo fare swap fra node e successore (che avrà almeno un figlio NULL)
            e poi potrò cancellare node
*/
struct tree *BSTdelete(struct tree *root, struct tree *node, bool successor) {
    struct tree *deleteNode = malloc(sizeof(struct tree));
    if(node->left == NULL || node->right == NULL) {
        //se almeno uno dei figli di node è NULL
        deleteNode = node; 
    } else {
        //se invece entrambi figli non sono NULL cerco successore
        deleteNode = successor ? BSTsuccessor(node) : BSTpredecessor(node);
    }
    //ora so che x ha almeno un figlio NULL
    struct tree *delNodeSon = NULL;
    //assegno a y il figlio non NULL (se esiste) di x
    //y è NULL solo se successore di node è foglia
    delNodeSon = deleteNode->left != NULL ? deleteNode->left : deleteNode->right;
    if (delNodeSon != NULL) {
        //genitore di y diventa il genitore di x
        delNodeSon->parent = deleteNode->parent;
    }
    if(deleteNode->parent == NULL) {
        //x è radice e ha almeno un figlio NULL
        root = delNodeSon; 
    } else if(deleteNode == deleteNode->parent->left) {
        //se x era un figlio sx, il nuovo figlio sx del padre di x è il figlio di x
        deleteNode->parent->left = delNodeSon;
    } else {
        //se x era un figlio dx, il nuovo figlio dx del padre di x è il figlio di x
        deleteNode->parent->right = delNodeSon;
    }
    if(deleteNode != node) {
        //x è il successore di node
        node->key = deleteNode->key;
        node->details = deleteNode->details;
    }
    //free(node);
    //free(node->details);
    //free(x->details);
    free(deleteNode);
    //free(delNodeSon);
    return root;
}

//assume node is not the root, has a dad
//node will go up
struct tree *rightRotate(struct tree *root, struct tree *node) {
    struct tree *oldDad = NULL;
    struct tree *oldSon = NULL; //right son
    oldDad = node->parent;
    oldSon = node->right;
    if(oldDad != root) {
        //allaccio nonno node con node che diventa suo padre
        if(oldDad == oldDad->parent->left) {
            node->parent->parent->left = node;
        } else {
            node->parent->parent->right = node;
        }
        node->parent = oldDad->parent;
    } else {
        //node diventa radice
        root = node;
        node->parent = NULL;
    }
    node->right = oldDad;
    oldDad->left = oldSon;
    oldDad->parent = node;
    if(oldSon != NULL) {
        oldSon->parent = oldDad;
    }
    return root;
}

//assume node is not the root, has a dad
//node will go up
struct tree *leftRotate(struct tree *root, struct tree *node) {
    struct tree *oldDad = NULL;
    struct tree *oldSon = NULL; //left son
    oldDad = node->parent;
    oldSon = node->left;
    if(node->parent->parent != NULL) { //uguale a dire node->parent == root
        //allaccio nonno node con node che diventa suo padre
        if(node->parent == node->parent->parent->left) {
            node->parent->parent->left = node;
        } else {
            node->parent->parent->right = node;
        }
        node->parent = oldDad->parent;
    } else {
        //node diventa radice
        root = node;
        node->parent = NULL;
    }
    node->left = oldDad;
    oldDad->right = oldSon;
    oldDad->parent = node;
    if(oldSon != NULL) {
        oldSon->parent = oldDad;
    }
    return root;
}

/*
    can happen:
        - (before rotation) node height nH + 1 was equal to ex-father height hR (nH + 1 == hR)
        - node->right (ex-father) decrease his height: hR' = hR - 2
        - node goes on top and keep his height hN' = hN'
        - now node->parent should check if decrease one but update height doesnt check it
            because stops at node which keeps his height
    so:
        - must be checked node->parent height
            if it changes then error goes up
*/
//assume node has grandfather
struct tree *doubleRotateLeftRight(struct tree *root, struct tree *node) {
    root = leftRotate(root, node);
    updateHeight(node->left);
    root = rightRotate(root, node);
    updateHeight(node->right);
    return root;
}

//assume node has grandfather
struct tree *doubleRotateRightLeft(struct tree *root, struct tree *node) {
    root = rightRotate(root, node);
    updateHeight(node->right);
    root = leftRotate(root, node);
    updateHeight(node->left);
    return root;
}

struct tree *BSTpredecessor(struct tree *node) {
    if(node->left != NULL) {
        return BSTmax(node->left);
    } else {
        struct tree *y = malloc(sizeof(struct tree));
        while(y != NULL && node != y->right) {
            node = y;
            y = node->parent;
        }
        return y;
    }
}

struct tree *BSTsuccessor(struct tree *node) {
    if(node->right != NULL) {
        return BSTmin(node->right);
    } else {
        struct tree *y = malloc(sizeof(struct tree));
        while(y != NULL && node != y->left) {
            node = y;
            y = node->parent;
        }
        return y;
    }
}

struct tree *BSTmin(const struct tree *node) {
    if(node == NULL) {
        return NULL;
    } else {
        return goDeepOneDirection(node, true);
    }
}

struct tree *BSTmax(const struct tree *node) {
    if(node == NULL) {
        return NULL;
    } else {
        return goDeepOneDirection(node, false);
    }
}

//error if node == NULL
struct tree *goDeepOneDirection(const struct tree *node, bool left) {
    struct tree *next = left ? node->left : node->right;
    if(next == NULL) {
        return node;
    } else {
        return goDeepOneDirection(next, left);
    }
}

void destroyTree(struct tree *node) {
    if(node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        free(node->details);
        free(node);
    }
}

//-------------------------------------------------------------------------------------------
#pragma region AVL

//set node->height to 1 + max of height of his sons
//then do it to his father
//go up to the root, stops if node->height doesnt change
void updateHeight(struct tree *node) {
    if(node != NULL) {
        changeHeight(node);
        updateHeight(node->parent);
    }
}

//set node->height to 1 + max of height of his sons
void changeHeight(struct tree *node) {
    if(node != NULL) {
        node->height = 1 + max(h(node->left), h(node->right));
    }
} 

//insert node and eventually balance tree
struct tree *AVLInsert(struct tree *root, struct tree *node, bool balance) {
    root = BSTinsert(root, node);
    updateHeight(node);
    //polishOrder(root);
    //printf("\n");
    //balance only if have dad and grandad, otherwise already balanced
    if(balance && node->parent != NULL && node->parent->parent != NULL) {
        root = AVLBalanceIfNeeded(root, node->parent->parent);
    }
    return root;
}

//delete node and eventually balance it
struct tree *AVLDelete(struct tree *root, struct tree *node, bool balance) {
    struct tree *temp = NULL;
    if(node->left == NULL || node->right == NULL) {
        if(node->left == NULL && node->right == NULL) {
            temp = node->parent;
        } else {
            temp = node->left == NULL ? node->right : node->left;
        }
    } else {
        temp = BSTmin(node->right)->parent;
    }
    root = BSTdelete(root, node, true);
    updateHeight(temp);

    if(balance && temp != NULL) {
        root = AVLBalanceIfNeeded(root, temp);
    }
    return root;
}

struct tree *AVLBalanceIfNeeded(struct tree *root, struct tree *node) {
    if(node != NULL) {
        int dif = hDiff(node);
        if(dif < -1) {
            root = AVLFixUp(root, node->right);
        } else if(dif > 1) {
            root = AVLFixUp(root, node->left);
        } else {
            root = AVLBalanceIfNeeded(root, node->parent);
        }
    }        
    return root;
}

//balance tree
struct tree *AVLFixUp(struct tree *root, struct tree *node) {
    if(node != NULL) {
        struct tree *dad = node->parent;
        if(dad != NULL) {
            struct tree *son = h(node->left) > h(node->right) ? node->left : node->right;
            int dadHDif = hDiff(dad);
            int nodeHDif = hDiff(node);
            bool a, b;
            if(abs(dadHDif) > 1) {
                if((dadHDif > 1 && nodeHDif < 0) || (dadHDif < -1 && nodeHDif > 0)) {
                    if(dadHDif > 1) {
                        root = doubleRotateLeftRight(root, son);         
                    } else {
                        root = doubleRotateRightLeft(root, son);
                    }
                    dad = node->parent;
                } else { //((dadHDif > 1 && nodeHDif >= 0) ||(dadHDif < -1 && nodeHDif <= 0))
                    if(dadHDif > 0) {
                        root = rightRotate(root, node);
                    } else {
                        root = leftRotate(root, node);
                    }
                }
            }
            updateHeight(son);
            updateHeight(dad);
            root = AVLBalanceIfNeeded(root, dad);
        }
    }
    return root;
}

#pragma endregion AVL

//-------------------------------------------------------------------------------------------
#pragma region RBT

//insert node and eventually balance tree
struct tree *RBTInsert(struct tree *root, struct tree *node) {
    root = BSTinsert(root, node);
    node->color = node == root ? black : red;
    //polishOrder(root);
    //printf("\n");
    //balance only if have dad and grandad, otherwise already balanced
    if(node->parent != NULL && node->parent->parent != NULL && node->parent->color == red) {
        root = RBTFixUpOnInsert(root, node);
    }
    return root;
}

//assume max(T1) < x->key < min(T2)
struct tree *RBTJoinPublic(struct tree *T1, struct tree *T2, int key) {
    struct tree *x = create(key, NULL);
    if(blackHeight(T1) <= blackHeight(T2)) {
        return RBTJoinPrivate(T1, T2, x);
    } else {
        return RBTJoinPrivate(T2, T1, x);
    }
}

//assume blackHeight(T1) <= blackHeight(T2
//assume max(T1) < x->key < min(T2) || max(T2) < x->key < min(T1)
struct tree *RBTJoinPrivate(struct tree *T1, struct tree *T2, struct tree *x) {
    struct tree *node = T2;
    while(blackHeight(T1) < blackHeight(node) || node->color == 0) {
        //se chiavi t1 sono minori t2 ==> scendo sempre a sx
        //se chiavi t1 sono maggiori t1 ==> scendo sempre a dx
        node = T1->key < T2->key ? node->left : node->right;
    }
    struct tree *y = NULL;
    if(T1->key < T2->key) {
        //chiavi in T1 sono tutte minori di T2 ==> min(T1) diventa minimo generale
        y = node->left;
        node->left = x;
        x->left = T1;
        x->right = y;
    } else {
        //chiavi in T1 sono tutte maggiori di T2 ==> max(T1) diventa massimo generale
        y = node->right;
        node->right = x;
        x->right = T1;
        x->left = y;
    }
    T1->parent = x;
    y->parent = x;
    T2 = RBTFixUpOnInsert(T2, x);
    return T2;
}

int blackHeight(struct tree *node) {
    if(node == NULL) return 0;
    else {
        int bh = node->left->color == black ? 1 : 0;
        return bh + blackHeight(node->left);
    }
}

struct tree *RBTFixUpOnInsert(struct tree *root, struct tree *node) {
    if(node != NULL && node->parent != NULL && node->parent->color == red) {
        bool leftSon = leftSon(node);
        bool uncleIsOpp = true;
        struct tree *uncl = uncle(node, &uncleIsOpp);
        if((uncl == NULL || uncl->color == black) && uncleIsOpp) {
            //caso fortunato: zio black opposto a x
            node->parent->color = black;
            node->parent->parent->color = red;
            root = leftSon ? rightRotate(root, node->parent) : leftRotate(root, node->parent);
        } else if(uncl == NULL || uncl->color == black) {
            //caso quasi fortunato: zio black non opposto a x
            struct tree *dad = node->parent;
            root = leftSon ? rightRotate(root, node) : leftRotate(root, node);
            root = RBTFixUpOnInsert(root, dad);
        } else { //(uncl->color == red)
            node->parent->color = uncl->color = black;
            node->parent->parent->color = red;
            root = RBTFixUpOnInsert(root, node->parent->parent);
        }
    } else if(node != NULL && root == node) {
        node->color = black; //convenzione
    }
    return root;
}

struct tree *uncle(struct tree *node, bool *isOpposite) { 
    if(node != NULL && node->parent != NULL && node->parent->parent != NULL) {
        if(leftSon(node->parent)) {
            *isOpposite = leftSon(node);
            return node->parent->parent->right;
        } else {
            *isOpposite = !leftSon(node);
            return node->parent->parent->left;
        }
    }
    return NULL;
}

struct tree *RBTDelete(struct tree *root, struct tree *node) {
    struct tree *temp = NULL;
    struct tree *tempSon = NULL;
    struct tree *tempDad = NULL;
    bool fixUp = true;
    if(node->left == NULL || node->right == NULL) {
        temp = node;
    } else {
        temp = BSTpredecessor(node);
    }
    bool tempLeft = leftSon(temp);
    tempDad = temp->parent;
    tempSon = temp->left == NULL ? temp->right : temp->left;
    fixUp = (temp->color == black && (tempSon == NULL || tempSon->color == black));
    if(!fixUp && tempSon != NULL && tempSon->color == red) {
        tempSon->color = black;
    }
    root = BSTdelete(root, node, false);
    if(fixUp) {
        root = RBTFixUpOnDelete(root, tempSon, tempDad, tempLeft);
    }
    return root;
}

struct tree *RBTFixUpOnDelete(struct tree *root, struct tree *node, struct tree *dad, bool nodeLeft) { 
    struct tree *brother = nodeLeft ? dad->right : dad->left;
    if((node == NULL || node->color == black) && brother != NULL) {
        bool isOpposite = false;
        struct tree *nephew = oppositeRedSon(brother, &isOpposite);
        if(nephew != NULL && nephew->color == red && isOpposite) {
            //caso fortunato: node ha nipote red e opposto
            nephew->color = black;
            brother->color = dad->color;
            dad->color = black;
            root = nodeLeft ? leftRotate(root, brother) : rightRotate(root, brother);
        } else if (nephew != NULL && nephew->color == red) {
            //caso quasi fortunato: node ha nipote red non opposto
            nephew->color = black;
            brother->color = red;
            root = leftSon(nephew) ? rightRotate(root, nephew) : leftRotate(root, nephew);
        } else if (brother->color == black && (nephew == NULL || nephew->color == black)) {
            //caso sfortunato: node ha nipoti e fratello black
            if(dad->color == red) {
                dad->color = black;
                brother->color = red;
            } else {
                root = RBTFixUpOnDelete(root, dad, dad->parent, leftSon(dad));
            }
        } else if(brother->color == red && (nephew == NULL || nephew->color == black)) {
            brother->color = black;
            dad->color = red;
            root = nodeLeft ? leftRotate(root, brother) : rightRotate(root, brother);
            root = RBTFixUpOnDelete(root, node, dad, nodeLeft);
        } else {
            printf("WTF DUDE\n");
        }
    }
    return root;
}

//ritorna un nipote di cui node è nonno
//solo dal lato di left
//se esiste, ritorna il nipote rosso e opposto
//se esiste, ritorna l'altro nipote rosso
//se esiste, ritorna un nipote nero
//else, NULL se non ha nipoti
struct tree *oppositeRedSon(struct tree *node, bool *isOpposite) {
    if(node != NULL) {
        if(*isOpposite = (!leftSon(node) && node->right != NULL && node->right->color == red)) {
            return node->right;
        }
        if(*isOpposite = (leftSon(node) && node->left != NULL && node->left->color == red)) {
            return node->left;
        }
        *isOpposite = false;
        if(node->right != NULL && node->right->color == red) return node->right;
        if(node->left != NULL && node->left->color == red) return node->left;
        return node->left != NULL ? node->left : node->right;
    }
    return NULL;
}

struct tree *brother(struct tree *node) {
    if(node == NULL || node->parent == NULL) {
        return NULL;
    } else {
        return node == node->parent->left ? node->parent->right : node->parent->left;
    }
}

#pragma endregion RBT
//-------------------------------------------------------------------------------------------

void printTreeNice(struct tree *root, struct tree *node, int i, int level, int printed, bool left) {
    if(node != NULL) {
        if(printed == 0) {
            for(int i = 0; i < h(root) - level - 1; i++) {
                printf("\t");
            }
        }
        struct tree *next = NULL;
        struct tree *dad = NULL;
        dad = next = node;
        //scendi
        while(i < level && next != NULL) {
            dad = next;
            next = nextNode(next, left);
            i++;
            left = true;
        }
        print(next);
        printf("\t");
        if(level == 1) {
            printf("\t");
        }
        if(next != root && dad != NULL) {
            print(dad->right);
            printed++;
        }
        printed++;;
        //risali
        int toPrint = power(2, level);
        if(printed == toPrint) {
            printf("\n");
            level++;
            if(level < h(root)) {
                printTreeNice(root, root, 0, level, 0, true);
            }
        } else {
            printf(",\t");
            if((printed / 2) == toPrint) {
                printf("\t");
            }
            next = dad;
            i = level - i;
            left = true;
            while(next != root && left) {
                left = next == next->parent->right;
                next = next->parent;
                i++;
            }
            printTreeNice(root, next, level - i - 1, level, printed, false);
        }
    } else {
        print(node);
    }
}

int power(int base, int exp) {
    if(exp == 0) {
        return 1;
    }
    int k = base;
    for(int i = 0; i < exp - 1; i++) {
        base = base * k;
    }
    return base;
}

struct tree *nextNode(struct tree *node, bool left) {
    return node == NULL ? NULL : left ? node->left : node->right;
}