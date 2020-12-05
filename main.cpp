#include "FamilyTree.h"
#include "LinkedList.h"
#include <iostream>

using namespace std; 

int main(int argc, const char *argv[]){
    FamilyTree tree;
    
    //if a filename argument is provided, use that to build the tree
    //if not provided, a tree can still be manually built 
    if (argc == 2) {
        string filename(argv[1]);
        tree.buildTree(filename); 
    }
    else{
        cout << "Filename not provided. Tree is empty." << endl; 
    }

    string dmenu =  "======Main Menu======\n"
                    "1. Print Tree\n"
                    "2. Add Family\n"
                    "3. Add Child\n"
                    "4. Assign Family Groups\n"
                    "5. Check if related\n"
                    "6. Find Ancestors\n"
                    "7. Find Siblings\n"
                    "8. Find Children\n"
                    "9. Find Common Ancestor\n"
                    "10. Quit\n";
    
    int choice = 0;
    bool done = false;
    
    
    do {
        cout << dmenu;
        cin >> choice;
        
        // flush the newlines and other characters
        cin.clear();
        cin.ignore();
        
        switch (choice) {
            case 1: //print Tree
            {
                tree.printTree(); 
                break;
            }
            case 2: //add family
            {
                string parent1, parent2; 
                cout << "Enter parent 1: ";
                getline(cin,parent1);
                cout << "Enter parent2: ";
                getline(cin,parent2); 
                tree.addFamily(parent1, parent2);
                cout << "Family added successfully." << endl;
                break;
            } 
            case 3: //add children
            {
                string parent1, parent2, child; 
                cout << "Enter parent 1: ";
                getline(cin,parent1);
                cout << "Enter parent 2: ";
                getline(cin,parent2);
                cout << "Enter child: ";
                getline(cin,child); 
                bool success = tree.addChild(parent1, parent2, child);
                if(success){
                    cout << "Child added successfully." << endl; 
                }
                else{
                    cout << "Error. Please try again." << endl; 
                }
                break;
            }
            case 4: //assign family groups
            {
                tree.assignAndPrintFamily(); 
                break;
            }
            case 5: //check if related
            {
                string person1, person2;
                cout << "Enter person 1: ";
                getline(cin,person1);
                cout << "Enter person 2: "; 
                getline(cin,person2);  
                bool related = tree.areRelated(person1, person2); 
                if(related){
                    cout << "Yes, " << person1 << " and " << person2 << " are related." << endl;
                }
                else{
                    cout << "No, " << person1 << " and " << person2 << " are not related." << endl; 
                }
                break; 
            }
            case 6: //find ancestors
            {
                string person;
                cout << "Enter person's name: ";
                getline(cin, person);
                LinkedList ancestors = tree.findAncestors(person); 
                ancestors.printLL(); 
                break; 
            }
            case 7: //find siblings
            {
                string person;
                cout << "Enter person's name: ";
                getline(cin,person);
                LinkedList siblings = tree.findSiblings(person); 
                siblings.printLL(); 
                break; 
            }
            case 8: //find children
            {   
                string person;
                cout << "Enter person's name: ";
                getline(cin,person);
                LinkedList children = tree.findChildren(person); 
                children.printLL(); 
                break; 
            }
            case 9: //find common ancestor
            {
                string person1, person2;
                cout << "Enter person 1: ";
                getline(cin,person1);
                cout << "Enter person 2: "; 
                getline(cin,person2);
                string ancestor = tree.findCommonAncestor(person1, person2);
                if(ancestor != "")
                    cout << person1 << " and " << person2 << "'s common ancestor is " << ancestor << endl; 
                break; 
            }
            default:
            {
                done = true;
                break;
            }
        }
        
    } while(!done);
    
    return 0;
}