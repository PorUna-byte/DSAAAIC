//
//  Queue_imp.c
//  Queue_imp
//
//  Created by PorUnaCabeza on 2021/3/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Queue_ADT.h"
#define MinQueueSize 5
struct QueueRecord{
    int Front;
    int Rear;
    int Capacity;
    int Size;
    ElementType* Array;
};
int IsEmpty(Queue Q)
{
    return Q->Size==0;
}
int IsFull(Queue Q)
{
    return Q->Size==Q->Capacity;
}
Queue CreateQueue(int MaxElements)
{
    int Capacity=MaxElements>MinQueueSize?MaxElements:MinQueueSize;
    Queue new_Queue=(Queue)malloc(sizeof(struct QueueRecord));
    if(new_Queue==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    new_Queue->Array=(ElementType*)malloc(sizeof(ElementType)*Capacity);
    if(new_Queue->Array==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    new_Queue->Capacity=Capacity;
    new_Queue->Size=0;
    new_Queue->Front=0;
    new_Queue->Rear=-1;
    return new_Queue;
}
void DisposeQueue(Queue Q)
{
    free(Q->Array);
    free(Q);
    return ;
}
void MakeEmpty(Queue Q)
{
    Q->Front=0;
    Q->Rear=-1;
    Q->Size=0;
    return ;
}
void Enqueue(ElementType X,Queue Q)
{
    if(IsFull(Q))
    {
        printf("The Queue is already full!\n");
        exit(0);
    }
    Q->Rear=(Q->Rear+1)%Q->Capacity;//Circular array
    Q->Size++;
    Q->Array[Q->Rear]=X;
    return ;
}
ElementType Front(Queue Q)
{
    if(IsEmpty(Q))
    {
        printf("The Queue is Empty");
        exit(0);
    }
    return Q->Array[Q->Front];
}
void Dequeue(Queue Q)
{
    if(IsEmpty(Q))
    {
        printf("The Queue is Empty");
        exit(0);
    }
    Q->Front=(Q->Front+1)%Q->Capacity;//Circular array
    Q->Size--;
    return ;
}
ElementType FrontandDequeue(Queue Q)
{
    ElementType ans=Front(Q);
    Dequeue(Q);
    return ans;
}


