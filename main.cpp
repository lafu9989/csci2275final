#include "FamilyTree.h"
#include "LinkedList.h"

using namespace std; 

int main(int argc, const char *argv[]){
    string filename = argv[1]; 
    FamilyTree myTree; 
    myTree.buildTree(filename);
    //myTree.printTree(); 

    // LinkedList children = myTree.findSiblings("Fred Weasley"); 
    // children.printLL(); 

    myTree.assignFamily(); 
}