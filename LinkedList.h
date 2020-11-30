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
    public:
        LinkedList();
        void push(string name); 
        void printLL(); 
};


#endif