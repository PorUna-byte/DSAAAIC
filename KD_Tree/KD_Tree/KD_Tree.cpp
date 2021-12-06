//
//  KD_Tree.cpp
//  KD_Tree
//
//  Created by PorUnaCabeza on 2021/12/5.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "KD_Tree.hpp"
KD_node::KD_node(keyType* keys)
{
    for(int i=0;i<K;i++)
        this->keys[i]=keys[i];
    left=right=NULL;
}
bool KD_node::sameNode(keyType* keys)
{
    for(int i=0;i<K;i++)
        if(this->keys[i]!=keys[i])
            return false;
    return true;
}
void KD_node::do_Insert(keyType* keys,int height)
{
    int cd=height%K;//current dimension of the current node.
    if(sameNode(keys)) //already exist
        return;
    if(this->keys[cd]<=keys[cd])
    {
        if(right)
        right->do_Insert(keys, height+1);
        else
            right=new KD_node(keys);
    }
    else
    {
        if(left)
        left->do_Insert(keys, height+1);
        else
            left=new KD_node(keys);
    }
}
bool KD_node::do_Search(keyType* keys,int height)
{
    int cd=height%K;//current dimension of the current node.
    if(sameNode(keys)) //exist
        return true;
    if(this->keys[cd]<=keys[cd])
    {
        if(right)
            return right->do_Search(keys, height+1);
        else
            return false;
    }
    else
    {
        if(left)
            return left->do_Search(keys, height+1);
        else
            return false;
    }
}
void KD_Tree::Insert(keyType* keys)
{
    if(root)
        root->do_Insert(keys, 0);
    else
        root=new KD_node(keys);
}
bool KD_Tree::Search(keyType* keys)
{
    if(root)
        return root->do_Search(keys, 0);
    else
        return false;
}
KD_node* minNode(KD_node* n1,KD_node* n2,int dimension)
{
    return n1->getKeys(dimension)<n2->getKeys(dimension)?n1:n2;
}
KD_node* KD_node::do_FindMin(int dimension,int height)
{
    int cd=height%K;
    if(cd==dimension)
    {
        if(left)
        return left->do_FindMin(dimension, height+1);
        else
            return this;
    }
    else
    {
        KD_node* rval=this;
        if(left)
            rval=minNode(rval,left->do_FindMin(dimension, height+1),dimension);
        if(right)
            rval=minNode(rval,right->do_FindMin(dimension, height+1),dimension);
        return rval;
    }
}
keyType KD_Tree::FindMin(int dimension)
{
    if(root)
        return root->do_FindMin(dimension, 0)->getKeys(dimension);
    return -1;
}
void copykeys(KD_node* to,KD_node* from)
{
    for(int i=0;i<K;i++)
        to->keys[i]=from->keys[i];
}
KD_node* KD_node::do_Delete(keyType* keys,int height)
{
    int cd=height%K;
    if(sameNode(keys)) //found,delete current node
    {
        if(right)
        {
            KD_node* min=right->do_FindMin(cd, height+1);
            copykeys(this, min);
            right=right->do_Delete(this->keys, height+1);
        }
        else if(left)
        {
            KD_node* min=left->do_FindMin(cd, height+1);
            copykeys(this, min);
            right=left->do_Delete(this->keys, height+1);
        }
        else
        {
            delete this;
            return NULL;
        }
    }
    else//finding...
    {
        if(this->keys[cd]<=keys[cd]&&right)
            right=right->do_Delete(keys, height+1);
        else if(this->keys[cd]>keys[cd]&&left)
            left=left->do_Delete(keys, height+1);
        else
            cout<<"not found,deletion abort"<<endl;
    }
    return this;
}
void KD_Tree::Delete(keyType* keys)
{
    if(root)
        root->do_Delete(keys, 0);
}
