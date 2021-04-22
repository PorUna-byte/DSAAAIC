//
//  AVL.hpp
//  AVL_ADT_imp
//The fullname of AVL is Adelson-Velskii and Landis
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp
#include <stdlib.h>
#include <stdio.h>
#include <stack>  //That's why I choose C++ rather than C.
#define ElementType int
using namespace std;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
//N is the number of Nodes in this BST
//Here we assume there is no two different nodes have the same element X!
static int Height(Position P);//O(1)
int HasRight(SearchTree T);//O(1)
int HasLeft(SearchTree T);//O(1)
//Create a node with element X,O(1)
SearchTree CreateNode(ElementType X);
//Dispose a binary search tree,free the space
//O(N)
void DisposeAVL(SearchTree T);
//Find the element X in the BST T,return its position
//NULL,if it does not exist,O(logN)
Position Find(SearchTree T,ElementType X);
//Find the minimum element of the BST T
//return its position,O(logN)
Position FindMin(SearchTree T);
//Find the maximum element of the BST T
//return its position,O(logN)
Position FindMax(SearchTree T);
//Find the Path to element X(X itself is not included),O(logN)
//return the path traversed in reverse order.
stack<Position> FindPath(SearchTree T,ElementType X);
//Insert the element X into the BST T
//return the root of the BST after insertion
//O(logN)
SearchTree Insert(SearchTree T,ElementType X);
//Delete the element X from the BST T,O(logN)
//if X doesn't ,do nothing
//return the root of the BST after deletion
SearchTree Delete(SearchTree T,ElementType X);
//PreOrder traverse the BST T,O(N)
void PreOrder(SearchTree T);
//InOrder traverse the BST T,O(N)
void InOrder(SearchTree T);
//PostOrder traverse the BST T,O(N)
void PostOrder_recursive(SearchTree T);
void PostOrder_nonrecursive(SearchTree T);
//This function can be called only if K2 has a left child
//Perform a rotate between a node(K2) and its left child
//update heights,then return new root,O(1)
static Position SingleRotateWithLeft(Position K2);
//This function can be called only if K2 has a right child
//Perform a rotate between a node(K2) and its right child
//update heights,then return new root,O(1)
static Position SingleRotateWithRight(Position K2);
//This function can be called only if K3 has a left child
//and K3's left child has a right child
//Do the left-right double rotation
//update heights,then return new root,O(1)
static Position DoubleRotateWithLeft(Position K3);
//This function can be called only if K3 has a right child
//and K3's right child has a left child
//Do the right-left double rotation
//update heights,then return new root,O(1)
static Position DoubleRotateWithRight(Position K3);
//fix the tree after insertion or deletion if necessary
static void fix_tree(SearchTree &T,stack<Position> &sta);
struct TreeNode{
    ElementType element;
    SearchTree left;
    SearchTree right;
    int height;
};
#endif /* AVL_hpp */
