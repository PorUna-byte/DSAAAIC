//
//  LinkedList_imp.c
//  ListADT_imp_app
//  The implementation of LinkedList
//  Created by PorUnaCabeza on 2021/3/11.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "LinkedList_ADT.h"
Listptr MakeEmpty(void){
    Listptr L=(Listptr)malloc(sizeof(struct List));
    L->Head=L->Last=NULL;
    return L;
}
int IsEmpty(Listptr L){
    return L->Head==NULL;
}
int IsLast(Position P){
    return P->next==NULL;
}
Position Find(ElementType X,Listptr L)
{
    Position P=L->Head;
    while(P!=NULL&&P->element!=X)
        P=P->next;
    
    return P;
}
Position FindPrevious(ElementType X,Listptr L)
{
    Position P=L->Head;
    if(P==NULL||P->element==X)
        return NULL;
    while(P->next!=NULL&&P->next->element!=X)
        P=P->next;
    return IsLast(P)?NULL:P;
}
int Delete_by_ele(ElementType X,Listptr L)
{
    if(IsEmpty(L))
        return 0;
    Position Q=L->Head;
    if(Q->element==X)
    {
        L->Head=Q->next;
        free(Q->element);
        free(Q);
        return 1;
    }
    Position P=FindPrevious(X, L);
    if(P==NULL) return 0;
    Position Xtmp=P->next;
    P->next=Xtmp->next;
    if(IsLast(Xtmp))
        L->Last=P;
    free(Xtmp->element);
    free(Xtmp);
    return 1;
}
int Delete_by_pos(Listptr L,Position P)
{
    if(P==NULL) return 0;
    Position Xtmp=P->next;
    P->next=Xtmp->next;
    if(IsLast(Xtmp))
        L->Last=P;
    free(Xtmp->element);
    free(Xtmp);
    return 1;
}
void Insert_first_element(ElementType X,Listptr L)
{
    Position THIS=(Position)malloc(sizeof(struct Node));
    THIS->element=X;
    THIS->next=NULL;
    L->Head=L->Last=THIS;
}
void Insert(ElementType X,Listptr L,Position P)
{
    Position tmp=P->next;
    Position THIS=(Position)malloc(sizeof(struct Node));
    if(IsLast(P))
        L->Last=THIS;
    THIS->element=X;
    THIS->next=tmp;
    P->next=THIS;
}
void DeleteList(Listptr L)
{
    Position P=L->Head;
    Position Q=NULL;
    while(P!=NULL)
    {
        Q=P->next;
        free(P->element);
        free(P);
        P=Q;
    }
    free(L);
}
void Negative(Listptr L)
{
    Position A=L->Head;
    while(A!=NULL)
    {
        A->element->coff=-A->element->coff;
        A=A->next;
    }
}
void PrintLink(Listptr L)
{
    Position P=L->Head;
    if(P==NULL)
        printf("0\n");
    while(P!=NULL){
        if(P->next!=NULL)
        printf("(%fx^%d)+",P->element->coff,P->element->exp);
        else
        printf("(%fx^%d)",P->element->coff,P->element->exp);
        P=P->next;
    }
    printf("\n");
}
/*int main(){
    printf("A Test for This imp:\n");
    printf("We insert 3,5,6,9,10,22,7 first\n");
    Listptr list=MakeEmpty();
    Insert_first_element(3, list);
    Insert(5, list, list->Last);
    Insert(6, list, list->Last);
    Insert(9, list, list->Last);
    Insert(10, list, list->Last);
    Insert(22, list, list->Last);
    Insert(7, list, list->Last);
    printf("Now the link looks like:\n");
    PrintLink(list);
    printf("We delete 10,now looks like:\n");
    Delete(10, list);
    PrintLink(list);
    printf("We insert 40 after 6,now looks like:\n");
    Insert(40,list,Find(6, list));
    PrintLink(list);
    DeleteList(list);
    return 0;
}*/
