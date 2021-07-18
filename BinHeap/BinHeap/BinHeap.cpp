//
//  BinHeap.c
//  BinHeap
//  This Heap is a minimum heap
//  Created by PorUnaCabeza on 2021/6/24.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#ifndef BinHeap_cpp
#define BinHeap_cpp
#include "BinHeap.hpp"
int IsEmpty(PriorityQueue H)
{
    return H->Size==0;
}
int IsFull(PriorityQueue H)
{
    return H->Size==H->Capacity;
}
void oom()
{
   printf("Out of memory");
    exit(-1);
}
PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H=(PriorityQueue)malloc(sizeof(struct HeapStruct));
    if(!H)
        oom();
    H->Elements=(Elestu*)malloc(sizeof(Elestu)*(MaxElements+1));//One more space for sentinel
    if(!H->Elements)
        oom();
    H->Capacity=MaxElements;
    H->Size=0;
    H->Elements[0].key=Sentinel;
    for(int i=0;i<H->Capacity+1;i++)
        H->Elements[i].element=(Edge*)malloc(sizeof(Edge));
    return H;
}
//O(logN)
static void Percolate_up(PriorityQueue &H,int Position, KeyType new_key) {
    int i;
    Edge* posele=H->Elements[Position].element;
    for(i=Position;H->Elements[i/2].key>new_key;i/=2)//Note that H->elements[i/2] is the parent of H->elements[i]
    {
        H->Elements[i].key=H->Elements[i/2].key;
        H->Elements[i].element=H->Elements[i/2].element;
    }
    H->Elements[i].key=new_key;
    H->Elements[i].element=posele;
}

void Insert(Elestu* X,PriorityQueue H)//O(logN)
{
    if(IsFull(H))
    {
        printf("PriorityQueue is Full\n");
        return ;
    }
    //percolate up to find the approprite space for X
    ++H->Size;
    H->Elements[H->Size].element=X->element;
    H->Elements[H->Size].key=X->key;
    Percolate_up(H,++H->Size,X->key);
    return ;
}
//O(logN)
static void Percolate_down(PriorityQueue H, int Position, KeyType new_key) {
    int child,i;
    Edge* posele=H->Elements[Position].element;
    for(i=Position;i*2<=H->Size;i=child)//Loop until the approprite position has been found
    {
        child=i<<1;
        //Find smaller children
        if(child!=H->Size&&H->Elements[child+1].key<H->Elements[child].key)
            child++;
        //percolate one level down
        if(H->Elements[child].key<new_key)
        {
            H->Elements[i].key=H->Elements[child].key;
            H->Elements[i].element=H->Elements[child].element;
        }
        else
            break;
    }
    H->Elements[i].key=new_key;
    H->Elements[i].element=posele;
}
Edge* DeleteMin(PriorityQueue H)
{
    int victim;
    Edge* Min;
    if(IsEmpty(H))
    {
        printf("PriorityQueue is Empty\n");
        return NULL;
    }
    Min=H->Elements[1].element;
    H->Elements[1].element=H->Elements[H->Size].element;
    victim=H->Elements[H->Size--].key;
    Percolate_down(H, 1, victim);
    return Min;
}
void UpdateKey(PriorityQueue H,int Position,KeyType new_key)
{
    if(H->Elements[Position].key<new_key) //Increase the key, we need to percolate down
        Percolate_down(H, Position, new_key);
    else if(H->Elements[Position].key>new_key) //Decrease the key, we need to percolate up.
        Percolate_up(H, Position, new_key);
}
void BuildHeap(PriorityQueue H)
{
    for(int i=H->Size/2;i>0;i--)
        Percolate_down(H, i, H->Elements[i].key);
}
#endif
