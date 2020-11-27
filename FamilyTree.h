#ifndef FAMILYTREE_H
#define FAMILYTREE_H
#include <vector>
#include <string>
#include <iostream>
#include "LinkedList.h"


using namespace std; 

struct Person;
struct Family;

struct Family{
    vector<Person> children;
    Person *parent1;
    Person *parent2; 
    bool visited;
    int FamID; 

    Family(Person *parent1, Person *parent2){
        this->parent1 = parent1; 
        this->parent2 = parent2; 
    }
};

struct Person{
    string name;
    Family *parents;
    Family *children;

    Person(string name){
        this->name = name; 
    }
};

class FamilyTree{
    private:
        vector<Family> families; 
        Person * findPerson(string name); 
        Family * findFamily(string p1, string p2); 
    public:
        bool buildTree(string file); 
        void printTree(); 
        bool addFamily(string p1, string p2); 
        bool addChild(string p1, string p2, string child); 
        void assignFamily(); 
        void assignFamily(string name); //overload with family name
        bool areRelated(string name1, string name2);
        LinkedList findAncestors(string name); 
        LinkedList findSiblings(string name); 
        LinkedList findChildren(string name); 
        string findCommonAncestor(string name1, string name2); 
};


#endif 