//
//  Binomial_Queue.hpp
//  Binomial_Queue
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Binomial_Queue_hpp
#define Binomial_Queue_hpp

#include <stdio.h>
#include <stdlib.h>
typedef struct BinNode* Position;
typedef struct Collection* BinQueue;
typedef Position BinTree;
#define MaxTrees 10
#define Capacity (1<<(MaxTrees-1))
#define ElementType int
#define Insert(H,X) (H=Insert_(H,X))
#define DeleteMin(H) (H=DeleteMin_(H))
BinQueue Initialize();
BinQueue Merge(BinQueue H1,BinQueue H2);//O(logN)
BinQueue DeleteMin_(BinQueue H);//O(logN)
BinQueue Insert_(BinQueue H,ElementType X);//O(logN)
#endif /* Binomial_Queue_hpp */
