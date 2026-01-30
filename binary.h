//
//  binary.h
//  p2
//
//  Created by Anastasia Nesterova on 10/13/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#ifndef binary_h
#define binary_h

#include "node.h"

class BST{
    
    friend std::ostream &operator<<(std::ostream &, const BST& );
public:
    BST();
    ~BST();
    void add(const int integer);
    Node* search(const int integer);
    void remove(const int integer);
    int comparisons;
private:
    Node *root;
    void clear(Node* );
    void privatePrint(Node* ptr) const;
    void privateAdd(Node*& node, const int integer);
    Node* removeMin(Node*& node);
    void privateRemove(Node*& node, const int integer);
    void addUsingLoop(const int integer);
};

std::ostream& operator<<(std::ostream & out, const BST& tree)
{ //TODO: HELPPPPPPP
    tree.privatePrint(tree.root);
    return out;
}

void BST::privatePrint(Node* ptr) const
{
    if(ptr != NULL)
    {
        if(ptr->right == NULL && ptr->left == NULL)
        {
            std::cout << "[" << ptr->value << "]";
        }
        else if(ptr->right == NULL && ptr->left != NULL)
        {
            std::cout << "[" << ptr->value;
            privatePrint(ptr->left);
            std::cout << "[]]";
        }
        else if(ptr->right != NULL && ptr->left == NULL)
        {
            std::cout << "[" << ptr->value << "[]";
            privatePrint(ptr->right);
            std::cout << "]";
        }
        else
        {
            std::cout << "[" << ptr->value;
            privatePrint(ptr->left);
            privatePrint(ptr->right);
            std::cout << "]";
        }
        
        //privatePrint(ptr->left);
        //std::cout << "[" << ptr->value << "]";
        //privatePrint(ptr->right);
    }
}

BST::BST()
{
    root = nullptr;
    comparisons = 0;
}

BST::~BST()
{
    clear(root);
}

void BST::clear(Node* node)
{
    if(node == NULL)
        return;
    
    clear(node->left);
    clear(node->right);
    
    delete node;
    //TODO: make sure this works
}

void BST::privateAdd(Node*& node, const int integer)
{
    if(node == NULL)
    {
        ++comparisons;
        node = new Node(integer);
    }
    else if(node->value > integer)
    {
        ++comparisons;
        privateAdd(node->left, integer);
    }
    else if(node->value < integer)
    {
        ++comparisons;
        privateAdd(node->right, integer);
    }
}

void BST::add(const int integer)
{
    privateAdd(this->root, integer);
}

void BST::addUsingLoop(const int integer)
{
    Node** temp = &root;
    // Checking for the pointer that temp is referring to.
    while(*temp)
    {
        if(integer < (*temp)->value)
        {
            ++comparisons;
            temp = &(*temp)->left;
        }
        else if(integer > (*temp)->value)
        {
            ++comparisons;
            temp = &(*temp)->right;
        }
        else
        {
            return;
        }
    }
    // The pointer where we would insert the value is now null
    // and temp is referring to it. So we can allocate new Node
    // and assign to that pointer.
    *temp = new Node(integer);
}

Node* BST::search(const int integer)
{
    Node* temp = root;
    while(temp)
    {
        if(temp->value == integer)
        {
            ++comparisons;
            return temp;
        }
        else if(integer < temp->value)
        {
            ++comparisons;
            temp = temp->left;
        }
        else if(integer > temp->value)
        {
            ++comparisons;
            temp = temp->right;
        }
    }
    return nullptr;
}

Node* BST::removeMin(Node*& node)
{
    if(node)
    {
        if(node->left)
        {
            return removeMin(node->left); // keep moving left because min node is always on the left side of the subtree
        }
        else
        {
            Node* temp = node; //temp stores node address to be returned because node will be changed
            node = node->right; //node is being changed to node->right so whoever was pointing to node now points to node->right
            temp->right = nullptr; //this node has no children anymore
            return temp; //return address of node
        }
    }
    else
    {
        throw std::logic_error("cannot call removeMin on null node");
    }
}

//this function removes integer from subtree defined by node
void BST::privateRemove(Node*& node, const int integer)
{
    if(node)
    {
        if(node->value < integer)
        {
            ++comparisons;
            privateRemove(node->right, integer);
        }
        else if(node->value > integer)
        {
            ++comparisons;
            privateRemove(node->left, integer);
        }
        else if(node->left && node->right) // both != NULL
        {
            ++comparisons;
            Node* minRightSubtreeNode = removeMin(node->right);
            node->value = minRightSubtreeNode->value; //TODO: copy other data????
            //std::cout << "deleting min " << minRightSubtreeNode->value << std::endl;
            delete minRightSubtreeNode;
        }
        else
        {
            Node* remove = node;
            if(node->left)
            {
                node = node->left;
            }
            else if(node->right)
            {
                node = node->right;
            }
            else
            {
                node = nullptr;
            }
            delete remove;
        }
    }
    else
    {
        //std::cout << "Value " << integer << " not found" << std::endl;
        return;
    }
}

void BST::remove(const int integer)
{
    privateRemove(root, integer);
}

#endif /* binary_h */
