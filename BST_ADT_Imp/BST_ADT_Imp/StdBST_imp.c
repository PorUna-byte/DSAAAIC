//
//  StdBST_imp.c
//  BST_ADT_Imp
//
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#include "BST_ADT.h"
struct TreeNode{
    ElementType element;
    SearchTree  left;
    SearchTree  right;
};
int HasRight(SearchTree T)
{
    return T->right!=NULL;
}
int HasLeft(SearchTree T)
{
    return T->left!=NULL;
}
//Dispose a BST recursively
//exploit the property that a BST itself is defined recursively!
void DisposeBST(SearchTree T)
{
    if(T!=NULL)
    {
        DisposeBST(T->left);
        DisposeBST(T->right);
        free(T);
    }
    return ;
}
//Since the find routine can be easily performed non-recursively
//and non-recursive routine generally has better performance
//we decide to implement the routine non-recursively
Position Find(SearchTree T,ElementType X)
{
    Position P=T;
    while(P!=NULL)
    {
        if(X>P->element)
            P=P->right;
        else if(X<P->element)
            P=P->left;
        else
            return P;
    }
    return NULL;
}
Position FindMin(SearchTree T)
{
    if(T==NULL)
        return NULL;
    Position P=T;
    while(HasLeft(P))
        P=P->left;
    return P;
}
Position FindMax(SearchTree T)
{
    if(T==NULL)
        return NULL;
    Position P=T;
    while(HasRight(P))
        P=P->right;
    return P;
}
Position FindParent(SearchTree T,ElementType X)
{
    if(T==NULL)
        return NULL;
    Position P=T;
    Position Q=NULL;
    while(P!=NULL)
    {
        if(P->element==X)
           break;
        Q=P;
        if(X>P->element)
            P=P->right;
        else if(X<P->element)
            P=P->left;
    }
    return Q;
}
//We decide to implement insertion non-recursively for better performance
SearchTree Insert(SearchTree T,ElementType X)
{
    if(T==NULL)
    {
        T=(SearchTree)malloc(sizeof(struct TreeNode));
        if(T==NULL)
        {
            printf("Out of Space!\n");
            exit(0);
        }
       T->element=X;
       T->left=T->right=NULL;
      return T;
    }
    if(Find(T, X)!=NULL)
        return T;
    Position parent=FindParent(T, X);  //The last spot on the path travesed when we attempt to find X
    SearchTree new_Node=(SearchTree)malloc(sizeof(struct TreeNode));
    if(new_Node==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    new_Node->element=X;
    new_Node->left=new_Node->right=NULL;
    if(parent->element<X)
        parent->right=new_Node;
    else
        parent->left=new_Node;
    
    return T;
}
//For simplicity ,we implement the deletion recursively
//It will not hurt performance since only two iteration will be enough.
SearchTree Delete(SearchTree T,ElementType X)
{
    Position THIS=Find(T, X);
    if(THIS==NULL)
    {
        printf("X does not exist!\n");
        return 0;
    }
    Position parent=FindParent(T, X);  //what if parent ==NULL?
    int lor=0;
    if(parent!=NULL)
    lor=parent->left==THIS?1:0 ; //if This node is the left child of parent then lor=1 or 0;
    if(HasLeft(THIS)&&HasRight(THIS))
    {
        ElementType RightMin=FindMin(THIS->right)->element;
        Delete(THIS, RightMin);  //Delete the rightMin,since rightMin has one child at most it can be handled
        //by the following else code,So the time spent here is O(logN).
        THIS->element=RightMin;
    }
    else{
        if(HasLeft(THIS))//if This node has only left child
        {
            if(parent!=NULL)
            {
            Position LeftChild=THIS->left;
            if(lor)
                parent->left=LeftChild;
            else
                parent->right=LeftChild;
            }
            else
            {
                T=THIS->left;
            }
        }
        else if(HasRight(THIS))//if This node has only right child
        {
            if(parent!=NULL)
            {
            Position RightChild=THIS->right;
            if(lor)
                parent->left=RightChild;
            else
                parent->right=RightChild;
            }
            else{
                T=THIS->right;
            }
        }
        else{  //if This node has no child
            if(parent!=NULL)
            {
            if(lor)
                parent->left=NULL;
            else
                parent->right=NULL;
            }
            else
            {
                T=NULL;
            }
        }
        free(THIS);
    }
    return T;
}
void PreOrder(SearchTree T)
{
    if(T==NULL)
        return ;
    printf("%d  ",T->element);
    PreOrder(T->left);
    PreOrder(T->right);
}
void InOrder(SearchTree T)
{
    if(T==NULL)
        return ;
    InOrder(T->left);
    printf("%d  ",T->element);
    InOrder(T->right);
}
void PostOrder(SearchTree T)
{
    if(T==NULL)
        return ;
    PostOrder(T->left);
    PostOrder(T->right);
    printf("%d  ",T->element);
}
