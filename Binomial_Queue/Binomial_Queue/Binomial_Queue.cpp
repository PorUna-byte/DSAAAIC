//
//  Binomial_Queue.cpp
//  Binomial_Queue
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Binomial_Queue.hpp"
#include <iostream>
using namespace std;
struct BinNode
{
    ElementType Element;
    Position LeftChild;
    Position NextSibling;
};
struct Collection
{
    int CurrentSize;
    BinTree TheTrees[MaxTrees];
};
void oom()
{
    printf("out of memory.\n");
    exit(-1);
}
/*
 This routine combines two Bintree with the same height
 */
BinTree CombineTrees(BinTree T1,BinTree T2)
{
    if(T1->Element>T2->Element)//Make sure T1 has smaller root
        swap(T1, T2);
    T2->NextSibling=T1->LeftChild;
    T1->LeftChild=T2;
    return T1;
}
/*
 Merge two binomial queues
 H1 contains merged result
 */
BinQueue Merge(BinQueue H1,BinQueue H2)
{
    if(!H2)
        return H1;
    if(!H1)
        return H2;
    BinTree T1,T2,Carry=NULL;
    int i,j;
    if(H1->CurrentSize+H2->CurrentSize>Capacity)
    {
        printf("Merge would exceed capacity\n");
        exit(-1);
    }
    H1->CurrentSize+=H2->CurrentSize;//Note that the merged
    //result will be contained in H1
    //Note that we can finish the merge routine in
    //atmost logN +1 iterations
    for(i=0,j=1;j<=H1->CurrentSize;i++,j*=2)
    {
        T1=H1->TheTrees[i];
        T2=H2->TheTrees[i];
        //Here is a simple technique which consider all possible
        //conditions. Note that if T1!=NULL then !!T1 is 1
        switch (!!T1+2*!!T2+4*!!Carry) {
            case 0: //No trees
            case 1: //only T1 is not NULL
                //do nothing
                break;
            case 2://only T2 is not NULL
                H1->TheTrees[i]=T2;
                H2->TheTrees[i]=NULL;
                break;
            case 3://T1 and T2 is not NULL
                H1->TheTrees[i]=H2->TheTrees[i]=NULL;
                Carry=CombineTrees(T1, T2);
                break;
            case 4://only carry
                H1->TheTrees[i]=Carry;
                Carry=NULL;
                break;
            case 5://T1 and carry
                H1->TheTrees[i]=NULL;
                Carry=CombineTrees(T1, Carry);
                break;
            case 6://T2 and carry
                H2->TheTrees[i]=NULL;
                Carry=CombineTrees(T2, Carry);
                break;
            case 7://T1 ,T2, Carry
                H1->TheTrees[i]=Carry;
                H2->TheTrees[i]=NULL;
                Carry=CombineTrees(T1, T2);
                break;
        }
    }
    return H1;
}
BinQueue Initialize()
{
    BinQueue binqueue=(BinQueue)malloc(sizeof(struct Collection));
    if(!binqueue)
        oom();
    binqueue->CurrentSize=0;
    memset(binqueue->TheTrees, 0, MaxTrees*sizeof(void*));
    return binqueue;
}
BinQueue Insert_(BinQueue H,ElementType X)
{
    BinQueue SingleNode=Initialize();
    SingleNode->CurrentSize=1;
    SingleNode->TheTrees[0]=(BinTree)malloc(sizeof(struct BinNode));
    if(!SingleNode->TheTrees[0])
        oom();
    SingleNode->TheTrees[0]->Element=X;
    SingleNode->TheTrees[0]->LeftChild=
    SingleNode->TheTrees[0]->NextSibling=NULL;
    return Merge(H, SingleNode);
}
int IsEmpty(BinQueue H)
{
    return H->CurrentSize==0;
}
BinQueue DeleteMin_(BinQueue H)
{
    int i,j;
    int MinTree=0; //The index of the tree with the minimum root
    BinQueue DeletedQueue;
    Position DeletedTree,oldRoot;
    if(IsEmpty(H))
    {
        printf("Empty binomial queue\n");
        exit(-1);
    }
    for(i=0;i<MaxTrees;i++)
    {
        if(H->TheTrees[i]&&
           (!H->TheTrees[MinTree]||H->TheTrees[i]->Element<H->TheTrees[MinTree]->Element))
            MinTree=i;
    }
    DeletedTree=H->TheTrees[MinTree];
    oldRoot=DeletedTree;
    DeletedTree=oldRoot->LeftChild;
    printf("DeleteMin:%d\n",oldRoot->Element);
    free(oldRoot);
    DeletedQueue=Initialize();
    DeletedQueue->CurrentSize=(1<<MinTree)-1;
    for(j=MinTree-1;j>=0;j--)
    {
        DeletedQueue->TheTrees[j]=DeletedTree;
        DeletedTree=DeletedTree->NextSibling;
        DeletedQueue->TheTrees[j]->NextSibling=NULL;
    }
    H->CurrentSize-=1<<MinTree;
    H->TheTrees[MinTree]=NULL;
    return Merge(H, DeletedQueue);
}
