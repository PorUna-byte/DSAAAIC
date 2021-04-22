//
//  Splay_Imp.c
//  Splay_tree_topdown
//
//  Created by PorUnaCabeza on 2021/3/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//  I will implement the Splay_ADT in a tow-down method.
// Not only in this way can we make life easier but also obtain a better performance in practice.
// It uses only O(1) extra space and retain the O(logN) amortized time bound.

#include "Splay_ADT.h"
#define NULLNODEVALUE -1
struct SplayNode{
    ElementType element;
    SplayTree Left;
    SplayTree Right;
};
static Position NullNode =NULL;

SplayTree Initialize(void)
{
    if(NullNode==NULL)
    {
        NullNode =(Position)malloc(sizeof(struct SplayNode));
        if(NullNode==NULL)
        {
            printf("Out of Space!\n");
            exit(0);
        }
        NullNode->Left=NullNode->Right=NullNode;
    }
    return NullNode;
}
SplayTree SingleRotateWithRight(Position X)
{
    Position right=X->Right;
    X->Right=right->Left;
    right->Left=X;
    return right;
}
SplayTree SingleRotateWithLeft(Position X)
{
    Position left=X->Left;
    X->Left=left->Right;
    left->Right=X;
    return left;
}
SplayTree Splay(ElementType Item,SplayTree T)
{
    static struct SplayNode Header;
    Position LeftTreeMax,RightTreeMin;  //L & R
    LeftTreeMax=RightTreeMin=&Header;
    Header.Left=Header.Right=NullNode;
    NullNode->element=Item;
    while(Item!=T->element)  //Splay all the way when we are finding Item
    {
        if(Item>T->element)
        {
            if(Item>T->Right->element) //zig-zig
                T=SingleRotateWithRight(T);
            if(T->Right==NullNode)  //We have found the last spot on the way to Item
                break;
            LeftTreeMax->Right=T;   //Zig
            LeftTreeMax=T;
            T=T->Right;
        }
        else
        {
            if(Item<T->Left->element)
                T=SingleRotateWithLeft(T);
            if(T->Left==NullNode)
                break;
            RightTreeMin->Left=T;
            RightTreeMin=T;
            T=T->Left;
        }
    }
    //Reassemble
    LeftTreeMax->Right=T->Left;
    RightTreeMin->Left=T->Right;
    T->Left=Header.Right;
    T->Right=Header.Left;
    NullNode->element=NULLNODEVALUE;
    return T;
}
SplayTree Insert(ElementType Item,SplayTree T)
{
    static Position NewNode=NULL;
    if(NewNode==NULL)
    {
        NewNode=(Position)malloc(sizeof(struct SplayNode));
        if(NewNode==NULL)
        {
            printf("Out of Space!\n");
            exit(0);
        }
    }
    NewNode->element=Item;
    if(T==NullNode)  //Handle empty tree case
    {
        NewNode->Left=NewNode->Right=NullNode;
        T=NewNode;
    }
    else
    {
    T=Splay(Item, T);  //Splay the tree in a top-dwon method when we are searching the Item
    if(T->element<Item)   //The NewNode will be the root of the tree
    {
        NewNode->Right=T->Right;
        NewNode->Left=T;
        T->Right=NullNode;
        T=NewNode;
    }
    else if(T->element>Item)
    {
        NewNode->Left=T->Left;
        NewNode->Right=T;
        T->Left=NullNode;
        T=NewNode;
    }
    else            //The Item is already in the tree we just return that tree.
        return T;   //There is no need to create a new node for next Item that we will insert.
    }
    NewNode=NULL;  //When we insert a node successfully, we let the NewNode to be NULL so we can crate a
    //new node for next Item to be inserted.
    return T;
}
SplayTree Remove(ElementType Item,SplayTree T)
{
    Position NewTree;
    if(T!=NullNode)
    {
        T=Splay(Item, T);
        if(Item==T->element) //Found it
        {
            if(T->Left==NullNode)
                return T->Right;
            else
            {
                NewTree=T->Left;
                NewTree=Splay(Item, NewTree); //after this operation NewTree->Right is NullNode.
                NewTree->Right=T->Right;
            }
            free(T);
            T=NewTree;
        }
    }
    return T;
}
SplayTree Find(ElementType Item,SplayTree T)
{
    T=Splay(Item, T);
    if(Item!=T->element)
    {
        printf("The Item is not in the Tree.\n");
        exit(0);
    }
    else
        return T;
}
