//
//  node.h
//  p2
//
//  Created by Anastasia Nesterova on 10/13/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#ifndef node_h
#define node_h

#include <iostream>

class Node{
    
public:
    Node(const int);
    int value;
    Node *left, *right;
};

Node::Node(const int value)
{
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

#endif /* node_h */
