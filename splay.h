//
//  splay.h
//  p2
//
//  Created by Anastasia Nesterova on 10/13/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#ifndef splay_h
#define splay_h

#include "DLnode.h"
#include "avl.h"

class Splay{
    
    friend std::ostream &operator<<(std::ostream &, const Splay& );
public:
    Splay();
    ~Splay();
    void add(const int integer);
    DLnode* search(const int integer);
    void remove(const int integer);
    int comparisons;
private:
    void splay(DLnode* node);
    void splayStep(DLnode* node);
    void privatePrint(DLnode* ptr) const;
    DLnode* privateAdd(DLnode*& parent, DLnode*& node, const int integer);
    void zigLeft(DLnode* node);
    void zigRight(DLnode* node);
    void zigZagLeft(DLnode* node);
    void zigZagRight(DLnode* node);
    void zigZigLeft(DLnode* node);
    void zigZigRight(DLnode* node);
    DLnode* removeMin(DLnode*& node);
    void privateRemove(DLnode*& node, const int integer);
    DLnode* root;
    void clear(DLnode* );
    //privateprint
    //privateadd
    //removes
};

std::ostream &operator<<(std::ostream & out, const Splay& tree)
{
    tree.privatePrint(tree.root);
    return out;
}

void Splay::privatePrint(DLnode* ptr) const
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

Splay::Splay()
{
    root = nullptr;
    comparisons = 0;
}

Splay::~Splay()
{
    clear(root);
}

void Splay::clear(DLnode* node)
{
    if(node == NULL)
        return;
    
    clear(node->left);
    clear(node->right);
    
    delete node;
}

void Splay::add(const int integer)
{
    DLnode* node = nullptr;
    if(root == NULL)
    {
        ++comparisons;
        node = new DLnode(integer);
        root = node;
    }
    else if(root->value > integer)
    {
        ++comparisons;
        node = privateAdd(root, root->left, integer);
    }
    else if(root->value < integer)
    {
        ++comparisons;
        node = privateAdd(root, root->right, integer);
    }
    splay(node);
    root = node;
}

// adds node to the tree defined by parent then splays it up to the root
DLnode* Splay::privateAdd(DLnode*& parent, DLnode*& node, const int integer)
{
    if(node == NULL)
    {
        ++comparisons;
        node = new DLnode(integer);
        node->parent = parent;
        if(parent->value > integer)
        {
            ++comparisons;
            parent->left = node;
        }
        else if(parent->value < integer)
        {
            ++comparisons;
            parent->right = node;
        }
        return node;
    }
    else if(node->value > integer)
    {
        ++comparisons;
        return privateAdd(node, node->left, integer);
    }
    else if(node->value < integer)
    {
        ++comparisons;
        return privateAdd(node, node->right, integer);
    }
    else
    {
        return parent;
    }
}

DLnode* Splay::search(const int integer)
{
    DLnode* temp = root;
    while(temp)
    {
        if(integer < temp->value)
        {
            ++comparisons;
            temp = temp->left;
        }
        else if(integer > temp->value)
        {
            ++comparisons;
            temp = temp->right;
        }
        else
        {
            break;
        }
    }
    if(temp)
    {
        //std::cout << "found value" << std::endl;
        //std::cout << "temp parent: " << temp->parent->value << std::endl;
        splay(temp); // temp is now top of the tree
        root = temp; // root has to be reassigned to the top of the tree
    }
    return temp;
}

// splays node to the top of the tree
void Splay::splay(DLnode* node)
{
    while(node->parent)
    {
        splayStep(node);
    }
}

// performs necessary splay step to node (one zig, zigzag, or zigzig)
// based off its position in the tree
void Splay::splayStep(DLnode* node)
{
    /**
     3 cases, each with 2 subcases
     1. Zig (left and right) (only when node starts at odd depth, child of root)
     2. Zig-Zag (right child of a left or left child of a right)
     3. Zig-Zig (right child of a right child or left child of a left child)
     */
    //std::cout << "node: " << node->value << " root: " << (root ? root->value : 9999999999999)
    // << " parent: " << node->parent->value << std::endl;
    
    if(node->parent == nullptr)
    {
        return;
    }
    else if(node->parent->parent == nullptr) // zig
    {
        ++comparisons;
        if(node->parent->left && node->parent->left == node)
        {
            ++comparisons;
            zigLeft(node);
        }
        else if(node->parent->right && node->parent->right == node)
        {
            ++comparisons;
            zigRight(node);
        }
    }
    else // when parent->parent != nullptr
    {
        DLnode* grandparent = node->parent->parent;
        //std::cout << "GRANDPARENT: " << grandparent->value << std::endl;
        if(grandparent->left)
        {
            DLnode* left = grandparent->left;
            // current node could be either on the left or right side of the left
            // that is why we check only two cases
            if(left->left && left->left == node)
            {
                //std::cout << "zigzigleft: " << node->value << std::endl;
                zigZigLeft(node); // left left (zigZig)
                return;
            }
            else if(left->right && left->right == node)
            {
                //std::cout << "zigzagleft: " << node->value << std::endl;
                zigZagLeft(node); // left right (zigZagLeft) (case 2)
                return;
            }
        }
        if(grandparent->right)
        {
            DLnode* right = grandparent->right;
            // current node could be either on the left or right side of the right
            // that is why we check only two cases
            if(right->right && right->right == node)
            {
                //std::cout << "zigzigright: " << node->value << std::endl;
                zigZigRight(node); // right right (zigZig)
            }
            else if(right->left && right->left == node)
            {
                //std::cout << "zigzagright: " << node->value << std::endl;
                zigZagRight(node); // right left (zigZagRight) (case 2)
            }
        }
    }
}

// node is the left node
// reshuffles node and its parent
// returns new top of the tree, which was the left child of parent
void Splay::zigLeft(DLnode* node)
{
    if(node->parent->left != node)
    {
        throw std::logic_error("zigLeft: incorrectly called");
    }
    DLnode* old_parent = node->parent;
    DLnode* grandparent = old_parent->parent;
    //connect the node to grandparent
    node->parent = grandparent;
    if(grandparent)
    {
        if(grandparent->left == old_parent)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    //grandparent and node are connected
       
    //taking right child of the node and making it left child of old_parent
    old_parent->left = node->right;
    if(old_parent->left)
    {
        old_parent->left->parent = old_parent;
    }
    
    //link old_parent to the node
    old_parent->parent = node;
    node->right = old_parent;
    /*
    if(node->parent->left != node)
    {
        throw std::logic_error("zigLeft: incorrectly called");
    }
    DLnode* old_parent = node->parent;
    DLnode* grandparent = old_parent->parent;
    node->parent = grandparent;
    old_parent->parent = node;
    old_parent->left = node->right;
    node->right = old_parent;
    if(grandparent)
    {
        if(grandparent->left == old_parent)
        {
            grandparent->left = node;
        }
        else if(grandparent->right == old_parent)
        {
            grandparent->right = node;
        }
        else
        {
            throw std::logic_error("zigLeft: cannot match grandparent");
        }
    }*/
}

// node is the right node
// reshuffles node and its parent
// returns new top of the tree, which was the right child of parent
void Splay::zigRight(DLnode* node)
{
    if(node->parent->right != node)
    {
        throw std::logic_error("zigRight: incorrectly called");
    }
    DLnode* old_parent = node->parent;
    DLnode* grandparent = old_parent->parent;
    //connect the node to grandparent
    node->parent = grandparent;
    if(grandparent)
    {
        if(grandparent->left == old_parent)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    //grandparent and node are connected
    
    //taking left child of the node and making it right child of old_parent
    old_parent->right = node->left;
    if(old_parent->right)
    {
        old_parent->right->parent = old_parent;
    }
    
    //link old_parent to the node
    old_parent->parent = node;
    node->left = old_parent;
}

// node is right child of the left child
// node is being splayed to the top of the tree
// returns new top of the tree
void Splay::zigZagLeft(DLnode* node)
{
    zigRight(node);
    zigLeft(node);
}

// node is left child of the right child
// node is being splayed to the top of the tree
// returns new top of the tree
void Splay::zigZagRight(DLnode* node)
{
    zigLeft(node);
    zigRight(node);
}

// returns new top of the tree
void Splay::zigZigLeft(DLnode* node)
{
    //first, parent goes on top of his parent
    zigLeft(node->parent);
    //then, node goes on top
    zigLeft(node);
}

void Splay::zigZigRight(DLnode* node)
{
    //first, parent goes on top of his parent
    zigRight(node->parent);
    //then, node goes on top
    zigRight(node);
}

DLnode* Splay::removeMin(DLnode*& node)
{
    if(node)
    {
        if(node->left)
        {
            return removeMin(node->left); // keep moving left because min node is always on the left side of the subtree
        }
        else
        {
            DLnode* temp = node; //temp stores node address to be returned because node will be changed
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
void Splay::privateRemove(DLnode*& node, const int integer)
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
            DLnode* minRightSubtreeNode = removeMin(node->right);
            node->value = minRightSubtreeNode->value;
            delete minRightSubtreeNode;
        }
        else
        {
            DLnode* remove = node;
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
        return;
    }
}

void Splay::remove(const int integer)
{
    search(integer);
    if(root && root->value == integer)
    {
        ++comparisons;
        privateRemove(root, integer);
    }
}

#endif /* splay_h */
