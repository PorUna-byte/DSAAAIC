//
//  B_tree.hpp
//  B_tree
//
//  Created by PorUnaCabeza on 2021/4/1.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef B_tree_hpp
#define B_tree_hpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
using namespace std;
#define ElementType int
using namespace std;
struct BTreeNode;
typedef struct BTreeNode *BTree;
typedef BTree Position;
//Insert Element X into BTree T
BTree Insert(ElementType X,BTree T);
//Delete an element X from BTree T
BTree Delete(ElementType X ,BTree T);
//Print the tree level by level
void Print_Tree(Position root);
#endif /* B_tree_hpp */
