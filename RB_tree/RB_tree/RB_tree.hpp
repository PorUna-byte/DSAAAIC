//
//  RB_tree.hpp
//  RB_tree
//
//  Created by PorUnaCabeza on 2021/7/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 A red-black tree is a binary tree that satisfy the following red-black properties:
 1.Every node is either red or black
 2.The root is black
 3.Every leaf(nil) is black
 4.If a node is red, then both its children are black.(Node that two red nodes can not be adjacent,but black nodes can
 adjacent to red node or black node.)
 5.For each node, all simple paths from the node to descendent leaves contain the same number of black nodes.
 Hence, we can define black-height of a node to be this number.
 
 For 3 insertion cases , please refer to insertion_case.jpg
 For 4 deletion cases , please refer to deletion_case.jpg
 Lemma:A red-black tree with n internal nodes has height at most 2lg(n+1)
 */
#ifndef RB_tree_hpp
#define RB_tree_hpp
#include <iostream>
#include <stdio.h>
#define KeyType int
#define ElementType int
#define sentinel 1<<31  //the smallest interger
using namespace std;
enum Color{red,black};
typedef struct node{ //A tree node
    enum Color color; //black or red
    KeyType key;
    ElementType element;
    struct node* left;
    struct node* right;
    struct node* parent;
}Node;
typedef struct tree{
    Node* root; //the root of RB tree
    Node* nil;  //the leaf of RB tree
}Tree;
/*
 Initialize a red black tree
 O(1)
 */
Tree* Init_RBT();
/*
 Insert a node into RBT
 O(logn)
 */
void Insert(Tree* T,KeyType key,ElementType element);

/*
 Delete a node by Key
 O(logn)
 */
void Delete(Tree* T,KeyType key);
/*
 print the red black tree level by level.
 */
void Print_tree(Tree* T);
/*
 This function verify wheather a tree is a red-black tree.
 We only verify the property 2,4,5 .since the property 1,3 is obvious held.
 */
bool verify_RBT(Tree* T);
#endif /* RB_tree_hpp */
