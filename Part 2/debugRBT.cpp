#include "headers/tree.h"
#include "headers/tree.cpp"

int main() { 
    
    /*
    Esercizio 16 - alberi binari di ricerca
    input (continuo):
        insert k
        remove k
        find k
        clear
        show
    */
    
    bool getInput = true;
    string command = "";
    struct tree *myTree = NULL;

    while(getInput) {

        cin >> command;
        int key = 0;
        struct tree *temp = NULL;
        
        if(command.compare("insert") == 0) {
            cin >> key;
            myTree = RBTinsert(myTree, create(key));
            
        } else if (command.compare("remove") == 0) {
            cin >> key;
            temp = BSTfind(myTree, key);
            myTree = RBTdelete(myTree, temp);

        } else if (command.compare("find") == 0) {
            cin >> key;
            temp = BSTfind(myTree, key);
            print(temp);
            printf("\n");

        } else if(command.compare("clear") == 0) {
            destroyTree(myTree);

        } else if(command.compare("show") == 0) {
            polishOrder(myTree);
            printf("\n");

        } else if(command.compare("exit") == 0) {
            getInput = false;

        } else {
            //getInput = false;
            //printf("Command not found");

        }
        polishOrder(myTree);
        printf("\n");
    }
    destroyTree(myTree);

    return 0;
}