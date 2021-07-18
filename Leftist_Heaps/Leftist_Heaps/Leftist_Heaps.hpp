//
//  Leftist_Heaps.hpp
//  Leftist_Heaps
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Leftist_Heaps_hpp
#define Leftist_Heaps_hpp

#include <stdio.h>
#include <stdlib.h>
#define ElementType int
struct TreeNode;
typedef struct TreeNode* PriorityQueue;
/*
 Minimal set of priority queue operations
 Note that nodes will be shared among several
 leftist heaps after a merge;the user must
 make sure to not use the old leftist heaps.
 */
PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2);
PriorityQueue Insert_(ElementType X,PriorityQueue H);
PriorityQueue DeleteMin_(PriorityQueue H);
#define Insert(X,H) (H=Insert_(X,H))
#define DeleteMin(H) (H=DeleteMin_(H))
#endif /* Leftist_Heaps_hpp */
