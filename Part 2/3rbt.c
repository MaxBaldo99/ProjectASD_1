/*

Si richiede l'implementazione di un albero binario di ricerca di tipo Red-Black ("rosso-neri"),
in cui ciascun nodo contiene una chiave numerica (di tipo intero) e un valore alfanumerico
(di tipo stringa). 

Come nei precedenti esercizi, il programma che implementa le operazioni di un albero di ricerca
di tipo Red-Black dovrà essere di tipo interattivo: a ogni iterazione, l'utente potrà indicare
un'operazione (ad esempio, insert 5 five, find 5, clear, show) e in output verrà fornito eventualmente
il risultato dell'operazione. In particolare, l'operazione show produce come risultato la
rappresentazione in notazione polacca dell'albero, in cui ogni nodo è rappresentato da una stringa
che ne descrive la chiave, il valore, e il colore (ad esempio, "5:five:red", oppure "3:three:black").
Il programma terminerà ogni qualvolta l'utente inserisca un'operazione non supportata (ad esempio, "exit").

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int data;
    char color;
    char string[20];
    struct node *left, *right, *parent;
};

void insertion(struct node **root, int data, char *value);
struct node *insert(struct node *root, struct node *z);
struct node *newNode(int data, char *value);
void insertFixUp(struct node **root,struct node *z);
void leftRotate(struct node **root,struct node *x);
void rightRotate(struct node **root,struct node *y);
void printPreOrder(struct node *root);
void printColor(struct node *node);
void find(struct node *node, int toFind);

int main(){
    char action[8];
    scanf("%s", action);

	struct node *root=NULL;
    while(strcmp(action, "exit")){
        if(!strcmp(action, "insert")){
            int key;
            scanf("%d", &key);
            char value[20];
            scanf("%s", value);
            insertion(&root, key, value);
        }else if(!strcmp(action, "show")){
            printPreOrder(root);
            putchar('\n');
        }else if(!strcmp(action, "find")){
            int toFind;
            scanf("%d", &toFind);
            find(root, toFind);
        }else if(!strcmp(action, "clear")){
            root=NULL;
        }else{
            break;
        }
        
        scanf("%s", action);
    }
}

void insertion(struct node **root, int data, char *value)
{
    //create a new node
    struct node *z = newNode(data, value);

    //make the insertion of the new node
    (*root) = insert(*root, z);

    // call insertFixUp to fix reb-black tree's property if it
    // is violated due to insertion.
    insertFixUp(root, z);
}


// Utility function to insert newly node in RedBlack tree
struct node *insert(struct node *root, struct node *z)
{
    if(root == NULL)
    {
        root = z;
    }
    else if((z->data)<(root->data))
    {
        root->left = insert(root->left, z);
        root->left->parent = root; 
    }
    else
    {
        root->right = insert(root->right, z);
        root->right->parent = root; 
    }

    return root;
}

struct node *newNode(int data, char *value)
{
    struct node *node=(struct node *)malloc(sizeof(struct node));
    node->data=data;
    node->color = 'R';
    strcpy(node->string, value);
    node->left=NULL; 
    node->right=NULL;
    node->parent=NULL;
    return node;
}

// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct node **root, struct node *z)
{

    // iterate until z is not the root and z's parent color is red
    while ((z != *root) && (z->color == 'R') && (z->parent->color == 'R'))
    {
        struct node *y;

        // Find uncle and store uncle in y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if(y != NULL && (y->color == 'R'))
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }

        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            
            // Left-Left (LL) case, do following
            // (i)  Right Rotate Grandparent
            // (ii) Swap color of parent and grandparent
            
            if (z->parent == z->parent->parent->left)
            {

                // Left-Right (LR) case, do following
                // (i) Left Rotate Parent
                if (z == z->parent->right)
                {
                    leftRotate(root,z->parent);
                    z = z->left;
                }

                printf("%i %i %i\n", z->data, z->parent->data, z->parent->parent->data);
                rightRotate(root,z->parent->parent);

                char ch = z->parent->color ;
                z->parent->color = z->parent->right->color;
                z->parent->right->color = ch;

            }

            // Right-Right (RR) case, do following
            // (i)  Left Rotate Grandparent
            // (ii) Swap color of parent and grandparent
            else
            {
                
                // Right-Left (RL) case, do following
                // (i) Right Rotate Parent
                if (z == z->parent->left)
                {
                    rightRotate(root,z->parent);
                    z = z->right;
                }

                leftRotate(root,z->parent->parent);
                
                char ch = z->parent->color ;
                z->parent->color = z->parent->left->color;
                z->parent->left->color = ch;
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}

// Left Rotation
void leftRotate(struct node **root,struct node *x)
{
    if (!x || !x->right)
        return ;
    //y stored pointer of right child of x
    struct node *y = x->right;

    //store y's left subtree's pointer as x's right child
    x->right = y->left;

    //update parent pointer of x's right
    if (x->right != NULL)
        x->right->parent = x;

    //update y's parent pointer
    y->parent = x->parent;

    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;

    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    
        x->parent->right = y;

    // make x as left child of y
    y->left = x;

    //update parent pointer of x
    x->parent = y;
}


// Right Rotation (Similar to LeftRotate)
void rightRotate(struct node **root,struct node *y)
{
    if (!y || !y->left)
        return ;

    struct node *x = y->left;
    y->left = x->right;

    if (y->left != NULL)
        y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else 
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void printPreOrder(struct node *root){
    if(root!=NULL){
        printf("%d:%s:", root->data, root->string);
        printColor(root);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }else{
        printf("NULL ");    
    }
}

void printColor(struct node *node){
    if(node->color == 'R'){
        printf("red ");
    }else{
        printf("black ");
    }
}

void find(struct node *node, int toFind){
    if((node->data)==toFind){
        printf("%s\n", node->string);
    }else if(toFind<(node->data)){
        find(node->left, toFind);
    }else{
        find(node->right, toFind);
    }
}