//
//  Treaps.cpp
//  Treaps
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Treaps.hpp"
#include <stack>
#define Range 100000
Treap* NullNode=NULL;  //needs more initialization.
void oom(){
    printf("out of memory\n");
    exit(-1);
}
int random_(){
    return rand()%Range;
}
void *Malloc(size_t size)//A simple warpper to simplify the code
{
    void *ptr=malloc(size);
    if(ptr==NULL)
        oom();
    return ptr;
}
void Initialize(Treap* &T)
{
    if(NullNode==NULL)
    {
        NullNode=(Treap*)Malloc(sizeof(Treap));
        NullNode->key=NullNode->element=-1;
        NullNode->left=NullNode->right=NullNode;
        NullNode->priority=RAND_MAX;
    }
    T=NullNode;
}
//This is right rotation.
Treap* SingleRotateWithLeft(Treap* T)
{
    Treap* base=T->left;
    T->left=base->right;
    base->right=T;
    return base;
}
//This is left rotation
Treap* SingleRotateWithRight(Treap* T)
{
    Treap* base=T->right;
    T->right=base->left;
    base->left=T;
    return base;
}
static void fix_treap(bool& flag, int key, Treap *&p, stack<Treap *> &path, Treap *&x) {
    while(!path.empty())  //fix the treap bottom-up
    {
        p=path.top();
        path.pop();
        if(x->left->priority<x->priority||x->right->priority<x->priority)
        {
            if(key<x->key&&x->key<p->key&&x->left->priority<x->priority)
                p->left=SingleRotateWithLeft(x);
            else if(key>x->key&&x->key<p->key&&x->right->priority<x->priority)
                p->left=SingleRotateWithRight(x);
            else if(key<x->key&&x->key>p->key&&x->left->priority<x->priority)
                p->right=SingleRotateWithLeft(x);
            else if(key>x->key&&x->key>p->key&&x->right->priority<x->priority)
                p->right=SingleRotateWithRight(x);
        }
        else //the heap property is held.
        {
            flag=true;
            return ;
        }
        x=p;
    }
    if(key<x->key&&x->left->priority<x->priority)
        x=SingleRotateWithLeft(x);
    else if(key>x->key&&x->right->priority<x->priority)
        x=SingleRotateWithRight(x);
}

Treap* Insert(Treap* T,KeyType key,ElementType element)
{
    stack<Treap*> path;
    Treap* x=T;
    Treap* newnode=NULL;
    Treap* p;
    //If the treap is empty.
    if(T==NullNode)
    {
        T=(Treap*)Malloc(sizeof(Treap));
        T->key=key;
        T->element=element;
        T->left=T->right=NullNode;
        T->priority=random_();
        return T;
    }
    else
    {
        while(x!=NullNode)
        {
            path.push(x);
            if(key<x->key)
                x=x->left;
            else if(key>x->key)
                x=x->right;
            else  //already exist, just update its element and return the original treap.
            {
                x->element=element;
                return T;
            }
        }
        newnode=(Treap*)Malloc(sizeof(Treap));
        newnode->key=key;
        newnode->element=element;
        newnode->left=newnode->right=NullNode;
        newnode->priority=random_();
        x=path.top();
        path.pop();
        if(key<x->key)
           x->left=newnode;
        else
           x->right=newnode;
        bool flag=false;
        fix_treap(flag, key, p, path, x);
        if(flag) //terminate prematurely
            return T;
        else
            return x;
    }
}
Treap* Delete(Treap* T,KeyType key,bool& flag)
{
    if(T==NullNode)
    {
        cout<<"Delete error:empty treap"<<endl;
        return T;
    }
    Treap* x=T;
    Treap* p=NULL;
    while(x!=NullNode)
    {
        if(key<x->key)
        {
            p=x;
            x=x->left;
        }
        else if(key>x->key)
        {
            p=x;
            x=x->right;
        }
        else  //node found
        {
            if(p==NULL)
            {
                if(x->left->priority<x->right->priority)
                    T=p=SingleRotateWithLeft(x);
                else
                    T=p=SingleRotateWithRight(x);
                if(p==NullNode)  //The deleted node is at bottom now.
                {
                    free(p->left);
                    p->left=NullNode;
                    return T;
                }
            }
            if(x->left->priority<x->right->priority)
            {
                (x->key<p->key?p->left:p->right)=SingleRotateWithLeft(x);
                p=(x->key<p->key?p->left:p->right);
            }
            else
            {
                (x->key<p->key?p->left:p->right)=SingleRotateWithRight(x);
                p=(x->key<p->key?p->left:p->right);
            }
            if(p==NullNode)  //The deleted node is at bottom now.
            {
                free(p->left);
                p->left=NullNode;
                return T;
            }
        }
    }
    //the code shall never reach here.
    cout<<"Delete error: The key "<<key<<" is not found "<<endl;
    flag=false;
    return NULL;
}
