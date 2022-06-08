/*

*/
#include <iostream>
#include <fstream>
#include <cstring>

#include "node.h"

using namespace std;

//function prototypes
void display(Node* current, int depth);

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
                //add(head, head, value);
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
                //add(head, head, value);
            }
        }

        if (strcmp(input, "DISPLAY") == 0) { //display tree
            display(root, 0);
        }

        if (strcmp(input, "REMOVE") == 0) { //delete an integer from tree
            cout << "Enter an integer to REMOVE:" << endl;
            int value; cin >> value;

            //head = remove(head, value);
        }

        if (strcmp(input, "SEARCH") == 0) { //search for an integer
            cout << "Enter an integer to search for:" << endl;
            int value; cin >> value; 
            /*
            if (search(head, value) == true) { //value found in tree
                cout << "Integer is in the tree!" << endl;
            }           
            else { //value not found in tree
                cout << "Integer is not in the tree!" << endl;
            }
            */
        }

        if (strcmp(input, "QUIT") == 0) { //quit
            stillPlaying = false;
        }
    }
}

//void add(Node* current, int value, )

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
        //cout << current->getValue() << endl;
        //cout << "B" << current->getValue() << endl;
        cout << "B" << current->getValue() << ":";
    }
    else if (current->getColor() == 1) { //red node
        //cout << "\033[1;31m" << current->getValue() << " \033[0m" << endl;
        //cout << "R" << current->getValue() << endl;
        cout << "R" << current->getValue() << ":";
    }

    if (current->getParent() == NULL) {
        cout << "NULL" << endl;
    }
    else {
        cout << "P" << current->getParent()->getValue() << endl;
    }

    if (current->getLeft() != NULL) { //go left
        display(current->getLeft(), depth+1); //recursive call
    }
}