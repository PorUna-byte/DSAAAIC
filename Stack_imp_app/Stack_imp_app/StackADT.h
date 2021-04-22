//
//  StackADT.h
//  Stack_imp_app
//
//  Created by PorUnaCabeza on 2021/3/14.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef StackADT_h
#define StackADT_h
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
//Create an empty stack,O(1)
Stack CreateStack(void);
//Create a stack with capacity of Capacity
//Stack CreateStack_s(int Capacity);
//O(1)
int IsEmpty(Stack S);
//O(1)
int IsFull(Stack S);
//Pop the top element from the stack S,O(1)
void POP(const Stack S);
//return the element of the top of the stack,O(1)
ElementType TOP(const Stack S);
//Push the element X into the stack S,O(1)
void PUSH(const Stack S,ElementType X);
//POP the top element from the stack S and return its value,O(1)
ElementType TOPandPOP(const Stack S);
//Pop all elements from the stack,O(n)
void ClearStack(const Stack S);
//Delete The stack,O(n)
void DeleteStack(const Stack S);
#endif /* StackADT_h */
