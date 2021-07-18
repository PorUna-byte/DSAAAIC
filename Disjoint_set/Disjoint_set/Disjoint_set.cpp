//
//  Disjoint_set.cpp
//  Disjoint_set
//
//  Created by PorUnaCabeza on 2021/7/10.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#ifndef Dis_cpp
#define Dis_cpp
#include "Disjoint_set.hpp"
DisjSet Dis_Initialize(int Num)
{
    DisjSet Diset=(DisjSet)malloc(sizeof(ElementType)*(Num+1));
    if(Diset==NULL)
    {
        printf("out of memory\n");
        exit(-1);
    }
    for(int i=1;i<=Num;i++)
        Diset[i]=-1; //-(-1)=1 is the number of nodes in initial set.
    return Diset;
}
void SetUnion(DisjSet S,SetType root1,SetType root2)
{
    if(root1==root2)  //Already in the same set, nothing need to do.
        return;
    if(S[root2]<=S[root1]) //root2 has more elements than root1
    {
        S[root2]+=S[root1] ; //update root2, since we incorporate root1 into root2
        S[root1]=root2; //let root1 be a subset of root2
    }
    else
    {
        S[root1]+=S[root2] ; //update root1, since we incorporate root2 into root1
        S[root2]=root1; //let root2 be a subset of root1
    }
}
SetType Find(ElementType X,DisjSet S)
{
    if(S[X]<0) //X is the root
        return X;
    else
        return S[X]=Find(S[X], S);//find the root recursively and do path compression.
}
void Show(DisjSet S)
{
    for(int i=1;i<=NumSets;i++)
    {
        if(S[i]<0)
        {
            printf("root %d:",i);
            for(int j=1;j<=NumSets;j++)
            {
                if(Find(j, S)==i)
                    printf("%d\t",j);
            }
            printf("\n");
        }
    }
}
#endif
