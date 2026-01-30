//
//  main.cpp
//  p2
//
//  Created by Anastasia Nesterova on 10/13/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "binary.h"
#include "avl.h"
#include "splay.h"

using namespace std;

int main(int argc, const char * argv[])
{
    /*
    std::srand ( unsigned ( std::time(0) ) );
    
    vector<int> v1(1000);
    vector<int> v2(1000);
    
    for(int i = 0; i < 1000; i++)
    {
        v1[i] = i+1;
        v2[i] = i+1;
    }
    
    for(int i = 0; i < 1000; i++)
    {
        std::random_shuffle(v1.begin(), v1.end());
        std::random_shuffle(v2.begin(), v2.end());
        
        Splay a;
        for(int i = 0; i < 1000; i++)
        {
            a.add(v1[i]);
        }
        for(int i = 0; i < 1000; i++)
        {
            a.remove(v2[i]);
        }
    }
    cout << "program finished" << endl;*/
    
    string fileName = "";
    string input = "";
    string dollar = "";
    int integer = 0;
    
    fileName = argv[1];
    ifstream inFile;
    
    inFile.open(fileName.c_str());
    
    if(!inFile)
    {
        return 0;
    }
    
    BST binary;
    AVL avl;
    Splay splay;
    
    inFile >> integer;
    while(inFile)
    {
        binary.add(integer);
        avl.add(integer);
        splay.add(integer);
        inFile >> integer;
    }
    
    cout << "Binary tree: " << binary << " comparisons: " << binary.comparisons << endl;
    cout << "AVL tree: " << avl << " comparisons: " << avl.comparisons << endl;
    cout << "Splay tree: " << splay << " comparisons: " << splay.comparisons << endl << endl;
    
    inFile.clear();
    inFile >> dollar;
    
    inFile >> integer;
    while(inFile)
    {
        binary.search(integer);
        avl.search(integer);
        splay.search(integer);
        inFile >> integer;
    }
    
    cout << "POST SEARCHES" << endl;
    cout << "Splay tree: " << splay << endl << endl;
    
    inFile.clear();
    inFile >> dollar;
    
    inFile >> integer;
    while(inFile)
    {
        binary.remove(integer);
        avl.remove(integer);
        splay.remove(integer);
        inFile >> integer;
    }
    
    cout << "POST REMOVALS" << endl;
    cout << "Binary tree: " << binary << endl;
    cout << "AVL tree: " << avl << endl;
    cout << "Splay tree: " << splay << endl << endl;
    
    cout << "TOTAL COMPARISONS" << endl;
    cout << "Binary comparisons: " << binary.comparisons << endl;
    cout << "AVL comparisons: " << avl.comparisons << endl;
    cout << "Splay comparisons: " << splay.comparisons << endl;
    
    return 0;
}
