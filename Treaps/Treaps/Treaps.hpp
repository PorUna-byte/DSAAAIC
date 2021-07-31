//
//  Treaps.hpp
//  Treaps
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 Treap is so simple, and the time for a single operation is much higher compared with previous balanced trees.
 But it still have O(logN) expected time for each operation !
 We decide to implement the Treap non-recursively for better performance and understanding .
 For more detail, please refer to the paper "Treap.pdf".
 */
#ifndef Treaps_hpp
#define Treaps_hpp

#include <stdio.h>
#include <iostream>

#define KeyType int
#define ElementType int
typedef struct treap
{
    KeyType key;
    ElementType element;
    int priority;
    struct treap* left;
    struct treap* right;
}Treap;
using namespace std;

//Initialize the singleton NullNode.
void Initialize(Treap* &T);
/*Insert a node with key 'key' & element 'element' into the tree
 O(logN) expected time.
 */
Treap* Insert(Treap* T,KeyType key,ElementType element);
/*Delete a node with key 'key' from the tree
 O(logN) expected time.
 */
Treap* Delete(Treap* T,KeyType key,bool& flag);
#endif /* Treaps_hpp */
