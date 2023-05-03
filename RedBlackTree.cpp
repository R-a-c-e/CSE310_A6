//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author:  Race Musgrave
// ASU ID:  1215151093
// Description:   all of the functions from RedBlackTree.h are defined here
//                all disctionary functions are implamented exception for deletion.
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//constructor
RedBlackTree::RedBlackTree(){
	root = NULL;
      //size = 0;
}

//Destructor
RedBlackTree::~RedBlackTree(){
	if(getRoot() == NULL){
            cout << "The number of nodes deleted: 0" << endl;
      }
      else{
            int nodeSize = deleteNode(getRoot());
	      cout << "The number of nodes deleted: " << nodeSize << " ";
      }
}

//returns the root of the RBT
Node* RedBlackTree::getRoot(){
      return root;
}


//this returns a key based on a given node
string RedBlackTree::getKey(Node* z){
      //cout << "    **Entered getKey1 in RBT.cpp\n";
      if(z == nullptr){
            return nullptr;
      }
      string key = to_string(z->vin);
      key += z->model;
      key += z->make;
      return key;
}


//this returns a key based on a given vin, model, and make
string RedBlackTree::getKey(int vin, string model, string make){
      //cout << "    **Entered getKey2 in RBT.cpp\n";
      string key = to_string(vin);
      key += model;
      key += make; 
      return key;
}


//a recursive function to delete a whole subtree beginning at a given node.
//returns the number of nodes that were deleted.
int RedBlackTree::deleteNode(Node* toDelete){
      int tot = 0;
      if(toDelete == NULL){
            return 0;
      }
      else{
            tot += deleteNode(toDelete->leftChild);         //recursive deletion on left child
            tot += deleteNode(toDelete->rightChild);        //recursive deletion on right child
            delete toDelete;
            tot++;
      }
      return tot;
}


//general BST insertion, does not take color into account,
//simply adds a node as a leef in the correct BST position
void RedBlackTree::insertNode(Node* z){         //z is the node being inserted 
      Node* x = getRoot();                      //x begins as the root node
      Node* y = NULL;                           //y is parent of z
      while(x != NULL){                         //loop to leaf and insert
            y = x;
            string zKey = getKey(z);
            string xKey = getKey(x);                                 
            if(zKey < xKey){
                  x = x->leftChild;
            }
            else{
                  x = x->rightChild;
            }
      }
      z->parent = y;
      if(y == NULL){
            root = z;                           //set z as root if its parent is NULL
      }
      else if(getKey(z) < getKey(y)){
            y->leftChild = z;
      }
      else{
            y->rightChild = z;
      }
}


//fixup keeps the correct color order of a Red Black tree
void RedBlackTree::fixUp(Node* x){
      Node* y = new Node;
      if(x->parent != nullptr){
            while(x->parent->color == "RED"){
                  if((x->parent->parent->leftChild != nullptr) && (x->parent->vin == x->parent->parent->leftChild->vin)){           //if x's parent is a left child
                        y = x->parent->parent->rightChild;                                //y is the uncle of x
                        if((y != nullptr) && (y->color == "RED")){                        //case 1; terminal
                              x->parent->color = "BLACK";
                              y->color = "BLACK";
                              x->parent->parent->color = "RED";
                              x = x->parent->parent;                                      //set x to be its grandparent
                        }
                        else {
                              if((x->parent->rightChild != nullptr) && (x->vin == x->parent->rightChild->vin)){         //case 2; if x is a right child of its parent
                                    x = x->parent;                                        //convert to case 3
                                    leftRotate(x);                                        //convert to case 3
                              }
                              x->parent->parent->color = "RED";                           //case 3; set grandparent color
                              x->parent->color = "BLACK";                                 //set parent color
                              rightRotate(x->parent->parent);
                        }
                  }
                  else{                                                                                                             //if x's parent is a right child
                        y = x->parent->parent->leftChild;                                 //y is the uncle of x
                        if((y != nullptr) && (y->color == "RED")){                        //case 1; terminal
                              x->parent->color = "BLACK";
                              y->color = "BLACK";
                              x->parent->parent->color = "RED";
                              x = x->parent->parent;                                      //set x to be its grandparent
                        }
                        else {
                              if((x->parent->leftChild != nullptr) && (x->vin == x->parent->leftChild->vin)){           //case 2; if x is a left child of its parent
                                    x = x->parent;                                        //convert to case 3
                                    rightRotate(x);                                       //convert to case 3
                              }
                              x->parent->parent->color = "RED";                           //case 3; set grandparent color
                              x->parent->color = "BLACK";                                 //set parent color
                              leftRotate(x->parent->parent);
                        }
                  }
                  if((x == nullptr) || (x->parent == nullptr)){
                        break;
                  }
            }
      }
      getRoot()->color = "BLACK";         //root must always remain black
}


//prints out the preorder traversal of a subtree
void RedBlackTree::preOrderTraversal(Node *z){
      if(getRoot() == NULL){
            cout << "\ntree is empty\n";
      }
      if(z != nullptr){
            print(z);
            preOrderTraversal(z->leftChild);
            preOrderTraversal(z->rightChild);
      }
}


//prints ot the inorder traversal of a subtree
void RedBlackTree::inOrderTraversal(Node *z){
      if(getRoot() == NULL){
            cout << "\ntree is empty\n";
      }
      if(z != nullptr){
            inOrderTraversal(z->leftChild);
            print(z);
            inOrderTraversal(z->rightChild);
      }
}


//prints out the postorder traversal of a substree
void RedBlackTree::postOrderTraversal(Node* z){
      if(getRoot() == NULL){
            cout << "\ntree is empty\n";
      }
      if(z != nullptr){
            postOrderTraversal(z->leftChild);
            postOrderTraversal(z->rightChild);
            print(z);
      }
}


//this finds the minimum node rooted at a given node
Node* RedBlackTree::findMinimumNode(Node* z){
      while(z->leftChild != nullptr){
            z = z->leftChild;
      }
      return z;
}


//this finds the maximum node rooted at a given node
Node* RedBlackTree::findMaximumNode(Node* z){
      while(z->rightChild != nullptr){
            z = z->rightChild;
      }
      return z;
}


//based on recieved information, it traverses the RBT looking for a matching
//key, if it finds it, it returns the match, if not, it returns NULL
Node* RedBlackTree::treeSearch(int vin, string model, string make){
      string zKey = getKey(vin,model,make);                             //zKey is the key of the given information
      Node* x = getRoot();                                              //x will be the node we are comparing to
      while((x != NULL) && (getKey(x).compare(zKey) != 0)){
            if(zKey > getKey(x)){
                  x = x->rightChild;
            }
            else{
                  x = x->leftChild;
            }
      }
      return x;                     //either returns the found node or a NULL dummy node;
}


//This function left-rotate the BST rooted at 'node'
void RedBlackTree::leftRotate(Node* x){
      if(x->rightChild != nullptr){             //precondition: x's right cant be null
            Node* y = x->rightChild;                        //y is x's right child
            x->rightChild = y->leftChild;                   
            if(y->leftChild != nullptr){                    
                  y->leftChild->parent = x;                 //x replaces y as parent of y's left
            }
            y->parent = x->parent;                          //x's parent is y's parent
            if(x->parent == nullptr){
                  root = y;
                  y->leftChild = x;
                  x->parent = y;
            }
            else if(x == x->parent->leftChild){             //if x is a left child
                  x->parent->leftChild = y;
                  x->parent = y;
                  y->leftChild = x;
            }
            else{                                           //if x is a right child
                  x->parent->rightChild = y;
                  y->leftChild = x;                         //put x on y's left
                  x->parent = y;
            }
      }
}


//This function right-rotate the BST rooted at 'node'
void RedBlackTree::rightRotate(Node* x){
      if(x->leftChild != nullptr){              //precondition: x's left cant be null
            Node* y = x->leftChild;                         //y is x's left child
            x->leftChild = y->rightChild;
            if(y->rightChild != nullptr){
                  y->rightChild->parent = x;                //x replaces y as parent of y's right
            }
            y->parent = x->parent;                          //x's parent is y's parent
            if(x->parent == nullptr){
                  root = y;
                  y->rightChild = x;
                  x->parent = y;
            }
            else if(x == x->parent->rightChild){            //if x is a right child
                  x->parent->rightChild = y;
                  x->parent = y;
                  y->rightChild = x;
            }
            else{                                           //if x is a left child
                  x->parent->leftChild = y;
                  y->rightChild = x;                        //put x on y's right
                  x->parent = y;
            }
      }
}


//This function finds the predecessor of the given 'node'
//also return a pointer that points to the successor node
Node* RedBlackTree::findPredecessorNode(Node* z){
      if(findMinimumNode(getRoot()) == z){            //if the node is the minimum, it wont have a predecessor
            return NULL;
      }
      if(z->leftChild != NULL){
            return findMaximumNode(z->leftChild);
      }
      Node* y = z->parent;
      while(z != NULL && z == y->leftChild){
            z = y;
            y = y->parent;
      }
      return y;
}


//This function finds the successor of the given 'node'
//also return a pointer that points to the successor node
Node* RedBlackTree::findSuccessorNode(Node* z){
      if(findMaximumNode(getRoot()) == z){            //if the node is a maximum, it wont have a successor
            return NULL;
      }
      if(z->leftChild != nullptr){
            return findMinimumNode(z->rightChild);
      }
      Node* y = z->parent;
      while(z != NULL && z == y->rightChild){
            z = y;
            y = y->parent;
      }
      return y;
}


//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.
void RedBlackTree::treeMin(){
      if(getRoot() != nullptr){
            print(findMinimumNode(getRoot()));
      }
      else{
            cout << "\ntree is empty\n";
      }
}


//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.
void RedBlackTree::treeMax(){
      if(getRoot() != nullptr){
            print(findMaximumNode(getRoot()));
      }
      else{
            cout << "\ntree is empty\n";
      }
}

//This function print out the pre-order traversal of the entire red-black tree
void RedBlackTree::treePreorder(){
      preOrderTraversal(getRoot());
}

//This function print out the in-order traversal of the entire red-black tree
void RedBlackTree::treeInorder(){
      inOrderTraversal(getRoot());
}

//This function print out the post-order traversal of the entire red-black tree
void RedBlackTree::treePostorder(){
      postOrderTraversal(getRoot());
}


//calls findPredecessor with the root of the RBT
void RedBlackTree::treePredecessor(int vin, string model, string make){
      findPredecessorNode(getRoot());
}


//calls findSuccessor with the root of the RBT
void RedBlackTree::treeSucessor(int vin, string model, string make){
      findSuccessorNode(getRoot());
}


//This function create a node from the given info., then insert
//the node inside the red-black tree.
void RedBlackTree::treeInsert(int vin, string model, string make, double price){
      //cout << "    **Entered treeInsert in RedBlackTree.cpp**\n";
      if(treeSearch(vin, model, make) == nullptr){                               //first check if the car already exists
            Node* x = new Node;           //x is the node to be inserted
            x->vin = vin;                 //set x vin
            x->model = model;             //set x model
            x->make = make;               //set x make
            x->price = price;             //set x price
            x->color = "RED"; 
            insertNode(x);                //general BST insertion

            fixUp(x);                     //fix up maintains the necessary RBT properties
      }
}



//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node){
      if(node == nullptr){
            cout << "this node is empty\n";
      }
      else{
            cout << left;
            cout << setw(8)  << node->vin
            << setw(12) << node->model
            << setw(12) << node->make
            << setw(10) << fixed << setprecision(2) << node->price;
            cout << right << setw(7) << node->color << endl;
      }
}