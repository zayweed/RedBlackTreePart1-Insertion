/*
Zayeed Saffat
6/14/2022
This project makes a red-black tree that sorts numbers in a balanced binary search tree. Each node is either red or black and has two children. The program allows you to add numbers from file or user input aswell as display the tree to the terminal.
Credits to Ruby Amyeen for helping me with the check function with the 'leftRotate' and 'rightRotate' methods.
*/
#include <iostream>
#include <fstream>
#include <cstring>

#include "node.h"

using namespace std;

//function prototypes
void add(Node*& root, Node* current, int value);
void check(Node* current);
void leftRotate(Node* root, Node* a);
void rightRotate(Node* root, Node* a);
void display(Node* current, int depth);
bool search(Node* root, int value);

int main() {
    Node* root = NULL;  

    bool stillPlaying = true;
    while (stillPlaying == true) {
        cout << "Would you like to add by file(FILE), add by input(INPUT), display the tree(DISPLAY), remove a node(REMOVE), search for a node(SEARCH), or quit(QUIT)?" << endl;
        char input[100];
        cin >> input;

        if (strcmp(input, "FILE") == 0) { //add by file
            cout << "Enter how many integers you would like to add:" << endl;
            int n; cin >> n;
            fstream fin;
            fin.open("numbers.txt"); //open file

            int value;
            for (int i = 0; i < n; i++) { //iterates through the first n integers in the file
                fin >> value;
                
                add(root, root, value);
                while (root->getParent() != NULL) { //reset root
                    root = root->getParent();
                }
            }

            fin.close(); //close file
        }

        if (strcmp(input, "INPUT") == 0) { //add by input
            cout << "Enter how many you integers would like to add:" << endl;
            int n; cin >> n;

            cout << "Enter the integers:" << endl;
            int value;
            for (int i = 0; i < n; i++) {
                cin >> value;
            
                add(root, root, value);
                while (root->getParent() != NULL) { //reset root
                    root = root->getParent();
                }
            }
        }

        if (strcmp(input, "DISPLAY") == 0) { //display tree
            display(root, 0);
        }

        if (strcmp(input, "SEARCH") == 0) { //search for an integer
            cout << "Enter an integer to search for:" << endl;
            int value; cin >> value; 
            
            if (search(root, value) == true) { //value found in tree
                cout << "Integer is in the tree!" << endl;
            }           
            else { //value not found in tree
                cout << "Integer is not in the tree!" << endl;
            }
        }

        if (strcmp(input, "REMOVE") == 0) { //delete an integer from tree
            cout << "Enter an integer to REMOVE:" << endl;
            int value; cin >> value;

            //
        }

        if (strcmp(input, "QUIT") == 0) { //quit
            stillPlaying = false;
        }
    }
}

void add(Node*& root, Node* current, int value) { //function that adds integer to tree
    if (root == NULL) { //if tree is empty and root is NULL
        root = new Node(value);
        check(root); //checks for violations and updates tree
    }

    else if (value < current->getValue()) { //if value is less than current
        if (current->getLeft() == NULL) { //add value to tree
            current->setLeft(new Node(value));
            current->getLeft()->setParent(current);
            check(current->getLeft()); //checks for violations and updates tree
        }
        else { //go left
            add(root, current->getLeft(), value);
        }
    }

    else if (value > current->getValue()) { //if value is greater than current
        if (current->getRight() == NULL) { //add value to tree
            current->setRight(new Node(value));
            current->getRight()->setParent(current);
            check(current->getRight()); //checks for violations and updates tree
        }
        else { //go right
            current->getRight();
            add(root, current->getRight(), value);
        }
    }
}

void check(Node* current) {
    //cout << "CURRENT: " << current->getValue() << ": ";
    Node* parent = NULL; Node* grandparent = NULL; Node* uncle = NULL;
    if (current->getParent() != NULL) { //set initial values for parent, grandparent, and uncle
        parent = current->getParent();
        if (parent->getParent() != NULL) {
            grandparent = parent->getParent();   
            if (grandparent->getLeft() == parent) {
                uncle = grandparent->getRight();
            }
            else {
                uncle = grandparent->getLeft();
            }
        } 
    }

    if (current->getParent() == NULL) { //added to the root
        current->setBlack(); //root must be black
    } 

    else if (current->getParent()->getColor() == 0) { //parent is black
        //nothing happens
    } 

    else if (uncle != NULL && uncle->getColor() == 1) { //both parent and uncle are red
        
        current->getParent()->setBlack(); //parent and uncle turned black
        grandparent->setRed(); //grandparent turned red
        uncle->setBlack();
        check(grandparent); //recursive call
    } 

    else { //parent is red but uncle isn't or doesn't exist
        if (current == parent->getRight() && parent == grandparent->getLeft()) { //current is larger than parent
            leftRotate(current, parent);
            current = current->getLeft();
        } 
        else if (current == parent->getLeft() && parent == grandparent->getRight()) { //current is smaller than parent
            rightRotate(current, parent);
            current = current->getRight();
        }
        parent = current->getParent(); 
        grandparent = parent->getParent();
        if (current == parent->getLeft()) { //current is smaller than parent
            rightRotate(current, grandparent);
        } 
        else { //current is larger than parent
            leftRotate(current, grandparent);
        }
        parent->setBlack();
        grandparent->setRed();
    }
}

void leftRotate(Node* root, Node* a) { //function for left rotate
    Node* b = a->getRight(); 
    a->setRight(b->getLeft()); 
    if (b->getLeft() != NULL) {
        b->getLeft()->setParent(a);
    }
    b->setParent(a->getParent());

    if (a->getParent() == NULL) {
        root = b;
    } 
    else if (a == a->getParent()->getLeft()) {
        a->getParent()->setLeft(b);
    } 
    else {
        a->getParent()->setRight(b);
    }
    b->setLeft(a);
    a->setParent(b);
}

void rightRotate(Node* root, Node* a) { //function for right rotate
    Node* b = a->getLeft();
    a->setLeft(b->getRight());
    if (b->getRight() != NULL) {
        b->getRight()->setParent(a);
    }
    b->setParent(a->getParent());

    if (a->getParent() == NULL) {
        root = b;
    } 
    else if (a == a->getParent()->getLeft()) {
        a->getParent()->setLeft(b);
    } 
    else {
        a->getParent()->setRight(b);
    }
    b->setRight(a); 
    a->setParent(b);
}

void display(Node* current, int depth) { //function that displays tree
    if (current == NULL) { //if tree is empty and head is NULL exit function
        return;
    }

    if (current->getRight() != NULL) { //go right
        display(current->getRight(), depth+1); //recursive call
    }

    for (int i = 0; i < depth; i++) { //print tabs based on depth
        cout << "\t";
    }

    if (current->getColor() == 0) { //black node
        //cout << "B" << current->getValue() << endl;
        cout << "B" << current->getValue() << "|";
    }
    else if (current->getColor() == 1) { //red node
        //cout << "R" << current->getValue() << endl;
        cout << "R" << current->getValue() << "|";
    }

    if (current->getParent() == NULL) {
        cout << "NULL" << endl;
    }
    else {
        cout << current->getParent()->getValue() << endl;
    }

    if (current->getLeft() != NULL) { //go left
        display(current->getLeft(), depth+1); //recursive call
    }
}

bool search(Node* root, int value) { //function that searches for a value in the tree
    Node* current = root;
    while (current != NULL) {
        if (value < current->getValue()) { //if value is less than current go left
            current = current->getLeft();
        }
        else if (value > current->getValue()) { //if value is greater than current go right
            current = current->getRight();
        }
        else if (value == current->getValue()) { //value is found and true is returned
            return true;
        }
    }
    return false; //if NULL node is reached without finding the value then we know it doesn't exist in the tree
}
