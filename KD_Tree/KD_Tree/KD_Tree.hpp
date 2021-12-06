//
//  KD_Tree.hpp
//  KD_Tree
/*
 A K-D Tree(also called as K-Dimensional Tree) is a binary search tree where data in each node is a K-Dimensional point in space. In short, it is a space partitioning(details below) data structure for organizing points in a K-Dimensional space.
 
 https://www.geeksforgeeks.org/k-dimensional-tree/
 */
//  Created by PorUnaCabeza on 2021/12/5.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef KD_Tree_hpp
#define KD_Tree_hpp

#include <stdio.h>
#include <iostream>

using namespace std;
const int K=2;
typedef int keyType;
class KD_node{
private:
    keyType keys[K];
    KD_node* left;
    KD_node* right;
    KD_node(keyType* keys);
    void do_Insert(keyType* keys,int height);
    bool do_Search(keyType* keys,int height);
    KD_node* do_FindMin(int dimension,int height);
    KD_node* do_Delete(keyType* keys,int height);
    bool sameNode(keyType* keys);
public:
    keyType getKeys(int index)
    {
        return keys[index];
    }
    friend class KD_Tree;
    friend void copykeys(KD_node* to,KD_node* from);
};
class KD_Tree{
private:
    KD_node* root=NULL;
public:
    KD_node* getroot()
    {
        return root;
    }
    void Insert(keyType* keys);
    bool Search(keyType* keys);
    keyType FindMin(int dimension);
    void Delete(keyType* keys);
};
#endif /* KD_Tree_hpp */
