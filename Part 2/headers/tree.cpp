#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "tree.h"

using namespace std;

#define max(x, y) (((x) > (y)) ? (x) : (y))

struct tree *create(int key) {
    struct tree *x = new struct tree;
    //x->details = nullptr;
    x->key = key;
    x->left = x->right = x->parent = nullptr;
    x->height = -1;
    x->color = -1;
    return x;
}

struct tree *add(int key, bool left, char *details, struct tree *parent) {
    struct tree *x = new struct tree;
    x->key = key;
    x->left = x->right = x->parent = nullptr;
    //x->details = nullptr;
    x->height = -1;
    x->color = -1;
    if(left && parent->left == nullptr) {
        parent->left = x;
        x->parent = parent;
    } else if (!left && parent->right == nullptr) {
        parent->right = x;
        x->parent = parent;
    } else {
        printf("error: cannot add if NOT nullptr");
    }
    return x;
}

int height(const struct tree *node) {
    return node == nullptr ? 0 : node->height;
}

void preOrder(struct tree *node) {
    if(node != nullptr) {
        print(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(struct tree *node) {
    if(node != nullptr) {
        inOrder(node->left);
        print(node);
        inOrder(node->right);
    }
}

void postOrder(struct tree *node) {
    if(node != nullptr) {
        print(node);
        postOrder(node->left);
        postOrder(node->right);
    }
}

//polish is same as pre order but with nullptrs printed too
void polishOrderNice(struct tree *node, int tab) {
    for(int i = 0; i < tab; i++) {
        printf("\t");
    }
    print(node);
    if(node != nullptr) {
        printf(" {\n");
        tab++;
        polishOrderNice(node->left, tab);
        polishOrderNice(node->right, tab);   
        for(int i = 0; i < tab - 1; i++) {
            printf("\t");
        }
        printf(" }\n");
    } else {
        printf("\n");
    }
}

//polish is same as pre order but with nullptrs printed too
void polishOrder(struct tree *node) {
    print(node);
    if(node != nullptr) {
        polishOrder(node->left);
        polishOrder(node->right);
    }
}

void print(struct tree *node) {
    if(node != nullptr) {
        printf("%d", node->key);
        /*if(node->details != nullptr) {
            printf(":%s", node->details);
        }*/
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

struct tree *BSTinsert(struct tree *&root, struct tree *node) {
    struct tree *y = nullptr;
    struct tree *x = nullptr;

    y = nullptr;
    x = root;
    while(x != nullptr) {
        y = x;
        if(x->key > node->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    //x = y;
    if(y == nullptr) {
        root = node;
    } else {
        node->parent = y;
        if(node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }
    }
    return root;
}

struct tree *BSTfind(struct tree *root, int key) {
    if(root == nullptr || root->key == key) {
        return root;
    } else if(key > root->key) {
        return BSTfind(root->right, key);
    } else {
        return BSTfind(root->left, key);
    }
}

/*
    algoritmo per cancellazione:
        - se 
            almeno uno dei due figli è nullptr allora posso cancellare il nodo
        - altrimenti
            devo fare swap fra node e successore (che avrà almeno un figlio nullptr)
            e poi potrò cancellare node
*/
struct tree *BSTdelete(struct tree *root, struct tree *node, bool successor) {
    struct tree *delNode = nullptr;
    if(node->left == nullptr || node->right == nullptr) {
        //se almeno uno dei figli di node è nullptr
        delNode = node; 
    } else {
        //se invece entrambi figli non sono nullptr cerco successore
        delNode = successor ? BSTsuccessor(node) : BSTpredecessor(node);
    }
    //ora so che x ha almeno un figlio nullptr
    struct tree *delNodeSon = nullptr;
    //assegno a y il figlio non nullptr (se esiste) di x
    //y è nullptr solo se successore di node è foglia
    delNodeSon = delNode->left != nullptr ? delNode->left : delNode->right;
    if (delNodeSon != nullptr) {
        //genitore di y diventa il genitore di x
        delNodeSon->parent = delNode->parent;
    }
    if(delNode->parent == nullptr) {
        //x è radice e ha almeno un figlio nullptr
        root = delNodeSon; 
    } else if(delNode == delNode->parent->left) {
        //se x era un figlio sx, il nuovo figlio sx del padre di x è il figlio di x
        delNode->parent->left = delNodeSon;
    } else {
        //se x era un figlio dx, il nuovo figlio dx del padre di x è il figlio di x
        delNode->parent->right = delNodeSon;
    }
    if(delNode != node) {
        //x è il successore di node
        node->key = delNode->key;
        //node->details = deleteNode->details;
    }
    //free(node);
    //free(node->details);
    //free(x->details);
    delete delNode;
    //free(delNodeSon);
    return root;
}

//assume node is not the root, has a dad
//node will go up
struct tree *rightRotate(struct tree *root, struct tree *node) {
    struct tree *oldDad = nullptr;
    struct tree *oldSon = nullptr; //right son
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
        node->parent = nullptr;
    }
    node->right = oldDad;
    oldDad->left = oldSon;
    oldDad->parent = node;
    if(oldSon != nullptr) {
        oldSon->parent = oldDad;
    }
    return root;
}

//assume node is not the root, has a dad
//node will go up
struct tree *leftRotate(struct tree *root, struct tree *node) {
    struct tree *oldDad = nullptr;
    struct tree *oldSon = nullptr; //left son
    oldDad = node->parent;
    oldSon = node->left;
    if(node->parent->parent != nullptr) { //uguale a dire node->parent == root
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
        node->parent = nullptr;
    }
    node->left = oldDad;
    oldDad->right = oldSon;
    oldDad->parent = node;
    if(oldSon != nullptr) {
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
    AVLupdateHeight(node->left);
    root = rightRotate(root, node);
    AVLupdateHeight(node->right);
    return root;
}

//assume node has grandfather
struct tree *doubleRotateRightLeft(struct tree *root, struct tree *node) {
    root = rightRotate(root, node);
    AVLupdateHeight(node->right);
    root = leftRotate(root, node);
    AVLupdateHeight(node->left);
    return root;
}

struct tree *BSTpredecessor(struct tree *node) {
    if(node->left != nullptr) {
        return BSTmax(node->left);
    } else {
        struct tree *y = node;
        while(y != nullptr && node != y->right) {
            node = y;
            y = node->parent;
        }
        return y;
    }
}

struct tree *BSTsuccessor(struct tree *node) {
    if(node->right != nullptr) {
        return BSTmin(node->right);
    } else {
        struct tree *y = node;
        while(y != nullptr && node != y->left) {
            node = y;
            y = node->parent;
        }
        return y;
    }
}

struct tree *BSTmin(struct tree *node) {
    if(node == nullptr) {
        return nullptr;
    } else {
        return goDeepOneDirection(node, true);
    }
}

struct tree *BSTmax(struct tree *node) {
    if(node == nullptr) {
        return nullptr;
    } else {
        return goDeepOneDirection(node, false);
    }
}

//error if node == nullptr
struct tree *goDeepOneDirection(struct tree *node, bool left) {
    struct tree *next = left ? node->left : node->right;
    if(next == nullptr) {
        return node;
    } else {
        return goDeepOneDirection(next, left);
    }
}

/*
void destroyTree(struct tree *&node) {
    if(node != nullptr) {
        //if not necessary, useful to reduce stack calls
        if(node->left != nullptr) { 
            destroyTree(node->left);
        }
        if(node->right != nullptr) {
            destroyTree(node->right);
        }
        //free(node->details);
        delete node;
    }
}
*/

struct tree* destroyTree(struct tree*& root) {
    if (root == nullptr) return nullptr;
    //Elimino la le foglie
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }
    else {
        //Elimino ricorsivamente i figli
        if (root->left != nullptr) root->left = destroyTree(root->left);
        if (root->right != nullptr) root->right = destroyTree(root->right);
        //Elimino la root
        return destroyTree(root);
    }
}

 struct tree* destroyTreeRasera(struct tree*& root, int &volte) {
    volte++;
    if(volte % 500000 == 0) cout << volte << endl;
    if (root == nullptr) return nullptr;
    //Elimino la le foglie
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }
    else {
        //Elimino ricorsivamente i figli
        if (root->left != nullptr) root->left = destroyTreeRasera(root->left, volte);
        if (root->right != nullptr) root->right = destroyTreeRasera(root->right, volte);
        //Elimino la root
        delete root;
        return nullptr;
    }
}

//-------------------------------------------------------------------------------------------
#pragma region AVL

//set node->height to 1 + max of height of his sons
//then do it to his father
//go up to the root, stops if node->height doesnt change
void AVLupdateHeight(struct tree *node) {
    if(node != nullptr) {
        AVLchangeHeight(node);
        AVLupdateHeight(node->parent);
    }
}

//set node->height to 1 + max of height of his sons
void AVLchangeHeight(struct tree *node) {
    if(node != nullptr) {
        node->height = 1 + max(h(node->left), h(node->right));
    }
} 

//insert node and balance tree
struct tree *AVLinsert(struct tree *&root, struct tree *node) {
    root = BSTinsert(root, node);
    AVLupdateHeight(node);
    //polishOrder(root);
    //printf("\n");
    //balance only if have dad and grandad, otherwise already balanced
    if(node->parent != nullptr && node->parent->parent != nullptr) {
        root = AVLbalanceIfNeeded(root, node->parent->parent);
    }
    return root;
}

//delete node and balance it
struct tree *AVLdelete(struct tree *root, struct tree *node) {
    struct tree *temp = nullptr;
    if(node->left == nullptr || node->right == nullptr) {
        if(node->left == nullptr && node->right == nullptr) {
            temp = node->parent;
        } else {
            temp = node->left == nullptr ? node->right : node->left;
        }
    } else {
        temp = BSTmin(node->right)->parent;
    }
    root = BSTdelete(root, node, true);
    AVLupdateHeight(temp);

    if(temp != nullptr) {
        root = AVLbalanceIfNeeded(root, temp);
    }
    return root;
}

struct tree *AVLbalanceIfNeeded(struct tree *root, struct tree *node) {
    if(node != nullptr) {
        int dif = hDiff(node);
        if(dif < -1) {
            root = AVLfixUp(root, node->right);
        } else if(dif > 1) {
            root = AVLfixUp(root, node->left);
        } else {
            root = AVLbalanceIfNeeded(root, node->parent);
        }
    }        
    return root;
}

//balance tree
struct tree *AVLfixUp(struct tree *root, struct tree *node) {
    if(node != nullptr) {
        struct tree *dad = node->parent;
        if(dad != nullptr) {
            struct tree *son = h(node->left) > h(node->right) ? node->left : node->right;
            int dadHDif = hDiff(dad);
            int nodeHDif = hDiff(node);
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
            AVLupdateHeight(son);
            AVLupdateHeight(dad);
            root = AVLbalanceIfNeeded(root, dad);
        }
    }
    return root;
}

#pragma endregion AVL

//-------------------------------------------------------------------------------------------
#pragma region RBT

//insert node and eventually balance tree
struct tree *RBTinsert(struct tree *&root, struct tree *node) {
    root = BSTinsert(root, node);
    node->color = node == root ? black : red;
    //polishOrder(root);
    //printf("\n");
    //balance only if have dad and grandad, otherwise already balanced
    if(node->parent != nullptr && node->parent->parent != nullptr && node->parent->color == red) {
        root = RBTfixUpOnInsert(root, node);
    }
    return root;
}

//assume max(T1) < x->key < min(T2)
struct tree *RBTjoinPublic(struct tree *T1, struct tree *T2, int key) {
    struct tree *x = create(key);
    if(RBTblackHeight(T1) <= RBTblackHeight(T2)) {
        return RBTjoinPrivate(T1, T2, x);
    } else {
        return RBTjoinPrivate(T2, T1, x);
    }
}

//assume blackHeight(T1) <= blackHeight(T2
//assume max(T1) < x->key < min(T2) || max(T2) < x->key < min(T1)
struct tree *RBTjoinPrivate(struct tree *T1, struct tree *T2, struct tree *x) {
    struct tree *node = T2;
    while(RBTblackHeight(T1) < RBTblackHeight(node) || node->color == 0) {
        //se chiavi t1 sono minori t2 ==> scendo sempre a sx
        //se chiavi t1 sono maggiori t1 ==> scendo sempre a dx
        node = T1->key < T2->key ? node->left : node->right;
    }
    struct tree *y = nullptr;
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
    T2 = RBTfixUpOnInsert(T2, x);
    return T2;
}

int RBTblackHeight(struct tree *node) {
    if(node == nullptr) return 0;
    else {
        int bh = node->left->color == black ? 1 : 0;
        return bh + RBTblackHeight(node->left);
    }
}

struct tree *RBTfixUpOnInsert(struct tree *root, struct tree *node) {
    if(node != nullptr && node->parent != nullptr && node->parent->color == red) {
        bool isLeftSon = isLeftSon(node);
        bool uncleIsOpp = true;
        struct tree *uncl = uncle(node, &uncleIsOpp);
        if((uncl == nullptr || uncl->color == black) && uncleIsOpp) {
            //caso fortunato: zio black opposto a x
            node->parent->color = black;
            node->parent->parent->color = red;
            root = isLeftSon ? rightRotate(root, node->parent) : leftRotate(root, node->parent);
        } else if(uncl == nullptr || uncl->color == black) {
            //caso quasi fortunato: zio black non opposto a x
            struct tree *dad = node->parent;
            root = isLeftSon ? rightRotate(root, node) : leftRotate(root, node);
            root = RBTfixUpOnInsert(root, dad);
        } else { 
            //caso sfortunato: zio red
            node->parent->color = uncl->color = black;
            node->parent->parent->color = red;
            root = RBTfixUpOnInsert(root, node->parent->parent);
        }
    } else if(node != nullptr && root == node) {
        node->color = black; //convenzione
    }
    return root;
}

struct tree *uncle(struct tree *node, bool *isOpposite) { 
    if(node != nullptr && node->parent != nullptr && node->parent->parent != nullptr) {
        if(isLeftSon(node->parent)) {
            *isOpposite = isLeftSon(node);
            return node->parent->parent->right;
        } else {
            *isOpposite = !isLeftSon(node);
            return node->parent->parent->left;
        }
    }
    return nullptr;
}

struct tree *RBTdelete(struct tree *root, struct tree *node) {
    struct tree *temp = nullptr;
    struct tree *tempSon = nullptr;
    struct tree *tempDad = nullptr;
    bool fixUp = true;
    if(node->left == nullptr || node->right == nullptr) {
        temp = node;
    } else {
        temp = BSTpredecessor(node);
    }
    bool tempLeft = isLeftSon(temp);
    tempDad = temp->parent;
    tempSon = temp->left == nullptr ? temp->right : temp->left;
    fixUp = (temp->color == black && (tempSon == nullptr || tempSon->color == black));
    if(!fixUp && tempSon != nullptr && tempSon->color == red) {
        tempSon->color = black;
    }
    root = BSTdelete(root, node, false);
    if(fixUp) {
        root = RBTfixUpOnDelete(root, tempSon, tempDad, tempLeft);
    }
    return root;
}

struct tree *RBTfixUpOnDelete(struct tree *root, struct tree *node, struct tree *dad, bool nodeLeft) { 
    struct tree *brother = nodeLeft ? dad->right : dad->left;
    if((node == nullptr || node->color == black) && brother != nullptr) {
        bool isOpposite = false;
        struct tree *nephew = RBToppositeRedSon(brother, &isOpposite);
        if(nephew != nullptr && nephew->color == red && isOpposite) {
            //caso fortunato: node ha nipote red e opposto
            nephew->color = black;
            brother->color = dad->color;
            dad->color = black;
            root = nodeLeft ? leftRotate(root, brother) : rightRotate(root, brother);
        } else if (nephew != nullptr && nephew->color == red) {
            //caso quasi fortunato: node ha nipote red non opposto
            nephew->color = black;
            brother->color = red;
            root = isLeftSon(nephew) ? rightRotate(root, nephew) : leftRotate(root, nephew);
        } else if (brother->color == black && (nephew == nullptr || nephew->color == black)) {
            //caso sfortunato: node ha nipoti e fratello black
            if(dad->color == red) {
                dad->color = black;
                brother->color = red;
            } else {
                root = RBTfixUpOnDelete(root, dad, dad->parent, isLeftSon(dad));
            }
        } else if(brother->color == red && (nephew == nullptr || nephew->color == black)) {
            brother->color = black;
            dad->color = red;
            root = nodeLeft ? leftRotate(root, brother) : rightRotate(root, brother);
            root = RBTfixUpOnDelete(root, node, dad, nodeLeft);
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
//else, nullptr se non ha nipoti
struct tree *RBToppositeRedSon(struct tree *node, bool *isOpposite) {
    if(node != nullptr) {
        if(*isOpposite = (!isLeftSon(node) && node->right != nullptr && node->right->color == red)) {
            return node->right;
        }
        if(*isOpposite = (isLeftSon(node) && node->left != nullptr && node->left->color == red)) {
            return node->left;
        }
        *isOpposite = false;
        if(node->right != nullptr && node->right->color == red) return node->right;
        if(node->left != nullptr && node->left->color == red) return node->left;
        return node->left != nullptr ? node->left : node->right;
    }
    return nullptr;
}

struct tree *brother(struct tree *node) {
    if(node == nullptr || node->parent == nullptr) {
        return nullptr;
    } else {
        return node == node->parent->left ? node->parent->right : node->parent->left;
    }
}

#pragma endregion RBT
//-------------------------------------------------------------------------------------------

void printTreeNice(struct tree *root, struct tree *node, int i, int level, int printed, bool left) {
    if(node != nullptr) {
        if(printed == 0) {
            for(int i = 0; i < h(root) - level - 1; i++) {
                printf("\t");
            }
        }
        struct tree *next = nullptr;
        struct tree *dad = nullptr;
        dad = next = node;
        //scendi
        while(i < level && next != nullptr) {
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
        if(next != root && dad != nullptr) {
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
    return node == nullptr ? nullptr : left ? node->left : node->right;
}


bool isBSTPrivate(struct tree *bt, int l, int r) {

    bool bst = true;
    if(bt != nullptr) {
        bst = (bt->key > l && bt->key < r);
        if(bst) {
            bst = isBSTPrivate(bt->left, l, bt->key);
        }
        if(bst) {
            bst = isBSTPrivate(bt->right, bt->key, r);
        }
    } 
    return bst;
}