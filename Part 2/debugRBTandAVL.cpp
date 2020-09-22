#include "headers/tree.h"
#include "headers/tree.cpp"

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
    bool RBT = true;
    printf("mode: RBT\n");

    while(getInput) {

        cin >> command;
        int key = 0;
        struct tree *temp = NULL;
        
        if(command.compare("avl") == 0) {
            if(RBT) {
                myTree = destroyTree(myTree);
                printf("\nmode: AVL\n");
            }
            RBT = false;
        } else if(command.compare("rbt") == 0) {
            if(!RBT) {
                myTree = destroyTree(myTree);
                printf("\nmode: RBT\n");
            }
            RBT = true;
        } else if(command.compare("insert") == 0) {
            cin >> key;
            temp = create(key);
            if(RBT) {
                myTree = RBTinsert(myTree, temp);
            } else {
                myTree = AVLinsert(myTree, temp);
            }
            
        } else if (command.compare("remove") == 0) {
            cin >> key;
            temp = BSTfind(myTree, key);
            if(RBT) {
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
            //printf("Command not found");

        }
        //polishOrder(myTree);
        polishOrderNice(myTree, 0);
        printf("\n");
    }
    destroyTree(myTree);

    return 0;
}