//
//  CursorList_ADT.h
//  ListADT_imp_app
//  Created by PorUnaCabeza on 2021/3/13.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef _Cursor_H
#define _Cursor_H
#define ElementType int
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
//Initialize the space for all possible Nodes in all links.
//Emulate the heap in system memory,but the size is constrained.
//It's just like a free "List" which compromise all free space.
void InitializeCursorSpace(void);
//Allocate space for an element and return the position,O(1)
static Position CursorAlloc(void);
//Free the space in Position P,return
static void CursorFree(Position P);
//Allocate space for a new List(List Header),O(1)
//if There is no more space ,return -1
List MakeEmpty(void);
//O(1)
int IsEmpty(const List L);
//O(1)
int IsLast(const Position P);
//Find the first Position of X in List L,0 if not exist,O(n)
Position Find(ElementType X,const List L);
//Find the previous position of the first occurence of X in L,O(n)
//if X does not exist return 0;
Position FindPrevious(ElementType X,const List L);
//Delete the first ouccurence of X in List L,do nothing if not exist,O(n)
//if delete an element return true(1),or false(0).
int Delete(ElementType X,const List L);
//Insert X in List L(non-empty) after the Position P,O(1)
//if there is no more space,do nothing
void Insert(ElementType X,Position P);
//O(n)
void DeleteList(List L);
#include <stdio.h>

#endif /* CursorList_ADT_h */
