//
//  DLnode.h
//  p2
//
//  Created by Anastasia Nesterova on 10/18/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#ifndef DLnode_h
#define DLnode_h

#include <iostream>

class DLnode{
    
public:
    DLnode();
    DLnode(const int&);
    int updateBalance();
    int getBalance();
    int height;
    int value;
    DLnode *parent;
    DLnode *left, *right;
};

DLnode::DLnode()
{
    this->value = 0;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
}

DLnode::DLnode(const int& integer)
{
    this->value = integer;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
}

// this function must update the height of the node and return the difference between the height
// of the left and right subtrees
int DLnode::updateBalance()
{
    int rightHeight = right ? right->height : 0;
    int leftHeight = left ? left->height : 0;
    
    height = std::max(leftHeight, rightHeight) + 1;
    return leftHeight - rightHeight;
}

int DLnode::getBalance()
{
    int rightHeight = right ? right->height : 0;
    int leftHeight = left ? left->height : 0;
    return leftHeight - rightHeight;
}


#endif /* DLnode_h */
