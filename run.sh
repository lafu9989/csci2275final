#shell script to compile and run program using the testinputtree file as input
#usage: ./run.sh

g++ -std=c++11 FamilyTree.cpp LinkedList.cpp main.cpp
./a.out testinputtree.csv