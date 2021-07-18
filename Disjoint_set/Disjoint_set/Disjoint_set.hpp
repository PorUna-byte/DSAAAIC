//
//  Disjoint_set.hpp
//  Disjoint_set
//
//Disjoint set is an efficient data structure to solve equivalence problem
//  Created by PorUnaCabeza on 2021/7/10.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.

#ifndef Disjoint_set_hpp
#define Disjoint_set_hpp

#include <stdio.h>
#include <iostream>
#include "../../BinHeap/BinHeap/BinHeap.hpp"
#include "../../GraphAlgo/GraphAlgo/Graph.hpp"
#define NumSets 100
#define Unite(a,b,set) \
SetUnion(set,Find(a,set),Find(b,set))
using namespace std;

typedef int* DisjSet;
typedef int SetType ;
typedef int ElementType;
/*
 Initialize the disjoint set by setting all elements to -1 (the absolute value of which represents the size of corresponding set)
 O(NumSets)
 */
DisjSet Dis_Initialize(int Num);

/*
 Unite two disjoint sets into one set by incorporating the smaller one into the larger one.
 O(1), Union by size
 */
void SetUnion(DisjSet S,SetType root1,SetType root2);

/*
 Find the set which contains element X while using path compression strategy.
 The effect of path compression is that every node on the path from X to the root has its parent changed to the root.
 Path compression is perfectly compatible with union-by-size(which we use above)
 Theorem:Any sequence of M=\Omega(N) (M is the number of union operations, N is the number of Find operations)
 take a total of O(Mlog*N) running time (log*N is the number of times the logarithm of N needs to be applied until result <=1, eg log*65536=4 since loglogloglog65536=1)
 */
SetType Find(ElementType X,DisjSet S);
void Show(DisjSet S);
#endif /* Disjoint_set_hpp */
