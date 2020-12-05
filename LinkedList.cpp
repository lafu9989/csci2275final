#include "LinkedList.h"
#include <iostream>

using namespace std;

//constructor
LinkedList::LinkedList(){
    root = nullptr;
    tail = nullptr;
    currentSize = 0; 
}

//adds name to the end of the linked list
void LinkedList::push(string name){
    LLPerson *toAdd = new LLPerson(name);
    if(root == nullptr){
        root = toAdd;
        tail = toAdd; 
        currentSize = 1; 
        return;
    }
    else{
        tail->next = toAdd;
        tail = toAdd;
        currentSize++; 
    }
}

//prints the contents of the linked list
void LinkedList::printLL(){
    LLPerson *temp = root;
    while(temp != nullptr){
        cout << temp->name << endl;
        temp = temp->next;
    }
}

//returns the string at that index of the linked list (0-indexed)
string LinkedList::valueAt(int index){
    if(index >= currentSize){
        return "";
    }
    else{
        LLPerson *temp = root; 
        for(int i = 0; i < index; i++){
            temp = temp->next; 
        }
        return temp->name; 
    }
}

//checks if the linked list is empty, returns true if it is
bool LinkedList::isEmpty(){
    if(currentSize == 0){
        return true;
    }
    return false;
}

//returns the size of the linked list
int LinkedList::size(){
    return currentSize; 
}