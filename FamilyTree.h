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
    vector<Person *> children; //stores pointers to children
    Person *parent1; //pointer to parents
    Person *parent2; 
    bool visited; //used in DFS operations
    int FamID; //used to assign family groups

    Family(Person *parent1, Person *parent2){
        this->parent1 = parent1; 
        this->parent2 = parent2; 
        visited = false;
        FamID = -1; 
    }
};

struct Person{
    string name;
    int parents; //index of parent family
    int children; //index of child family
    bool visited; //used in DFS operations
    int FamID; //used to assign family groups

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
        vector<Family> families; //stores families in family tree
        bool assigned; //checks if family groups have already been assigned (if so, no need to re-assign)
        Person * findPerson(string name); 
        int findFamily(string p1, string p2); 
        void DFSLabel(int i, int ID); 
        void unvisit(); 
        void assignFamily(); 
        void DFSLabelAndPrint(int i, int ID); 

    public:
        FamilyTree(){
            assigned = false;
        };
        ~FamilyTree(){}; 
        bool buildTree(string file); 
        void printTree(); 
        int addFamily(string p1, string p2); 
        bool addChild(string p1, string p2, string child); 
        void assignAndPrintFamily(); 
        bool areRelated(string name1, string name2);
        LinkedList findAncestors(string name); 
        LinkedList findSiblings(string name); 
        LinkedList findChildren(string name); 
        string findCommonAncestor(string name1, string name2); 
};


#endif 