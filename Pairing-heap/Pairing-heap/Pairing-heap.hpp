//
//  Pairing-heap.hpp
//  Pairing-heap
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
//For more detail, please refer to the paper "pairing-heaps".
#ifndef Pairing_heap_hpp
#define Pairing_heap_hpp

#include <stdio.h>
#include <iostream>
#define KeyType int
#define ElementType int
using namespace std;
typedef struct pnode{
    KeyType key;
    ElementType element;
    struct pnode* LeftChild;
    struct pnode* NextSibling;
    struct pnode* Prev;
}PairNode;
typedef PairNode* Position;
typedef Position PairHeap;
/*
 This is the basic operation to maintain order.
 Links first and second together to satisfy heap order.
 Returns the resulting tree.
 First is assumed NOT NULL.
 First->NextSibling Must be NULL on entry.
 O(1)
 */
Position CompareAndLink(Position first,Position second);

/*
 Insert Item into pairing heap H.
 Return resulting pairing heap.
 A reference to the newly allocated node is passed back by reference and accessed as Loc.
 O(1)
 */
PairHeap Insert(KeyType key,ElementType element,PairHeap H,Position &Loc);

/*
 Lower item in Position P by Delta.
 O(1)
 */
PairHeap DecreaseKey(Position P,KeyType Delta,PairHeap H);
/*
 Delete the node with Minimum key from heap(which is the root of minimum heap)
 O(|Children|)
 */
PairHeap DeleteMin(KeyType &MinKey,PairHeap H);

/*
 A helper routine for DeleteMin .
 It combines all children of the deleted node.
 */
PairHeap CombineSiblings(Position FirstSibling);
#endif /* Pairing_heap_hpp */
