#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList(){
    root = nullptr;
    tail = nullptr;
}

void LinkedList::push(string name){
    LLPerson *toAdd = new LLPerson(name);
    if(root == nullptr){
        root = toAdd;
        tail = toAdd; 
        return;
    }
    else{
        tail->next = toAdd;
        tail = toAdd;
    }
}


void LinkedList::printLL(){
    LLPerson *temp = root;
    while(temp != nullptr){
        cout << temp->name << endl;
        temp = temp->next;
    }
}