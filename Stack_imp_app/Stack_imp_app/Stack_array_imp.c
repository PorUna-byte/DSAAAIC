//
//  Stack_array_imp.c
//  Stack_imp_app
//
//  Created by PorUnaCabeza on 2021/3/15.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "StackADT.h"
#define EmptyTOS -1
#define MinStackSize 5
struct Node{
    int TopofStack;
    int Capacity;
    ElementType * Array;
};
Stack CreateStack_s(int Capacity)
{
    int my_Size=Capacity>=MinStackSize?Capacity:MinStackSize;
    Stack new_Stack=(Stack)malloc(sizeof(struct Node));
    if(new_Stack==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    new_Stack->TopofStack=-1;
    new_Stack->Capacity=my_Size;
    new_Stack->Array=(ElementType*)malloc(sizeof(ElementType)*my_Size);
    if(new_Stack->Array==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    return new_Stack;
}
int IsEmpty(Stack S)
{
    return S->TopofStack==EmptyTOS;
}
int IsFull(Stack S)
{
    return S->TopofStack==S->Capacity-1;
}
void POP(const Stack S)
{
    if(IsEmpty(S))
    {
        printf("The Stack is empty!\n");
        exit(0);
    }
    S->TopofStack--;
    return ;
}
ElementType TOP(const Stack S)
{
    if(IsEmpty(S))
    {
        printf("The Stack is empty!\n");
        exit(0);
    }
    return S->Array[S->TopofStack];
}
void PUSH(const Stack S,ElementType X)
{
    if(IsFull(S))
    {
        printf("The stack is full!\n");
        exit(0);
    }
    S->Array[++S->TopofStack]=X;
    return ;
}
ElementType TOPandPOP(const Stack S)
{
    ElementType X=TOP(S);
    POP(S);
    return X;
}
void ClearStack(const Stack S)
{
    S->TopofStack=EmptyTOS;
}
void DeleteStack(const Stack S)
{
    free(S->Array);
    free(S);
}
