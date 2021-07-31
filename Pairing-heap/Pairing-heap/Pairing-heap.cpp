//
//  Pairing-heap.cpp
//  Pairing-heap
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#define MaxSiblings 1000
#include "Pairing-heap.hpp"
void oom(){
    printf("out of memory\n");
    exit(-1);
}
void *Malloc(size_t size)//A simple warpper to simplify the code
{
    void *ptr=malloc(size);
    if(ptr==NULL)
        oom();
    return ptr;
}
Position CompareAndLink(Position first,Position second)
{
    if(second==NULL)
        return first;
    else if(first->key<=second->key)
    {
        second->Prev=first;
        first->NextSibling=second->NextSibling;
        if(first->NextSibling!=NULL)
            first->NextSibling->Prev=first;
        second->NextSibling=first->LeftChild;
        if(second->NextSibling!=NULL)
            second->NextSibling->Prev=second;
        first->LeftChild=second;
        return first;
    }
    else
    {
        second->Prev=first->Prev;
        first->Prev=second;
        first->NextSibling=second->LeftChild;
        if(first->NextSibling!=NULL)
            first->NextSibling->Prev=first;
        second->LeftChild=first;
        return second;
    }
}
PairHeap Insert(KeyType key,ElementType element,PairHeap H,Position &Loc)
{
    Position NewNode=(Position)Malloc(sizeof(PairNode));
    NewNode->key=key;
    NewNode->element=element;
    NewNode->Prev=NewNode->NextSibling=NewNode->LeftChild=NULL;
    Loc=NewNode;
    if(H==NULL)
        return NewNode;
    else
        return CompareAndLink(H, NewNode);
}
/*
 We disconnected the node that modified first and reconnect it later.
 */
PairHeap DecreaseKey(Position P,KeyType Delta,PairHeap H)
{
    if(Delta<0)
    {
        cout<<"Error:DecreaseKey called with negative Delta"<<endl;
        return H;
    }
    P->key-=Delta;
    if(P==H)
        return H;
    if(P->NextSibling!=NULL)
        P->NextSibling->Prev=P->Prev;
    if(P->Prev->LeftChild==P) //P is the left child of its prev
        P->Prev->LeftChild=P->NextSibling;
    else
        P->Prev->NextSibling=P->NextSibling;
    P->NextSibling=NULL;
    P->Prev=NULL;
    return CompareAndLink(H, P);
}
PairHeap CombineSiblings(Position FirstSibling)
{
    static Position TreeArray[MaxSiblings];
    int i,j,NumSiblings;
    
    if(FirstSibling->NextSibling==NULL)
        return FirstSibling;
    for(NumSiblings=0;FirstSibling!=NULL;NumSiblings++)
    {
        TreeArray[NumSiblings]=FirstSibling;
        FirstSibling->Prev->NextSibling=NULL; //break links
        FirstSibling=FirstSibling->NextSibling;
    }
    TreeArray[NumSiblings]=NULL;
    for(i=0;i+1<NumSiblings;i+=2)
    {
        TreeArray[i]=CompareAndLink(TreeArray[i], TreeArray[i+1]);
    }
    j=i-2;
    if(j==NumSiblings-3)//if an odd number of trees, get the last one.
        TreeArray[j]=CompareAndLink(TreeArray[j], TreeArray[j+2]);
    //Now go right to left, merging last tree with next to last.
    for(;j>=2;j-=2)
        TreeArray[j-2]=CompareAndLink(TreeArray[j-2], TreeArray[j]);
    
    return TreeArray[0];
}
PairHeap DeleteMin(KeyType &MinKey,PairHeap H)
{
    Position NewRoot=NULL;
    if(H==NULL)
    {
        cout<<"Pairing Heap is empty"<<endl;
        return H;
    }
    else
    {
        MinKey=H->key;
        if(H->LeftChild!=NULL)
            NewRoot=CombineSiblings(H->LeftChild);
        free(H);
    }
    return NewRoot;
}
