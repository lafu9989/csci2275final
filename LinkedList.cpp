#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList(){
    root = nullptr;
    tail = nullptr;
    currentSize = 0; 
}

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


void LinkedList::printLL(){
    LLPerson *temp = root;
    while(temp != nullptr){
        cout << temp->name << endl;
        temp = temp->next;
    }
}

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

bool LinkedList::isEmpty(){
    if(currentSize == 0){
        return true;
    }
    return false;
}

int LinkedList::size(){
    return currentSize; 
}