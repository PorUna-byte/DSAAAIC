//
//  ADT.h
//  ListADT_imp_app
//  the ADT for LinkedList,n is the size of List
//  Created by PorUnaCabeza on 2021/3/11.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#ifndef _LIST_H
#define ElementType PtrToPoly_element
#include <stdio.h>
#include <stdlib.h>
struct Node;
struct List;
struct Poly_element;
typedef struct List *Listptr;
typedef struct Node *PtrToNode;
typedef struct Poly_element *PtrToPoly_element;
typedef PtrToNode Position;
struct Node {
    ElementType element;
    PtrToNode next;
};
struct List {
    Position Head;
    Position Last;
};
struct Poly_element {
    float coff;
    int exp;
};
//Create an empty List,O(1)
Listptr MakeEmpty(void);

int IsEmpty(Listptr L);//O(1)
int IsLast(Position P);//O(1)

//Find the first Position of X in List L,null if not exist,O(n)
Position Find(ElementType X,Listptr L);

//Delete the first ouccurence of X in List L,do nothing if not exist,O(n)
//if delete an element return true(1),or false(0).
int Delete_by_ele(ElementType X,Listptr L);
//Delete the  element after Position P in List L,O(1)
//if delete an element return true(1),or false(0).
int Delete_by_pos(Listptr L,Position P);
//Find the previous position of the first occurence of X in L,O(n)
//if X does not exist or X is the first element then return NULL
Position FindPrevious(ElementType X,Listptr L);

//Insert X in List L(non-empty) after the Position P,O(1)
void Insert(ElementType X,Listptr L,Position P);
//Insert X in List L when the List is empty,O(1)
void Insert_first_element(ElementType X,Listptr L);
//Free the memory space of the List,O(n)
void DeleteList(Listptr L);
//Negate the List
void Negative(Listptr L);
//Print out this link from head to tail,O(n)
void PrintLink(Listptr L);
#define _LIST_H
#endif
