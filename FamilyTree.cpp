#include "FamilyTree.h"
#include <vector>
#include <fstream>
#include <sstream>

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
                if(families[i].children[j].name == name){
                    return &families[i].children[j]; 
                }
            }
        }
    }
    return nullptr;
}

Family * FamilyTree::findFamily(string p1, string p2){
    for(int i = 0; i < families.size(); i++){
        if(families[i].parent1->name == p1 && families[i].parent2->name == p2){
            return &families[i]; 
        }
    }
    return nullptr; 
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
            cout << families[i].children[j].name << ", "; 
        }
        cout << endl; 
    }
}
        
Family * FamilyTree::addFamily(string p1, string p2){
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
    return &newFamily;  
}
        
bool FamilyTree::addChild(string p1, string p2, string child){
    Family *theFamily = findFamily(p1, p2); 
    Person *toAdd = findPerson(child);
    if(toAdd == nullptr){
        toAdd = new Person(child); 
    }
    if(theFamily == nullptr){
        theFamily = addFamily(p1, p2); 
    }
    theFamily->children.push_back(*toAdd); 
    return true; 
}

void FamilyTree::assignFamily(){

}
    
void FamilyTree::assignFamily(string name){ //overload with family name

}
        
bool FamilyTree::areRelated(string name1, string name2){

}
        
LinkedList FamilyTree::findAncestors(string name){

}

LinkedList FamilyTree::findSiblings(string name){

}
        
LinkedList FamilyTree::findChildren(string name){

}

string FamilyTree::findCommonAncestor(string name1, string name2){

}