//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author:     Race Musgrave
// ASU ID:     1215151093
// Description:   this is the main program that reads input from keyboard,
//                it then execute various red-black tree operations which is 
//                given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;


//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string line, int& vin, string& model, string& make);

//This function used to get all info. of a Car
void getCarInfo(string line, int& vin, string& model, string& make, double& price);

int main()
{

   int vin;
   string model, make;
   double price;
   string command, oneLine, token;
   string delim = ",";

   int pos = 0;

   RedBlackTree* tree = new RedBlackTree();

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delim);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delim.length());

      if(command.compare("quit")==0){
         cout << "\nCommand: quit" << endl;
         tree->~RedBlackTree();                          //calls the destructor, should output the number of deleted cars
         break;
      }

      else if(command.compare("tree_preorder")==0){      //this command will view the RBT in Pre order
         cout << "\nCommand: tree_preorder" << endl;
         tree->treePreorder();
      }

      else if(command.compare("tree_inorder")==0){       //this command will view the RBT in In order
         cout << "\nCommand: tree_inorder" << endl;
         tree->treeInorder();
      }

      else if(command.compare("tree_postorder")==0){     //this command will view the RBT in Post order
         cout << "\nCommand: tree_postorder" << endl;
         tree->treePostorder();
      }

      else if(command.compare("tree_minimum")==0){       //This command finds the smallest node in the RBT
         cout << "\nCommand: tree_minimum" << endl;
         cout << "The MINIMUM is:\n";
         tree->treeMin();
      }

      else if(command.compare("tree_maximum")==0){       //This command finds the largest node in the RBT
         cout << "\nCommand: tree_maximum" << endl;
         cout << "The MAXIMUM is:\n";
         tree->treeMax();
      }

      else if(command.compare("tree_predecessor")==0){            //this finds the predecessor node from given information
         cout << "\nCommand: tree_predecessor" << endl;
         getCarKey(oneLine,vin,model,make);                       //vin, model, and make are given the correct info
         Node* y = tree->treeSearch(vin,model,make);              //find y in the RBT based on the given info
         if(y != NULL){
            cout << left;
            cout << setw(8)  << y->vin                            //if y is found, we get the following message
               << setw(12) << y->model
               << setw(13) << y->make
               << "is FOUND." << endl;
            Node* x = tree->findPredecessorNode(y);               //x is predecessor to y
            if(x != NULL){                                        //if predecessor is found
               cout << "Its Predecessor is: \n";
               tree->print(x);
            } 
            else{                                                 //if predecessor is NOT found
               cout << "Its Predecessor does NOT EXIST\n";
            }                                         
         }
      }

      else if(command.compare("tree_successor")==0){              //this finds the predecessor node from given information
         cout << "\nCommand: tree_successor" << endl;
         getCarKey(oneLine,vin,model,make);                       //vin, model, and make are given the correct info
         Node* y = tree->treeSearch(vin,model,make);              //find y in the RBT based on the given info
         if(y != NULL){
            cout << left;
            cout << setw(8)  << y->vin                            //if y is found, we get the following message
               << setw(12) << y->model
               << setw(13) << y->make
               << "is FOUND." << endl;
            Node* z = tree->findSuccessorNode(y);                 //z is successor to y
            if(z != NULL){                                        //if predecessor is found
               cout << "Its Successor is: \n";
               tree->print(z);
            } 
            else{                                                 //if predecessor is NOT found
               cout << "Its Successor does NOT EXIST\n";
            }                                         
         }
      }

      else if(command.compare("tree_search")==0){
         cout << "\nCommand: tree_search" << endl;
         getCarKey(oneLine,vin,model,make);
         Node* y = tree->treeSearch(vin,model,make);              //y is the car being searched for in the RBT
         if(y != NULL){
            cout << left;
            cout << setw(8)  << y->vin                            //if the car is found, we get this output message
               << setw(12) << y->model
               << setw(13) << y->make
               << setw(12) << "is FOUND." << endl;   
         }
         else{
            cout << left;                                         //if the car is NOT found, we get this output
            cout << setw(8)  << vin
               << setw(12) << model
               << setw(13) << make
               << setw(12) << "is NOT FOUND." << endl;
         }
      }

      else if(command.compare("tree_insert")==0){                 //for inserting a new car into the RBT
         if(tree->getRoot() == nullptr){
            cout << "Command: tree_insert" << endl;               //for the first inserted node
         }
         else{
            cout << "\nCommand: tree_insert" << endl;             //for all other insertions
         }
         getCarInfo(oneLine, vin, model, make, price);            //set the info in vin, model, make, and price
         cout << left;
         cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << price << endl;
         tree->treeInsert(vin, model, make, price);               //insertion!
         }

   } while(true);  //continue until 'quit'
   return 0;
}


//This function from one line, extracts the vin, model, make of a Car
void getCarKey(string line, int& vin, string& model, string& make){
   string delim = ",";
   int idx = line.find(delim);
   vin = stoi(line.substr(0,idx));                    //vin now contains the first value in line
   line.erase(0, idx+delim.length());

   idx = line.find(delim);
   model = line.substr(0,idx);                        //model now contains the second value in line
   line.erase(0, idx+delim.length());

   make = line;                                       //make is what is left in line
}


//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string line, int& vin, string& model, string& make, double& price){

   string delim = ",";
   int idx = line.find(delim);
   vin = stoi(line.substr(0,idx));                 //vin now contains the first value in line
   line.erase(0, idx+delim.length());

   idx = line.find(delim);
   model = line.substr(0,idx);                     //model now contains the second value in line
   line.erase(0, idx+delim.length());

   idx = line.find(delim); 
   make = line.substr(0,idx);                      //make now contains the second value in line
   line.erase(0, idx+delim.length());

   price = stod(line);
}