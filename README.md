# Self-Balancing Binary Search Trees

A comparative study of three binary search tree implementations in C++, analyzing their performance characteristics through insertion, search, and deletion operations.

## Overview

This project implements and compares three tree data structures:

| Data Structure | Description | Balance Strategy |
|----------------|-------------|------------------|
| **BST** | Basic Binary Search Tree | None (can become unbalanced) |
| **AVL Tree** | Adelson-Velsky and Landis Tree | Height-balanced with rotations |
| **Splay Tree** | Self-adjusting BST | Move accessed nodes to root |

## File Structure

```
p2/
├── main.cpp        # Driver program
├── node.h          # Basic tree node (for BST)
├── DLnode.h        # Doubly-linked node with parent pointer (for AVL/Splay)
├── binary.h        # Binary Search Tree implementation
├── avl.h           # AVL Tree implementation
├── splay.h         # Splay Tree implementation
├── Makefile        # Build configuration
└── p2_test*.txt    # Test input files
```

## Data Structures

### Binary Search Tree (BST)
A standard BST with no self-balancing. Provides O(log n) average-case operations but can degrade to O(n) with sorted input.

**Operations:**
- `add(int)` - Insert a value
- `search(int)` - Find a value
- `remove(int)` - Delete a value

### AVL Tree
A self-balancing BST that maintains a balance factor (height difference between subtrees) of at most 1.

**Key Features:**
- Height tracking per node
- Four rotation types to restore balance:
  - Single right rotation
  - Single left rotation  
  - Double rotation (left-right)
  - Double rotation (right-left)

**Balance Factor:** `left_height - right_height` must be in {-1, 0, 1}

### Splay Tree
A self-adjusting BST that moves recently accessed elements to the root via "splaying."

**Splaying Operations:**
| Case | Description | Operation |
|------|-------------|-----------|
| **Zig** | Node is child of root | Single rotation |
| **Zig-Zig** | Node and parent are both left (or both right) children | Two same-direction rotations |
| **Zig-Zag** | Node is left child of right child (or vice versa) | Two opposite-direction rotations |

## Building

```bash
# Compile the project
make

# Or compile manually
g++ -std=c++11 -Wall -g main.cpp -o p2
```

## Usage

```bash
./p2 <input_file>
```

### Input File Format

The input file has three sections separated by `$`:

```
<integers to insert>
$
<integers to search>
$
<integers to remove>
```

**Example** (`p2_test0.txt`):
```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
$
5 4 3 5 7 13
$
11 6 7 2 12 6
```

### Output

The program outputs:
1. Tree structure after insertions (with comparison counts)
2. Splay tree structure after searches (demonstrates splaying)
3. All tree structures after removals
4. Total comparison counts for each tree type

**Tree notation:** `[root[left][right]]` where empty subtrees are `[]`

## Example Run

```bash
$ ./p2 p2_test0.txt

Binary tree: [1[][2[][3...]]] comparisons: 120
AVL tree: [8[4[2[1][3]][6[5][7]]][12[10[9][11]][14[13][15]]]] comparisons: 45
Splay tree: [15[14[13...]]] comparisons: 58

POST SEARCHES
Splay tree: [13[5[3[1][4]][7]][14[][15]]]

POST REMOVALS
Binary tree: [1[][3[][4...]]]
AVL tree: [8[4[1[][3]][5]][13[10[9][]][14[][15]]]]
Splay tree: [15[14[13[10[9][]][]]]]

TOTAL COMPARISONS
Binary comparisons: 156
AVL comparisons: 78
Splay comparisons: 112
```

## Algorithm Complexity

| Operation | BST (avg/worst) | AVL | Splay (amortized) |
|-----------|-----------------|-----|-------------------|
| Insert | O(log n) / O(n) | O(log n) | O(log n) |
| Search | O(log n) / O(n) | O(log n) | O(log n) |
| Delete | O(log n) / O(n) | O(log n) | O(log n) |

## Implementation Details

### AVL Rotations

```
Right Rotation (when left-heavy):     Left Rotation (when right-heavy):

      y                 x                  x                  y
     / \               / \                / \                / \
    x   C    -->      A   y              A   y      -->     x   C
   / \                   / \                / \            / \
  A   B                 B   C              B   C          A   B
```

### Splay Tree - Zig-Zig vs Zig-Zag

**Zig-Zig** (node and parent are same-side children):
```
      g              p              x
     /              / \              \
    p      -->     x   g    -->       p
   /                                   \
  x                                     g
```

**Zig-Zag** (node and parent are opposite-side children):
```
    g                g                x
   /                /                / \
  p        -->     x        -->     p   g
   \              /
    x            p
```

## Cleaning Up

```bash
make clean    # Remove compiled files
make submit   # Create submission zip
```

## Author

Anastasia Nesterova  
Georgetown University  
Data Structures - Fall 2019

## References

- Weiss, M. A. *Data Structures and Algorithm Analysis in C++*
- [AVL Tree - Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)
- [Splay Tree - Wikipedia](https://en.wikipedia.org/wiki/Splay_tree)
