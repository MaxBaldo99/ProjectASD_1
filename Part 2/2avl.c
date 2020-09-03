
/*

Si richiede l'implementazione di un albero binario di ricerca di tipo AVL, in cui ciascun nodo contiene
una chiave numerica (di tipo intero) e un valore alfanumerico (di tipo stringa). Un albero binario di ricerca
di tipo AVL supporta le classiche operazioni di inserimento, ricerca, e rimozione di nodi, garantendo allo
stesso tempo la proprietà di quasi bilanciamento: per ogni nodo x, le altezze dei sotto-alberi di sinistra
e di destra nel nodo x differiscono al più di 1. Tale proprietà viene garantita eseguendo opportune rotazioni
sui nodi sbilanciati, partendo dal nodo sbilanciato più profondo (ad esempio, il "nonno" del nodo appena
inserito) e procedendo risalendo l'albero lungo il cammino di accesso a quel nodo. Per le operazioni di
ribilanciamento sarà necessario mantenere l'informazione relativa all'altezza di ciascun nodo, in modo da
evitare il calcolo diretto di essa (tale calcolo prenderebbe tempo lineare nella dimensione del sotto-albero).

Più precisamente, il ribilanciamento di un nodo x avviene nell'ipotesi che le altezze dei figli di x siano
note e differiscano esattamente di 2 unità, e che entrambi i sotto-alberi radicati nei figli di x
soddisfino la proprietà di quasi bilanciamento. L'effetto dell'operazione di ribilanciamento su x sarà che
l'intero sotto-albero radicato in x soddisfa la proprietà di quasi bilanciamento. L'operazione di
ribilanciamento su x effettua una distinzione di casi, a seconda di quale figlio di x abbia il
sotto-albero più alto. Si consideri il caso in cui il sotto-albero del figlio sinistro di x abbia altezza
maggiore di quello del figlio destro (il caso simmetrico può essere trattato in modo del tutto analogo).
Sia y il figlio sinistro di x e siano z1 e z2 i figli sinistro e destro di y (quindi due "nipoti" di x).
Se il sotto-albero radicato in z1 ha altezza maggiore o uguale a quella del sotto-albero radicato in z2,
allora basterà effettuare una rotazione verso destra sul nodo x. Altrimenti, se il sotto-albero radicato
in z1 ha altezza minore di quella del sotto-albero radicato in z1, allora, prima di effettuare una
rotazione verso destra sul nodo x, sarà opportuno effettuare una rotazione verso sinistra sul nodo y,
in modo da riportarsi al caso analizzato precedentemente.

A seguito delle operazioni di ribilanciamento, un albero di ricerca di tipo AVL mantiene un'altezza
proporzionale al logaritmo del numero dei suoi nodi. In particolare, tutte le operazioni supportate
da un albero di ricerca di tipo AVL avranno complessità logaritmica rispetto al numero di nodi.



Come nel precedente esercizio 17, il programma che implementa le operazioni di un albero di ricerca di
tipo AVL dovrà essere di tipo interattivo: a ogni iterazione, l'utente potrà indicare un'operazione
(ad esempio, insert 5 five, remove 5, find 5, clear, show) e in output verrà fornito eventualmente il
risultato dell'operazione. In particolare, l'operazione show produce come risultato la rappresentazione
in notazione polacca dell'albero, in cui ogni nodo è rappresentato da una stringa che ne descrive la chiave,
il valore, e l'altezza dell'albero in esso radicato (ad esempio, "5:five:15"). Il programma terminerà ogni
qualvolta l'utente inserisca un'operazione non supportata (ad esempio, "exit").

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct tree{
    int val;
    char string[20];
    int height;
    struct tree* left;
    struct tree* right;
};

typedef struct tree Tree;

void Insert(Tree **node, int key, char *value);
Tree *newNode(int key, char *value);
void ReHeight(Tree **node);
int Max(int first, int second);
int Height(Tree *node);
Tree *Avl(Tree *root, int key);
int GetBalance(Tree *node);
Tree *RightRotate(Tree *node);
Tree *LeftRotate(Tree *node);
Tree *Remove(Tree *root, int toRemove);
Tree *MinNode(Tree *node);
Tree *AvlDelete(Tree *root);
void printPreOrder(Tree *root);
void Find(Tree *root, int key);

int main(){
    char action[8];
    scanf("%s", action);

	Tree *root=NULL;
    while(strcmp(action, "exit")){
        if(!strcmp(action, "insert")){
            int key;
            scanf("%d", &key);
            char value[20];
            scanf("%s", value);
            Insert(&root, key, value);
        }else if(!strcmp(action, "remove")){
            int toRemove;
            scanf("%d", &toRemove);
            root = Remove(root, toRemove);
        }else if(!strcmp(action, "show")){
            printPreOrder(root);
            putchar('\n');
        }else if(!strcmp(action, "find")){
            int toFind;
            scanf("%d", &toFind);
            Find(root, toFind);
        }else if(!strcmp(action, "height")){
            printf("%d\n", Height(root));
        }else if(!strcmp(action, "clear")){
            root=NULL;
        }else{
            break;
        }
        
        scanf("%s", action);
    }
}

void Insert(Tree **root, int key, char *value){
    if((*root)==NULL){
        (*root) = newNode(key, value);
    }else if(key<((*root)->val)){
        Insert(&((*root)->left), key, value);
    }else{
        Insert(&((*root)->right), key, value);
    }

    ReHeight(root);
    
    (*root) = Avl((*root), key);
}

Tree *newNode(int key, char *value){
    Tree *node=(Tree *)malloc(sizeof(Tree));
    node->val=key;
    strcpy(node->string, value);
    node->left=NULL; 
    node->right=NULL;
    node->height=1;
    return node;
}

void ReHeight(Tree **node){
    (*node)->height = 1 + Max(Height((*node)->left), Height((*node)->right));
}

int Max(int first, int second){
    if(first>second){
        return first;
    }else{
        return second;
    }
}

int Height(Tree *node){ 
    if(node == NULL){
        return 0; 
    }else{
        return node->height; 
    }  
    
}

Tree *Avl(Tree *root, int key){

    int difference = GetBalance(root);

    if(difference>1 && key<root->left->val){ //LL
        return RightRotate(root); 
    }

    if(difference>1 && key>root->left->val){ //LR 
        root->left = LeftRotate(root->left); 
        return RightRotate(root); 
    }
    
    if(difference<-1 && key>root->right->val){ //RR
        return LeftRotate(root); 
    }

    if(difference<-1 && key<root->right->val){  //RL 
        root->right = RightRotate(root->right); 
        return LeftRotate(root);
    } 

    return root; 
}

int GetBalance(Tree *node){ 
    if(node==NULL){
        return 0; 
    }else{
        return Height(node->left) - Height(node->right); 
    }
}

Tree *RightRotate(Tree *node){ 
    Tree *node2 = node->left; 
    Tree *node3 = node2->right;
  
    node2->right = node;
    node->left = node3; 
  
    ReHeight(&node);
    ReHeight(&node2);

    return node2;
}

Tree *LeftRotate(Tree *node){ 
    Tree *node2 = node->right; 
    Tree *node3 = node2->left;
  
    node2->left = node; 
    node->right = node3; 
  
    ReHeight(&node);
    ReHeight(&node2);

    return node2;
}

Tree *Remove(Tree *root, int toRemove){

    if (root == NULL){
        return root; 
    }
    
    
    if (toRemove < root->val){
        root->left = Remove(root->left, toRemove); 
    }else if(toRemove > root->val){
        root->right = Remove(root->right, toRemove); 
    }else{ 
        Tree *temp;
        
        if( (root->left == NULL) || (root->right == NULL) ) 
        {

            temp = root->left ? root->left : root->right; 

            if(temp == NULL){ 
                temp=root; 
                root=NULL; 
            }else{
             *root = *temp;
            }

            free(temp); 
        } 
        else
        { 
            temp = MinNode(root->right); 
  
            root->val = temp->val;
            strcpy(root->string, temp->string);
  
            root->right = Remove(root->right, temp->val); 
        } 
    } 
  
    if(root == NULL){
        return root;
    }

    ReHeight(&root);
    return AvlDelete(root);
}

Tree *MinNode(Tree *node){
    if(node->left==NULL){
        return node;
    }else{
        MinNode(node->left);
    }
}

Tree *AvlDelete(Tree *root){

    int difference = GetBalance(root); 

	if(difference>1 && GetBalance(root->left)>=0){
		return RightRotate(root); 
    }
	
	if(difference>1 && GetBalance(root->left)<0){ 
		root->left = LeftRotate(root->left); 
		return RightRotate(root); 
	} 

	if(difference<-1 && GetBalance(root->right)<=0){
		return LeftRotate(root);
    }

	if(difference<-1 && GetBalance(root->right)>0){ 
		root->right = RightRotate(root->right); 
		return LeftRotate(root); 
	} 

	return root;
}

void printPreOrder(Tree *root){
    if(root!=NULL){
        printf("%d:%s:%d ", root->val, root->string, root->height);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }else{
        printf("NULL ");    
    }
}

void Find(Tree *root, int key){
    if((root->val)==key){
        printf("%s\n", root->string);
    }else if(key<(root->val)){
        Find(root->left, key);
    }else{
        Find(root->right, key);
    }
}