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
    vector<Person *> children; //store pointers to children, not children themselves so its less complicated
    Person *parent1;
    Person *parent2; 
    bool visited;
    int FamID; 

    Family(Person *parent1, Person *parent2){
        this->parent1 = parent1; 
        this->parent2 = parent2; 
        visited = false;
        FamID = -1; 
    }
};

struct Person{
    string name;
    int parents;
    int children;
    bool visited;
    int FamID; 
    //store int of family instead of pointer --> less complex

    Person(string name){
        this->name = name; 
        parents = -1; 
        children = -1; 
        visited = false; 
        FamID = -1; 
    }
};

class FamilyTree{
    private:
        vector<Family> families; 
        bool assigned;
        int numGroups; 
        Person * findPerson(string name); 
        int findFamily(string p1, string p2); //return int of family
        void DFSLabel(int i, int ID); 
        void unvisit(); 
        void assignFamily(); 
        void DFSLabelAndPrint(int i, int ID); 

    public:
        FamilyTree(){
            assigned = false;
            numGroups = -1; 
        };
        ~FamilyTree(){}; 
        bool buildTree(string file); 
        void printTree(); 
        int addFamily(string p1, string p2); //return int of family
        bool addChild(string p1, string p2, string child); 
        void assignAndPrintFamily(); 
        bool areRelated(string name1, string name2);
        LinkedList findAncestors(string name); 
        LinkedList findSiblings(string name); 
        LinkedList findChildren(string name); 
        string findCommonAncestor(string name1, string name2); 
};


#endif 