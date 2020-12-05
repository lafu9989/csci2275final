#include "FamilyTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>

using namespace std; 


//returns pointer to Person object with matching name
Person * FamilyTree::findPerson(string name){
    for(int i = 0; i < families.size(); i++){ 
        if(families[i].parent1->name == name){
            return families[i].parent1;
        }
        else if(families[i].parent2->name == name){
            return families[i].parent2; 
        }
        else{
            for(int j = 0; j < families[i].children.size(); j++){
                if(families[i].children[j]->name == name){
                    return families[i].children[j]; 
                }
            }
        }
    }
    return nullptr;
}

//returns index of family in vector families that has p1 and p2 as parents
int FamilyTree::findFamily(string p1, string p2){
    for(int i = 0; i < families.size(); i++){
        if(families[i].parent1->name == p1 && families[i].parent2->name == p2){
            return i; 
        }
    }
    return -1; 
}

//builds tree from filename, returns true if successful
//file should be a csv file with each line being 1 family
//example line: <parent1>,<parent2>,<child-1>,<child-2>,...,<child-n>
bool FamilyTree::buildTree(string file){
    ifstream inputFile; 
    inputFile.open(file); 
    if(!inputFile.is_open()){
        return false; 
    }
    string line; 
    while(getline(inputFile, line)){
        stringstream ss(line); 
        string p1, p2;
        getline(ss,p1,','); 
        getline(ss,p2,','); 
        addFamily(p1,p2); 
        string child;
        while(getline(ss,child,',')){
            addChild(p1,p2,child); 
        }
    }
    return true; 
}

//prints tree in following format:
//<parent1> + <parent2>: <child1>,<child2>,...,<child-n>
void FamilyTree::printTree(){
    for(int i = 0; i < families.size(); i++){
        cout << families[i].parent1->name << " + " << families[i].parent2->name << ": "; 
        for(int j = 0; j < families[i].children.size(); j++){
            cout << families[i].children[j]->name;
            if(j != families[i].children.size()-1){
                cout << ", "; 
            }
        }
        cout << endl; 
    }
}

//adds a family to the family tree with parents p1 and p2
//returns index of new family in vector families
int FamilyTree::addFamily(string p1, string p2){
    Person *parent1 = findPerson(p1); 
    Person *parent2 = findPerson(p2); 

    //if parent1 or parent2 don't exist, creates new Person objects
    if(parent1 == nullptr){
        parent1 = new Person(p1); 
    }
    if(parent2 == nullptr){
        parent2 = new Person(p2); 
    }

    Family newFamily(parent1, parent2); 
    families.push_back(newFamily);
    parent1->children = families.size()-1; 
    parent2->children = families.size()-1;  
    return families.size()-1;  
}

//adds a child to the family that has parents p1 and p2
//returns true if child is successfully added 
bool FamilyTree::addChild(string p1, string p2, string child){
    int theFamily = findFamily(p1, p2); 
    Person *toAdd = findPerson(child);

    //if the child is not found in the tree already, create a new Person
    if(toAdd == nullptr){
        toAdd = new Person(child); 
    }

    //if the family is not found in the tree already, create a new Family
    if(theFamily == -1){
        theFamily = addFamily(p1, p2); 
    }

    families[theFamily].children.push_back(toAdd); 
    toAdd->parents = theFamily; 
    return true; 
}

//uses modified DFS to assign family IDS to anyone that is related (including by marriage)
//called by isRelated function so it doesn't print all the groups when it runs
void FamilyTree::assignFamily(){ 
    int FamID = 1; 
    int i = 0; 
    while(i < families.size()){
        while(families[i].visited){
            i++; 
        }
        if(i < families.size()){
            DFSLabel(i, FamID); 
        } 
        FamID++; 
    }
    assigned = true;
    unvisit(); 
}

//does the same thing as assignFamily() but prints family groups as they are assigned
//called when user prompts assigning family groups 
void FamilyTree::assignAndPrintFamily(){ 
    int FamID = 1; 
    int i = 0; 
    while(i < families.size()){
        while(families[i].visited){
            i++; 
        }
        if(i < families.size()){
            cout << "Family " << FamID << ":" << endl; 
            DFSLabelAndPrint(i, FamID); 
        } 
        FamID++; 
    }
    assigned = true;
    unvisit(); 
}

//function used by assignAndPrintFamily to label family groups
void FamilyTree::DFSLabelAndPrint(int i, int ID){
    stack<int> s;
    s.push(i); 
    while(!s.empty()){
        int current = s.top(); 
        s.pop(); 
        if(current != -1 && !families[current].visited){
            families[current].FamID = ID; 
            families[current].visited = true;
            if(!families[current].parent1->visited){
                families[current].parent1->FamID = ID;
                families[current].parent1->visited = true;
                cout << families[current].parent1->name << endl; 
                s.push(families[current].parent1->parents);
            }
            if(!families[current].parent2->visited){
                families[current].parent2->FamID = ID; 
                families[current].parent2->visited = true;
                cout << families[current].parent2->name << endl; 
                s.push(families[current].parent2->parents); 
            }
            for(int i = 0; i < families[current].children.size(); i++){
                if(!families[current].children[i]->visited){
                    families[current].children[i]->FamID = ID; 
                    families[current].children[i]->visited = true;
                    cout << families[current].children[i]->name << endl; 
                     s.push(families[current].children[i]->children); 
                }
            }
        }
    }
}
        
//used by assignFamily to label family groups
void FamilyTree::DFSLabel(int i, int ID){
    stack<int> s;
    s.push(i); 
    while(!s.empty()){
        int current = s.top(); 
        s.pop(); 
        if(current != -1 && !families[current].visited){
            families[current].FamID = ID; 
            families[current].visited = true;
            families[current].parent1->FamID = ID;
            families[current].parent1->visited = true;
            s.push(families[current].parent1->parents);
            families[current].parent2->FamID = ID; 
            families[current].parent2->visited = true;
            s.push(families[current].parent2->parents); 
            for(int i = 0; i < families[current].children.size(); i++){
                families[current].children[i]->FamID = ID; 
                families[current].children[i]->visited = true;
                s.push(families[current].children[i]->children); 
            }
        }
    }
}

//uses family IDs assigned in assignFamily() to determine if 2 people in tree are related
//returns true if family IDs are the same
bool FamilyTree::areRelated(string name1, string name2){
    if(!assigned){
        assignFamily();
    }
    Person *p1 = findPerson(name1);
    Person *p2 = findPerson(name2); 

    //if either person does not already exist in the tree, return false
    if(p1 == nullptr || p2 == nullptr){
        return false; 
    }
    if(p1->FamID == p2->FamID){
        return true;
    }
    return false; 
}

//returns a linked list of all the ancestors (parents, grandparents, great-grandparents, etc) of a person using BFS
LinkedList FamilyTree::findAncestors(string name){ 
    Person *p1 = findPerson(name); 
    LinkedList toReturn; 
    queue<int> q; 
    if(p1 == nullptr){
        return toReturn; 
    }
    q.push(p1->parents); 
    while(!q.empty()){
        int current = q.front(); 
        q.pop(); 
        if(current != -1){
            toReturn.push(families[current].parent1->name);
            toReturn.push(families[current].parent2->name); 
            q.push(families[current].parent1->parents);
            q.push(families[current].parent2->parents); 
        }
    }
    return toReturn; //list should be ordered as parents, grandparents, greatgrandparents, etc.  
}

//unvisits people/families in tree after assigning family groups
void FamilyTree::unvisit(){
    for(int i = 0; i < families.size(); i++){
        families[i].visited = false; 
        families[i].parent1->visited = false;
        families[i].parent2->visited = false;
        for(int j = 0; j < families[i].children.size(); j++){
            families[i].children[j]->visited = false; 
        }
    }
}

//returns a linked list of all the siblings of a person in the tree 
LinkedList FamilyTree::findSiblings(string name){
    Person *p1 = findPerson(name); 
    LinkedList toReturn;
    if(p1 == nullptr){
        return toReturn;
    }
    int f = p1->parents; 
    for(int i = 0; i < families[f].children.size(); i++){
        if(families[f].children[i]->name != name)
            toReturn.push(families[f].children[i]->name); 
    }
    return toReturn; 
}

//returns a linked list of all the children of a person in the tree
LinkedList FamilyTree::findChildren(string name){
    Person *p1 = findPerson(name); 
    LinkedList toReturn; 
    if(p1 == nullptr){
        return toReturn; 
    }
    int f = p1->children; 
    for(int i = 0; i < families[f].children.size(); i++){
        toReturn.push(families[f].children[i]->name); 
    }
    return toReturn; 
}

//returns the name of the most recent common ancestor that both people in the tree share
//uses the findAncestors function
string FamilyTree::findCommonAncestor(string name1, string name2){
    LinkedList person1 = findAncestors(name1);
    LinkedList person2 = findAncestors(name2); 
    if(person1.isEmpty() || person2.isEmpty()){
        return "";
    }
    for(int i = 0; i < person1.size(); i++){
        for(int j = 0; j < person2.size(); j++){
            if(person1.valueAt(i) == person2.valueAt(j)){
                return person1.valueAt(i);
            }
        }
    }
    return ""; 
}