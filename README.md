# csci2275final
Repo for my CSCI 2275 final project.

My idea for the final project is to create a program that can store a family tree. 

The two data structures I'll use will be:  a graph to store the family tree, and linked lists that will be returned as part of functions within the family tree. 

The family tree will be designed so that there will be a struct for each person and a struct for the family that the people are connected to; therefore, it will be a bit more complex than just an ordinary graph. (i.e., the people structs will not have adjacency matrices, but the families will have adjacency matrices of people. Inspired by [this article](https://medium.com/@bigomega/building-my-family-tree-ef0be1fba775).

The family tree will be built from a CSV file, but it will also have functions that will allow the user to manually input. It will also have functions that allow the user to find common ancestors, siblings, family members, etc., of members of the tree. Linked lists will be returned in some of these functions (ex. for the siblings function call, a linked list of siblings will be returned). 


