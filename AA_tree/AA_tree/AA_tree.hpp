//
//  AA_tree.hpp
//  AA_tree
//
//  Created by PorUnaCabeza on 2021/7/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 AA tree is named after its invertor Arne Andersson, please refer to his paper for more detail.
 For your convenience, the paper is included in the directory.
 
 AA tree is a viriation of red black tree.
 We adopt a few rules:
 1.Only right children can be red.
 2.We code our procedures recursively.
 3.Instead of storing a color bit with each node, we store information in a short integer.This information is the level of a node.The level of a node is :
 *One if the node is a leaf.
 *The level of its parent, if the node is red.
 *One less then the level of its parent,if the node is black.
 */
#ifndef AA_tree_hpp
#define AA_tree_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
#define ElementType int
#define KeyType int
typedef struct aanode{
    KeyType key;
    ElementType element;
    struct aanode* Left;
    struct aanode* Right;
    int level;
}AANode,*AATree;
typedef AATree Position;
//Initialize the NullNode
AATree Initialize();
/*
 Insert a new node with key 'key' element 'element' into the AA tree.
 */
AATree Insert(AATree T,KeyType key,ElementType element);
/*
  Remove a node with key 'key' from the AA tree.
 */
AATree Remove(AATree T,KeyType key);

#endif /* AA_tree_hpp */
