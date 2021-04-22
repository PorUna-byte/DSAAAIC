//
//  Queue_ADT.h
//  Queue_ADT_imp
//
//  Created by PorUnaCabeza on 2021/3/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef _Queue_h
#define _Queue_h

#include <stdlib.h>
#include <stdio.h>
#define ElementType int
struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);//O(1)
int IsFull(Queue Q);//O(1)
//Create a queue with the max elements of MaxElements,O(1)
Queue CreateQueue(int MaxElements);
//Dispose a Queue,free space,O(1)
void DisposeQueue(Queue Q);
//Empty a Queue,O(1)
void MakeEmpty(Queue Q);
void Enqueue(ElementType X,Queue Q);//O(1)
ElementType Front(Queue Q);//O(1)
void Dequeue(Queue Q);//O(1)
ElementType FrontandDequeue(Queue Q);//O(1)
#endif
