#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>

using namespace std;



struct LLPerson{
    string name; 
    LLPerson * next;
    LLPerson(string name){
        this->name = name; 
    }
};

class LinkedList{
    private:
        LLPerson *root; 
        LLPerson *tail;
        int currentSize; 
    public:
        LinkedList();
        void push(string name); 
        void printLL(); 
        string valueAt(int index); 
        bool isEmpty();
        int size(); 
};


#endif