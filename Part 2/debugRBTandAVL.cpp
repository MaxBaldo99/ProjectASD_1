#include "headers/tree.h"
#include "headers/tree.cpp"

#define BST 0
#define RBT 1
#define AVL 2

int main() { 
    
    /*
    Esercizio 16 - alberi binari di ricerca
    input (continuo):
        avl         switch to avl
        rbt         switch to rbt
        insert k    insert key
        remove k    remove key
        find k      find fey
        clear       destroy tree
        show        polish order
    */
    
    bool getInput = true;
    string command = "";
    struct tree *myTree = NULL;
    int type = BST;
    printf("mode: BST\n");

    while(getInput) {

        cin >> command;
        int key = 0;
        struct tree *temp = NULL;
        
        if(command.compare("avl") == 0) {
            if(type != AVL) {
                type = AVL;
                myTree = destroyTree(myTree);
                printf("\nmode: AVL\n");
            } else {
                printf("mode already AVL\n");
            }
        } else if(command.compare("rbt") == 0) {
            if(type != RBT) {
                type = RBT;
                myTree = destroyTree(myTree);
                printf("\nmode: RBT\n");
            } else {
                printf("mode already RBT\n");
            }
        } else if(command.compare("bst") == 0) {
            if(type != BST) {
                type = BST;
                myTree = destroyTree(myTree);
                printf("\nmode: BST\n");
            } else {
                printf("mode already BST\n");
            }
        } else if(command.compare("insert") == 0) {
            cin >> key;
            temp = create(key);
            if(type == BST) {
                BSTinsert(myTree, temp);
            } else if(type == RBT) {
                myTree = RBTinsert(myTree, temp);
            } else {
                myTree = AVLinsert(myTree, temp);
            }
            
        } else if (command.compare("remove") == 0) {
            cin >> key;
            temp = BSTfind(myTree, key);
            if(type == BST) {
                myTree = BSTdelete(myTree, temp, true);
            } else if (type == RBT) {
                myTree = RBTdelete(myTree, temp);
            } else {
                myTree = AVLdelete(myTree, temp);
            }
        } else if (command.compare("find") == 0) {
            cin >> key;
            temp = BSTfind(myTree, key);
            print(temp);
            printf("\n");

        } else if(command.compare("clear") == 0) {
            myTree = destroyTree(myTree);

        } else if(command.compare("show") == 0) {
            polishOrder(myTree);
            printf("\n");

        } else if(command.compare("exit") == 0) {
            getInput = false;

        } else {
            //getInput = false;
            printf("Command not found\n");
            printf("Type 'exit' lo close terminal\n");

        }
        //polishOrder(myTree);
        polishOrderNice(myTree, 0);
        printf("\n");
    }
    destroyTree(myTree);

    return 0;
}