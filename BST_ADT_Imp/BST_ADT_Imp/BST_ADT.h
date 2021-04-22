//
//  BST_ADT.h
//  BST_ADT_Imp
//
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef BST_ADT_h
#define BST_ADT_h

#include <stdlib.h>
#include <stdio.h>
#define ElementType int
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
//N is the number of Nodes in this BST
//Here we assume there is no two different nodes have the same element X!

//Dispose a binary search tree,free the space
//O(1)
void DisposeBST(SearchTree T);
//Find the element X in the BST T,return its position
//NULL,if it does not exist,O(logN)
Position Find(SearchTree T,ElementType X);
//Find the minimum element of the BST T
//return its position,O(logN)
Position FindMin(SearchTree T);
//Find the maximum element of the BST T
//return its position,O(logN)
Position FindMax(SearchTree T);
//Find the parent of element X,O(logN)
//if X does not exist,return the last spot on the path traversed.
//if X is the root ,return NULL
Position FindParent(SearchTree T,ElementType X);
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
void PostOrder(SearchTree T);
#endif /* BST_ADT_h */
