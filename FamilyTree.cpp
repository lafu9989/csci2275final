#include "FamilyTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

using namespace std; 


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

int FamilyTree::findFamily(string p1, string p2){
    for(int i = 0; i < families.size(); i++){
        if(families[i].parent1->name == p1 && families[i].parent2->name == p2){
            return i; 
        }
    }
    return -1; 
}

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

void FamilyTree::printTree(){
    for(int i = 0; i < families.size(); i++){
        cout << families[i].parent1->name << " + " << families[i].parent2->name << ": "; 
        for(int j = 0; j < families[i].children.size(); j++){
            cout << families[i].children[j]->name << ", "; 
        }
        cout << endl; 
    }
}
        
int FamilyTree::addFamily(string p1, string p2){
    Person *parent1 = findPerson(p1); 
    Person *parent2 = findPerson(p2); 
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
        
bool FamilyTree::addChild(string p1, string p2, string child){
    int theFamily = findFamily(p1, p2); 
    Person *toAdd = findPerson(child);
    if(toAdd == nullptr){
        toAdd = new Person(child); 
    }
    if(theFamily == -1){
        theFamily = addFamily(p1, p2); 
    }
    families[theFamily].children.push_back(toAdd); 
    toAdd->parents = theFamily; 
    return true; 
}

void FamilyTree::assignFamily(){
    int FamID = 1; 
    int i = 0; 
    while(i < families.size()){
        while(families[i].visited){
            i++; 
        }
        if(i < families.size()){
            cout << "Group " << FamID << ":" << endl; 
            DFSLabel(i, FamID); 
        } 
        FamID++; 
    }
}

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
            cout << families[current].parent1->name << endl; 
            s.push(families[current].parent1->parents);
            families[current].parent2->FamID = ID; 
            families[current].parent2->visited = true;
            cout << families[current].parent2->name << endl; 
            s.push(families[current].parent2->parents); 
            for(int i = 0; i < families[current].children.size(); i++){
                families[current].children[i]->FamID = ID; 
                families[current].children[i]->visited = true;
                cout << families[current].children[i]->name << endl; 
                s.push(families[current].children[i]->children); 
            }
        }
    }
}
    
void FamilyTree::assignFamily(string name){ //overload with family name

}
        
bool FamilyTree::areRelated(string name1, string name2){

}
        
LinkedList FamilyTree::findAncestors(string name){

}

LinkedList FamilyTree::findSiblings(string name){
    Person *p1 = findPerson(name); 
    int f = p1->parents;
    LinkedList toReturn; 
    for(int i = 0; i < families[f].children.size(); i++){
        if(families[f].children[i]->name != name)
            toReturn.push(families[f].children[i]->name); 
    }
    return toReturn; 
}
        
LinkedList FamilyTree::findChildren(string name){
    Person *p1 = findPerson(name); 
    int f = p1->children; 
    LinkedList toReturn; 
    for(int i = 0; i < families[f].children.size(); i++){
        toReturn.push(families[f].children[i]->name); 
    }
    return toReturn; 
}

string FamilyTree::findCommonAncestor(string name1, string name2){

}