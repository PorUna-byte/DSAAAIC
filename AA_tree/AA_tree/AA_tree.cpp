//
//  AA_tree.cpp
//  AA_tree
//
//  Created by PorUnaCabeza on 2021/7/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "AA_tree.hpp"
Position NullNode=NULL; //Needs more initialization, which serve as a sentinel to simplify the code.
void oom(){
    printf("out of memory\n");
    exit(-1);
}
void *Malloc(size_t size)//A simple warpper to simplify the code
{
    void *ptr=malloc(size);
    if(ptr==NULL)
        oom();
    return ptr;
}
AATree Initialize()
{
    if(NullNode==NULL)
    {
        NullNode=(AATree)Malloc(sizeof(AANode));
        NullNode->Left=NullNode->Right=NullNode;
        NullNode->level=0;
        NullNode->key=NullNode->element=1<<31;
    }
    return NullNode;
}
//This is right rotation.
AATree SingleRotateWithLeft(AATree T)
{
    AATree base=T->Left;
    T->Left=base->Right;
    base->Right=T;
    return base;
}
//This is left rotation
AATree SingleRotateWithRight(AATree T)
{
    AATree base=T->Right;
    T->Right=base->Left;
    base->Left=T;
    return base;
}
/*
 Perform the right rotation to eliminate the horizontal left
 Node that this operation may introduce a consecutive horizontal right(which need be handled by split routine)
 */
AATree Skew(AATree T)
{
    if(T->Left&&T->Left->level==T->level)  //if T has horizontal left, then skew it.
        T=SingleRotateWithLeft(T);
    return T;
}
AATree Split(AATree T)
{
    if(T->Right&&T->Right->Right&&T->Right->Right->level==T->level)//if T has consecutive horizontal right,then split it
    {
        T=SingleRotateWithRight(T);
        T->level++;
    }
    return T;
}
AATree Insert(AATree T,KeyType key,ElementType element)
{
    if(T==NullNode)  //if we have reached the bottom and sees the sentinel NullNode
    {
        T=(AATree)Malloc(sizeof(AANode));
        T->key=key;
        T->element=element;
        T->level=1;  //All newly inserted nodes are in level 1.
        T->Left=T->Right=NullNode;
        return T;
    }
    else  //We insert the node recursively until we reach the bottom.
    {
        if(key<T->key)
            T->Left=Insert(T->Left, key, element);
        else if(key>T->key)
            T->Right=Insert(T->Right, key, element);
        else   //if there is a node with key 'key' already, just update its element.
            T->element=element;
    }
    T=Skew(T); //since skew T may introduce a consecutive horizontal right, we need a split to fix it.
    T=Split(T);
    return T;
}
AATree Remove(AATree T,KeyType key)
{
    static Position DeletePtr,LastPrt;
    if(T!=NullNode)
    {
        //step 1: search down tree and set LastPtr & DeletePtr
        LastPrt=T;
        if(key<T->key)  //Remove the node recursively
            T->Left=Remove(T->Left, key);
        else
        {
            DeletePtr=T;
            T->Right=Remove(T->Right, key);
        }
        //step2: If at the bottom of the tree and key is present, we remove it
        if(T==LastPrt&&DeletePtr!=NullNode&&DeletePtr->key==key)
        {
            DeletePtr->key=T->key;
            DeletePtr->element=T->element;
            DeletePtr=NullNode;
            T=T->Right;
            free(LastPrt);
        }
        //step3: Otherwise, we are not at the bottom, rebalance.
        else if((T->Left&&T->Left->level<T->level-1)||(T->Right&&T->Right->level<T->level-1))
        {
            if(T->Right->level>--T->level)
                T->Right->level=T->level;
            T=Skew(T);
            T->Right=Skew(T->Right);
            T->Right->Right=Skew(T->Right->Right);
            T=Split(T);
            T->Right=Split(T->Right);
        }
    }
    return T;
}
