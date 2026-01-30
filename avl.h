//
//  avl.h
//  p2
//
//  Created by Anastasia Nesterova on 10/13/19.
//  Copyright © 2019 Anastasia Nesterova. All rights reserved.
//

#ifndef avl_h
#define avl_h

#include "DLnode.h"
#include "binary.h"

class AVL{
    friend std::ostream &operator<<(std::ostream &, const AVL& );
public:
    AVL();
    ~AVL();
    void add(const int integer);
    DLnode* search(const int integer);
    void remove(const int integer);
    int comparisons;
private:
    void privatePrint(DLnode* ) const;
    void printNode(DLnode* ) const;
    void clear(DLnode* );
    DLnode* privateAdd(DLnode* node, const int integer);
    DLnode* privateRemove(DLnode* node, const int integer);
    DLnode* rebalanceSubtree(DLnode* node);
    DLnode* removeMin(DLnode*& node);
    DLnode* rotateWithLeftChild(DLnode* node);
    DLnode* rotateWithRightChild(DLnode* node);
    DLnode* doubleRotateWithLeftChild(DLnode* node);
    DLnode* doubleRotateWithRightChild(DLnode* node);
    void validate(DLnode* node);
    DLnode* root;
    //privateprint
    //privateadd
    //removes
};

std::ostream &operator<<(std::ostream & out, const AVL& tree)
{
    tree.privatePrint(tree.root);
    return out;
}

void AVL::privatePrint(DLnode* ptr) const
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

AVL::AVL()
{
    root = nullptr;
    comparisons = 0;
}

AVL::~AVL()
{
    clear(root);
}

void AVL::clear(DLnode* node)
{
    if(node == NULL)
        return;
    
    clear(node->left);
    clear(node->right);
    
    delete node;
}

// inserts node and then rebalances the tree
void AVL::add(const int integer)
{
    //std::cout << "AVL::add: " << integer << std::endl;
    root = privateAdd(this->root, integer);
    //validate(root);
    //std::cout << "tree after add: " << *this << std::endl;
}

// recursively traverses the tree and adds a node when a spot for it is found
// node is the top of the subtree that could be null
// integer is added to the subtree
// returns new top of the subtree (could be unchanged)
DLnode* AVL::privateAdd(DLnode* node, const int integer)
{
    if(node == NULL)
    {
        ++comparisons;
        node = new DLnode(integer);
        node->height = 1;
    }
    else if(node->value > integer)
    {
        ++comparisons;
        node->left = privateAdd(node->left, integer);
        int balance = node->updateBalance();
        if(balance > 1)
        {
            node = rebalanceSubtree(node); //topnode of subtree is changed
        }
    }
    else if(node->value < integer)
    {
        ++comparisons;
        node->right = privateAdd(node->right, integer);
        int balance = node->updateBalance();
        if(balance < -1)
        {
            node = rebalanceSubtree(node); //topnode of subtree is changed
        }
    }
    return node;
}

void AVL::printNode(DLnode* node) const
{
    std::cout << "node: " << node->value << " balance: " << node->getBalance() <<
    " height: " << node->height << std::endl;
}

// exchanges node with left child, left child is on top of node after the operations
// returns new top of the subtree with subtree updated
DLnode* AVL::rotateWithLeftChild(DLnode* node)
{
    DLnode* oldLeft = node->left;
    node->left = oldLeft->right;
    oldLeft->right = node; // old left goes on top of node
    node->updateBalance();
    oldLeft->updateBalance();
    return oldLeft;
}

// exchanges node with right child, right child is on top of node after the operations
// returns new top of the subtree with subtree updated
DLnode* AVL::rotateWithRightChild(DLnode* node)
{
    DLnode* oldRight = node->right;
    node->right = oldRight->left;
    oldRight->left = node;
    node->updateBalance();
    oldRight->updateBalance();
    return oldRight;
}

// returns new top of the subtree after double rotation and subtree updated
DLnode* AVL::doubleRotateWithLeftChild(DLnode* node)
{
    node->left = rotateWithRightChild(node->left);
    node->updateBalance();
    return rotateWithLeftChild(node);
}

// returns new top of the subtree after double rotation and subtree updated
DLnode* AVL::doubleRotateWithRightChild(DLnode* node)
{
    node->right = rotateWithLeftChild(node->right);
    node->updateBalance();
    return rotateWithRightChild(node);
}

DLnode* AVL::search(const int integer)
{
    DLnode* temp = root;
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

void AVL::remove(const int integer)
{
    root = privateRemove(root, integer);
    /*if(root)
    {
        validate(root);
    }*/
    //std::cout << "after removal: " << *this << std::endl;
}

// removes integer and rebalances subtree defined by node
// returns new top of the subtree
DLnode* AVL::privateRemove(DLnode* node, const int integer)
{
    if(node)
    {
        if(node->value < integer)
        {
            ++comparisons;
            node->right = privateRemove(node->right, integer);
        }
        else if(node->value > integer)
        {
            ++comparisons;
            node->left = privateRemove(node->left, integer);
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
        if(node)
        {
            int balance = node->updateBalance();
            if(balance < -1 || balance > 1)
            {
                node = rebalanceSubtree(node); //topnode of subtree is changed
            }
        }
    }
    else
    {
        //std::cout << "Value " << integer << " not found" << std::endl;
    }
    return node;
}

// removes minimum element from the subtree defined by node
// modifies the node to be node->right
// returns the original node address
DLnode* AVL::removeMin(DLnode*& node)
{
    if(node)
    {
        if(node->left)
        {
            DLnode* temp = removeMin(node->left); // keep moving left because min node is always on the left side of the subtree
            int balance = node->updateBalance();
            if(balance < -1) // balance can only tip over to the right side
            {
                node = rebalanceSubtree(node); //topnode of subtree is changed
            }
            return temp;
        }
        else
        {
            DLnode* temp = node; //temp stores node address to be returned because node will be changed
            node = node->right; //node is being changed to node->right so whoever was pointing to node now points to node->right
            temp->right = nullptr; //this node has no children anymore
            temp->height = 0; // just for safety so previous value is not used
            return temp; //return address of node
        }
    }
    else
    {
        throw std::logic_error("cannot call removeMin on null node");
    }
}

// returns node that is new top of subtree
// assuming that a single leaf is causing the imbalance
DLnode* AVL::rebalanceSubtree(DLnode* node)
{
    int balance = node->getBalance();
    /**
     Four cases:
     1. Insertion into left subtree of the leftChild of thisNode
     2. Insertion into the right subtree of the leftChild of thisNode
     3. Insertion into the left subtree of the rightChild of thisNode
     4. Insertion into the right subtree of the rightChild of thisNode
     
     These cases do not cover removal cases (see wikipedia for full set of rules)
     */
    
    //std::cout << "node: " << node->value << " balance: " << balance << std::endl;
    
    if(balance > 1) // case 1 and 2
    {
        // Have a left child
        int left_balance = node->left->getBalance();
        
        // if left node is also unbalanced, traversing further until child is balanced
        if(left_balance > 1 || left_balance < -1)
        {
            // must keep searching because imbalance is still high
            node->left = rebalanceSubtree(node->left);
            node->updateBalance();
        }
        // consider two cases:
        // 1. leftChild of this node should not be right-heavy
        // i.e. left imbalance should not be to the right side
        // see wikipedia
        else if(left_balance >= 0)
        {
            node = rotateWithLeftChild(node); // returns updated subtree
        }
        // 2. right subtree of the leftChild of this node is heavy
        else
        {
            node = doubleRotateWithLeftChild(node); // returns updated subtree
        }
    }
    else if(balance < -1) // case 4 and 3
    {
        // Have a right child
        int right_balance = node->right->getBalance();
        
        // if right node is also unbalanced, traversing further until child is balanced
        if(right_balance > 1 || right_balance < -1)
        {
            // must keep searching because imbalance is still high
            node->right = rebalanceSubtree(node->right);
            node->updateBalance();
        }
        // consider two cases:
        // 4. rightChild of this node should not be left-heavy
        // i.e. right imbalance should not be to the left side
        // see wikipedia
        else if(node->right->getBalance() <= 0)
        {
            node = rotateWithRightChild(node); // returns updated subtree
        }
        // 3. left subtree of the rightChild of this node is heavy
        else
        {
            node = doubleRotateWithRightChild(node); // returns updated subtree
        }
    }
    return node;
}

// validates that all heights are correct
void AVL::validate(DLnode* node)
{
    if(node->left)
    {
        validate(node->left);
    }
    if(node->right)
    {
        validate(node->right);
    }
    int test_height = node->height;
    int balance = node->updateBalance();
    if(test_height != node->height)
    {
        std::cout << "Node: " << node->value << " Height was: " << test_height << " became: "
        << node->height << std::endl;
        throw std::logic_error("AVL::validate: validation of height failed");
    }
    if(balance < -1 || balance > 1)
    {
        throw std::logic_error("AVL::validate: unbalanced tree");
    }
}

#endif /* avl_h */
