//
//  Splay_ADT.h
//  Splay_tree_topdown
//
//  Created by PorUnaCabeza on 2021/3/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Splay_ADT_h
#define Splay_ADT_h
#define ElementType int
#include <stdio.h>
#include <stdlib.h>

struct SplayNode;
typedef struct SplayNode *SplayTree;
typedef struct SplayNode *Position;
//Initialize a tree,O(1)
SplayTree Initialize(void);
//Splay the tree rooted at X for the item Item.
SplayTree Splay(ElementType Item,Position X);
//M consecutive tree operations as following from an empty tree takes O(MlogN) time
//So amortized time for each operation is O(logN),where N is the number of nodes in the tree
SplayTree Find(ElementType Item,SplayTree T);//Splay the tree first,if the root is X
//then we have found it or not
SplayTree Insert(ElementType Item,SplayTree T);//Splay the tree first,We insert X as the root of
//the tree if the root has not item X.
SplayTree Remove(ElementType Item,SplayTree T);//Splay the tree first,We remove the root of
//the tree if the root has item X.
#endif /* Splay_ADT_h */
