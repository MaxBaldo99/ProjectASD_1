# ProjectASD
This is the project of Algorithm and Data Structure of UniUd

## Part one
Selection algorithms
Implement and compare these three algorithms:
* Quick Select
* Median of Medians Select
* Heap Select

### ToDo:
- [x] Calculate the resolution of your device
- [x] Write the code of the three algorithms 
- [x] Execute them
- [x] Prove their theorical complexity:
    - [x] take time needed for the execution of each algorithm, with different array dimensions
    - [x] re-execute it if 1% relative error is not respected
    - [x] save and store all data about execution time spent and its standard deviation
    - [x] plot data found
    - [x] compare sperimental and asyntotic data
- [ ] Write the final relation with graphs of data found

[Link for relation](https://drive.google.com/open?id=1RBXC6th5qzl4aEK_ah5653H4VoKP_PkQs3e1rcd3mQo)

## Part two
Binary Search Trees (BST)
Implement and compare these three tyes of BST:
* Generic BST (non balanced)
* Red-Black Tree (RBT)
* Adelson-Velskij e Landis (AVL)

### ToDo:

Same as on top, but execution has the scheme:
- [ ] generate empty BST
- [ ] generate randomly n numbers [n1, ..., nn]
- [ ] find ni in BST, if not found then insert it in BST  

At the end of computation will be done:
* number of finds: n
* number of insert: m
* m <= n
* m == n if all generated numbers are different each other (no repetitions)
* so m tends to n if gets harder to generate same 2 times, which means:
  * random numbers possible range increases
  * array size decreases
