//
//  CursorList_imp.c
//  ListADT_imp_app
//
//  Created by PorUnaCabeza on 2021/3/13.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#define Header -1
#define SpaceSize 1000
#include "CursorList_ADT.h"
struct Node{
    ElementType element;
    Position next;
};
struct Node CursorSpace[SpaceSize];
void InitializeCursorSpace(void)
{
    for (int i=0;i<SpaceSize;i++)
        CursorSpace[i].next=i+1;
    CursorSpace[SpaceSize-1].next=0;
}
static Position CursorAlloc()
{
    Position P;
    P=CursorSpace[0].next;
    CursorSpace[0].next=CursorSpace[P].next;
    return P;
}
static void CursorFree(Position P)
{
    CursorSpace[P].next=CursorSpace[0].next;
    CursorSpace[0].next=P;
}
List MakeEmpty(void){
    Position P=CursorAlloc();
    if(P==0)
    {
        printf("Out of Space!\n");
        return -1;
    }
    CursorSpace[P].element=Header;
    return P;
}
int IsEmpty(const List L)
{
    return CursorSpace[L].next==0;
}
int IsLast(const Position P)
{
    return CursorSpace[P].next==0;
}
Position Find(ElementType X,const List L)
{
    Position P=CursorSpace[L].next;
    while(P&&CursorSpace[P].element!=X)
        P=CursorSpace[P].next;
    return P;
}
Position FindPrevious(ElementType X,const List L)
{
        Position P=L;
    while(CursorSpace[P].next&&CursorSpace[CursorSpace[P].next].element!=X)
        P=CursorSpace[P].next;
    return IsLast(P)?0:P;
}
int Delete(ElementType X,const List L)
{
    Position P,TmpCell;
    P=FindPrevious(X,L );
    if(!IsLast(P))
    {
        TmpCell=CursorSpace[P].next;
        CursorSpace[P].next=CursorSpace[TmpCell].next;
        CursorFree(TmpCell);
        return 1;
    }
    return 0;
}
void Insert(ElementType X,Position P)
{
    
    Position new_element=CursorAlloc();
    if(new_element==0){
        printf("Out of Space!\n");
        return ;
    }
    CursorSpace[new_element].element=X;
    CursorSpace[new_element].next=CursorSpace[P].next;
    CursorSpace[P].next=new_element;
}
