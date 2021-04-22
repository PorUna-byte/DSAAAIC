//
//  Stack_imp_app
//
//  Created by PorUnaCabeza on 2021/3/14.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "StackADT.h"
#define Header -1
struct Node{
    ElementType element;
    PtrToNode next;
};
Stack CreateStack(void)
{
    Stack new_Stack=(Stack)malloc(sizeof(struct Node));
    if(new_Stack==NULL)
    {
        printf("Out of space!\n");
        exit(0);
    }
    new_Stack->next=NULL;
    new_Stack->element=Header;
    return new_Stack;
}
int IsEmpty(Stack S)
{
    if(S==NULL)
    {
        printf("Invalid Stack!\n");
        exit(0);
    }
    return S->next==NULL;
}
void POP(const Stack S)
{
    if(S==NULL)
    {
        printf("Invalid Stack!\n");
        exit(0);
    }
    if(IsEmpty(S))
    {
        printf("The Stack is empty already!\n");
        return ;
    }
    PtrToNode tmp=S->next;
    S->next=tmp->next;
    free(tmp);
    return ;
}
ElementType TOP(const Stack S)
{
    if(S==NULL)
    {
        printf("Invalid Stack!\n");
        exit(0);
    }
    if(IsEmpty(S))
    {
        printf("The Stack is empty !\n");
        exit(0);
    }
    return S->next->element;
}
void PUSH(const Stack S,ElementType X)
{
    if(S==NULL)
    {
        printf("Invalid Stack!\n");
        exit(0);
    }
    PtrToNode new_Ele=(PtrToNode)malloc(sizeof(struct Node));
    if(new_Ele==NULL)
    {
        printf("Out of space!\n");
        exit(0);
    }
    new_Ele->element=X;
    new_Ele->next=S->next;
    S->next=new_Ele;
    return ;
}
ElementType TOPandPOP(const Stack S)
{
    ElementType ele=TOP(S);
    POP(S);
    return ele;
}
void ClearStack(const Stack S)
{
    if(S==NULL)
    {
        printf("Invalid Stack!\n");
        exit(0);
    }
    while(!IsEmpty(S))
        POP(S);
}
void DeleteStack(const Stack S)
{
    ClearStack(S);
    free(S);
}

