//
//  BinHeap.hpp
//  BinHeap
//
//  Created by PorUnaCabeza on 2021/6/24.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef BinHeap_hpp
#define BinHeap_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../../GraphAlgo/GraphAlgo/Graph.hpp"
#include "../../Disjoint_set/Disjoint_set/Disjoint_set.hpp"
#define Sentinel 1<<31  //let the smallest interger to be sentinel
using namespace std;
typedef int KeyType;
struct HeapStruct;
typedef struct HeapStruct* PriorityQueue;
typedef int Vertex;
typedef struct edge{
    Vertex from;
    Vertex to;
    int weight;
}Edge;
typedef struct ElementStruct{
    KeyType key;
    Edge* element;
}Elestu;
struct HeapStruct
{
    int Capacity;
    int Size;
    Elestu* Elements;
};
PriorityQueue Initialize(int MaxElements);//O(1)
void Insert(Elestu* X,PriorityQueue H);//O(logN)
Edge* DeleteMin(PriorityQueue H);//O(logN)
/*
 Update the Key in position P to the new value "value"
 O(logN)
 */
void UpdateKey(PriorityQueue H,int Position,KeyType new_key);
int IsEmpty(PriorityQueue H);//O(1)
int IsFull(PriorityQueue H);//O(1)
/*
 Although we can build a heap by calling the insert routine repeatedly,
 for efficiency we use a special routine for this function.
 O(N)
 */
void BuildHeap(PriorityQueue H);
#endif /* BinHeap_h */
