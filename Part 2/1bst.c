/*
In questo esercizio si considereranno alberi binari di ricerca in cui ciascun nodo contiene
due informazioni: una chiave numerica (di tipo intero) e un valore alfanumerico (di tipo stringa).
I nodi di un albero binario di ricerca devono essere "ordinati" secondo le loro chiavi, ovvero
garantendo la proprietà seguente: se x è un nodo e y è un suo discendente nel sotto-albero di
sinistra (rispettivamente di destra), allora la chiave di x deve essere strettamente maggiore
(rispettivamente minore) di quella di y. In particolare, si assuma che i nodi in un albero
binario di ricerca abbiano chiavi distinte. 

Implementare una struttura dati che supporti le seguenti operazioni sugli alberi binari di ricerca:

- insert k v: inserisce un nuovo nodo nell'albero binario di ricerca, con chiave k di tipo
intero e valore v di tipo stringa (si assuma che l'albero non contenga già un nodo con chiave k)

- remove k: rimuove dall'albero il nodo che contiene la chiave numerica k (si assuma che
tale nodo esista sempre)

- find k: trova nell'albero il nodo con chiave numerica k e restituisce il valore
(di tipo stringa) associato a tale nodo (come sopra, si assuma che tale nodo esista)

- clear: rimuove tutti i nodi dall'albero, che diventerà quindi vuoto

- show: visualizza l'albero corrente

Il programma dovrà essere di tipo interattivo: a ogni iterazione, l'utente potrà indicare
una fra le operazioni sopra riportate (ad es., "insert 5 five", oppure "remove 5"), e in
output verrà fornito eventualmente il risultato dell'operazione (ad es., "five" nel caso
in cui l'operazione sia "find 5"). Il programma terminerà ogni qualvolta l'utente inserisca
un'operazione non supportata (ad es., "exit").

Per l'operazione "show", l'output prodotto dovrà essere una rappresentazione dell'albero
in forma polacca (notazione prefissa). Il contenuto di ogni nodo deve essere rappresentato
nel formato "chiave:valore" e un (sotto-)albero vuoto deve essere rappresentato dalla stringa "NULL".

Di seguito si riporta un esempio di esecuzione attesa dal programma (per convenienza, le
stringhe di input e output sono intercalate in modo da rispettare l'ordine di interazione):

input=insert 5 five
output=

input=show
output=5:five NULL NULL

input=insert 7 seven
output=

input=insert 2 two
output=

input=show
output=5:five 2:two NULL NULL 7:seven NULL NULL

input=find 2
output=two

input=exit
output=

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct tree{
    int val;
    char string[20];
    struct tree* left;
    struct tree* right;
};

typedef struct tree Tree;

void Insertion(Tree **node, int key, char *value);
Tree *newNode(int key, char *value);
void Remove(Tree **root, int toRemove);
Tree **MinNode(Tree **node);
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
            Insertion(&root, key, value);
        }else if(!strcmp(action, "remove")){
            int toRemove;
            scanf("%d", &toRemove);
            Remove(&root, toRemove);
        }else if(!strcmp(action, "show")){
            printPreOrder(root);
            putchar('\n');
        }else if(!strcmp(action, "find")){
            int toFind;
            scanf("%d", &toFind);
            Find(root, toFind);
        }else if(!strcmp(action, "clear")){
            root=NULL;
        }else{
            break;
        }
        
        scanf("%s", action);
    }
}

void Insertion(Tree **root, int key, char *value){
    if((*root)==NULL){
        (*root) = newNode(key, value);
    }else if(key<((*root)->val)){
        Insertion(&((*root)->left), key, value);
    }else{
        Insertion(&((*root)->right), key, value);
    }
}

Tree *newNode(int key, char *value){  
  Tree *node=(Tree *)malloc(sizeof(Tree));
  node->val=key;
  strcpy(node->string, value);
  node->left=NULL; 
  node->right=NULL;
  return node;
}

void Remove(Tree **root, int toRemove){
    if(((*root)->val)==toRemove){
        if(((*root)->left)!=NULL && ((*root)->right)!=NULL){ //2 children
            Tree **minNode = MinNode(&((*root)->right));
            (*root)->val = (*minNode)->val;
            strcpy((*root)->string, (*minNode)->string);
            Remove(&((*root)->right), (*root)->val);
        }else if(((*root)->left)!=NULL){ //only left child
            (*root)=(*root)->left;
        }else if(((*root)->right)!=NULL){ //only right child
            (*root)=(*root)->right;
        }else{//no children
            (*root)=NULL;
        }
    }else if(toRemove<((*root)->val)){
        Remove(&((*root)->left), toRemove);
    }else{
        Remove(&((*root)->right), toRemove);
    }
}

Tree **MinNode(Tree **node){
    if((*node)->left==NULL){
        return node;
    }else{
        MinNode(&((*node)->left));
    }
}

void printPreOrder(Tree *root){
    if(root!=NULL){
        printf("%d:%s ", root->val, root->string);
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