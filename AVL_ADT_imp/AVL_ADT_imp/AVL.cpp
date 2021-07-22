//
//  AVL.cpp
//  AVL_ADT_imp
//
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
//Although The code is in .cpp it is more like C
#include "AVL.hpp"
#define Max(a,b) (a>b?a:b)
static int Height(Position P)
{
    if(P==NULL)
        return -1;
    else
        return P->height;
}
int HasRight(SearchTree T)
{
    return T->right!=NULL;
}
int HasLeft(SearchTree T)
{
    return T->left!=NULL;
}
SearchTree CreateNode(ElementType X)
{
    SearchTree T=(SearchTree)malloc(sizeof(struct TreeNode));
    if(T==NULL)
    {
        printf("Out of Space!\n");
        exit(0);
    }
    T->element=X;
    T->height=0;
    T->left=T->right=NULL;
    return T;
}
//Dispose a BST recursively
//exploit the property that a BST itself is defined recursively!
void DisposeAVL(SearchTree T)
{
    if(T!=NULL)
    {
        DisposeAVL(T->left);
        DisposeAVL(T->right);
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
void PreOrder(SearchTree T)
{
    if(T==NULL)
    {
        printf("empty tree!\n");
        return ;
    }
    Position P=T;
    stack<Position>sta;
    while(!sta.empty()||P!=NULL)
    {
        while(P!=NULL)
        {
        sta.push(P);
        printf("%d  ",P->element);
        P=P->left;
        }
        while(!sta.empty())
        {
            P=sta.top();
            sta.pop();
            if(HasRight(P))
            {
                sta.push(P->right);
                break;
            }
        }
        if(!sta.empty())
        {
            P=sta.top();
            sta.pop();
        }
        else
            return ;
    }
    return ;
}
void InOrder(SearchTree T)
{
    if(T==NULL)
    {
        printf("empty tree!\n");
        return ;
    }
    Position P=T;
    stack<Position>sta;
    while(!sta.empty()||P!=NULL)
    {
        while(P!=NULL)
        {
            sta.push(P);
            P=P->left;
        }
        Position R=NULL;
        while(!sta.empty())
        {
            R=sta.top();
            sta.pop();
            printf("%d  ",R->element);
            if(HasRight(R))
            {
                sta.push(R->right);
                break;
            }
        }
        if(!sta.empty())
        {
            P=sta.top();
            sta.pop();
        }
    }
    return ;
}
void PostOrder_recursive(SearchTree T)
{
    if(T==NULL)
        return ;
    PostOrder_recursive(T->left);
    PostOrder_recursive(T->right);
    printf("%d  ",T->element);
}
void PostOrder_nonrecursive(SearchTree T)
{
    if(T==NULL)
    {
        printf("empty tree!\n");
        return ;
    }
    Position P=T;
    stack<Position>sta;
    bool flag=true;
    Position pre=NULL;
    Position R=NULL;
    //An indication for left subtree.
    //if left subtree was visited before then flag=1,else 0.
    do{
        while(P!=NULL)  //push all left subtrees
        {
            sta.push(P);
            P=P->left;
        }
        flag=true; //left subtree has been visited
        while(!sta.empty()&&flag)
        {
            R=sta.top();
            if(HasRight(R)&&R->right!=pre)//if has right subtree and right subtree was not visited before!
            {
                P=R->right; //traverse right subtree
                flag=false; //now,the right subtree's left subtree is not visited.
            }
           else
           {
               printf("%d  ",R->element);
               pre=R;  //set current node as pre,since current node is being visited!
               sta.pop();
           }
        }
    }
    while(!sta.empty());
    return ;
}
//-----------------------------------------
static Position SingleRotateWithLeft(Position K2)
{
    Position K1=K2->left;
    K2->left=K1->right;
    K1->right=K2;
    K2->height=Max(Height(K2->left),Height(K2->right))+1;
    K1->height=Max(Height(K1->left),Height(K1->right))+1;
    return K1;
}
static Position SingleRotateWithRight(Position K2)
{
    Position K1=K2->right;
    K2->right=K1->left;
    K1->left=K2;
    K2->height=Max(Height(K2->left),Height(K2->right))+1;
    K1->height=Max(Height(K1->left),Height(K1->right))+1;
    return K1;
}
static Position DoubleRotateWithLeft(Position K3)
{
    K3->left=SingleRotateWithRight(K3->left);
    return SingleRotateWithLeft(K3);
}
static Position DoubleRotateWithRight(Position K3)
{
    K3->right=SingleRotateWithLeft(K3->right);
    return SingleRotateWithRight(K3);
}
stack<Position> FindPath(SearchTree T,ElementType X)
{
    stack<Position> sta;
    Position P=T;
    while(P!=NULL)
    {
        if(P->element==X)
            break;
        sta.push(P);
        if(X<P->element)
            P=P->left;
        else
            P=P->right;
    }
    return sta;
}
static void fix_tree(SearchTree &T,stack<Position> &sta) {
    while(!sta.empty())//fix the tree bottom-up
    {
        Position ancestor=sta.top();
        sta.pop();
        int old_height=ancestor->height;
        ancestor->height=Max(Height(ancestor->left), Height(ancestor->right))+1;
        SearchTree fixed_subtree=NULL;
        if(abs(Height(ancestor->left)-Height(ancestor->right))==2)
        {
            if(Height(ancestor->left)-Height(ancestor->right)==2)
            {
                if(Height(ancestor->left->left)>Height(ancestor->left->right))
                    fixed_subtree=SingleRotateWithLeft(ancestor);
                else
                    fixed_subtree=DoubleRotateWithLeft(ancestor);
            }
            else if(Height(ancestor->right)-Height(ancestor->left)==2)
            {
                if(Height(ancestor->right->right)>Height(ancestor->right->left))
                    fixed_subtree=SingleRotateWithRight(ancestor);
                else
                    fixed_subtree=DoubleRotateWithRight(ancestor);
            }
            if(!sta.empty())
            {
                Position super_ancestor=sta.top();
                if(super_ancestor->element>fixed_subtree->element)
                    super_ancestor->left=fixed_subtree;
                else
                    super_ancestor->right=fixed_subtree;
            }
            else
                T=fixed_subtree;
            
            break;  //after rotation and concatenation, the tree is balanced.
        }
        else if(old_height==ancestor->height)  //The tree is balanced
            break;
    }
}

//We decide to implement insertion non-recursively for better performance
SearchTree Insert(SearchTree T,ElementType X)
{
    if(T==NULL) //Deal with an empty tree
    {
        T=CreateNode(X);
        return T;
    }
    if(Find(T, X)!=NULL) //X is Already exist in the Tree,do nothing.
        return T;
    stack<Position>sta=FindPath(T, X);  //The path to X(not included)
    Position parent=sta.top();
    SearchTree new_Node=CreateNode(X);
    if(parent->element<X)
        parent->right=new_Node;
    else
        parent->left=new_Node;
    fix_tree(T,sta);
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
 stack<Position>sta=FindPath(T, X);  //what if parent ==NULL?
     Position parent=NULL;
  if(!sta.empty())
      parent=sta.top();
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
     fix_tree(T,sta);
 }
 return T;
 }
