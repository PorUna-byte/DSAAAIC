//
//  Leftist_Heaps.cpp
//  Leftist_Heaps
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
//why we need leftist heap? The reason is merge operation in Binheap is O(N) (somewhat not efficient
//However leftist heap can provide merge operation in O(logN)

#include "Leftist_Heaps.hpp"
#include <iostream>
#include <stack>
using namespace std;
struct TreeNode
{
    ElementType Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int  Npl; //the Npl of a node is the length of the shortest path
    //from the node to a another node without two children
};
void oom() //called if the memory is not enough.Although this is a very rare case.
{
    printf("out of memory!\n");
    exit(-1);
}
/*
 Note that this fuction is called by Merge.
 So,we know that H1's root element is smaller than H2's.
 */
PriorityQueue Merge_(PriorityQueue H1,PriorityQueue H2)
{
    if(H1->Left==NULL) //Note that H1 is a leftist priority queue,
        //so if H1->left is NULL that H1->right is also NULL,Hence H1 is a single node lpq
        H1->Left=H2;
    else  //if H1->Right is Null ,the following routine can also handle .
    {
        H1->Right=Merge(H1->Right,H2); //According to induction's rule 3, we must assume it works well for subtask.
        if(H1->Left->Npl<H1->Right->Npl)//if the property about npl is not hold,swap two children
        {
            PriorityQueue tmp=H1->Right;
            H1->Right=H1->Left;
            H1->Left=tmp;
        }
        H1->Npl=H1->Right->Npl+1; //update H1's npl
    }
    return H1;
}
/*
 Theorem:A leftist tree with r nodes on the right path must have at least 2^r-1 nodes.
 The proof is by induction.
 The time to perform merge is proportional to the sum of the length of the right paths.
 Since constant work is performed at each root node visited during the recursive calls.
 Thus we obtain an O(logN) time bound to merge two leftist heaps.
 N is the sum of nodes in both leftist heaps.
 */
PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2)//A driver routine which handles special cases
//and ensure the fitst paremeter in Merge_ has a smaller root
{
    if(!H1)
        return H2;
    if(!H2)
        return H1;
    if(H1->Element<H2->Element)
        return Merge_(H1,H2);
    else
        return Merge_(H2, H1);
}
/*
 Note that the recursive fashion of Merge is easy to implement,
 but it is hard to know how the merging work is actually done(because the os&compiler has done much
 work in recursive fuction and provide an abstract view for programers)
 What's more,recursive function adds some overhead.
 So,here I decide to implement a non-recursive fashion of Merge.(both for efficiency and clarity)
 
 Here is a brief description for how the routine work:
 In the first pass ,we create a new tree by merging the right paths of both heaps.
 To do this, we arrange the nodes on the right paths of H1 and H2 in sorted order,keeping their respective
 left children.
 In the second pass,we traverse bottom-up the heap,and childs swaps are performed at nodes that violates
 the leftist heap property(the left subtree has a higher or equal npl than the right subtree.)
 */
PriorityQueue Non_recur_merge(PriorityQueue H1,PriorityQueue H2)
{
    PriorityQueue H1_rightpath,H2_rightpath,tmp;
    stack<PriorityQueue> sta;
    if(!H1)
        return H2;
    if(!H2)
        return H1;
    if(H1->Element>H2->Element)
    {
        swap(H1, H2);
    }
    //Here H1 and H2 are not NULL
    //H1->Element<=H2->Element
    H1_rightpath=H1;
    H2_rightpath=H2;
    while(1)  //merge the right paths of H1 and H2 corresponding to the first pass
    {
        if(H1_rightpath->Right&&H1_rightpath->Right->Element>H2_rightpath->Element)
        {
            tmp=H1_rightpath->Right;
            H1_rightpath->Right=H2_rightpath;
            H1_rightpath=tmp;
            swap(H1_rightpath, H2_rightpath);
        }
        else if(H1_rightpath->Right)
            H1_rightpath=H1_rightpath->Right;
        else  //the only case to terminate the loop
        {
            H1_rightpath->Right=H2_rightpath;
            break;
        }
    }
    //Note that H2_rightpath is always a leftist heap in each iteration above
    //so we need only to check the node above H1_rightpath
    //we reuse the variable H2_rightpath here just for convenience
    H2_rightpath=H1;
    while(H2_rightpath!=H1_rightpath)
    {
        sta.push(H2_rightpath);
        H2_rightpath=H2_rightpath->Right;
    }
    sta.push(H2_rightpath);
    while(!sta.empty()) //fix the heap bottom-up corresponding to the second pass
    {
        H2_rightpath=sta.top();
        sta.pop();
        if(!H2_rightpath->Left)
        {
            H2_rightpath->Left=H2_rightpath->Right;
            H2_rightpath->Right=NULL;
        }
        else if(H2_rightpath->Right&&H2_rightpath->Left->Npl<H2_rightpath->Right->Npl)
            swap(H2_rightpath->Left, H2_rightpath->Right);
        H2_rightpath->Npl=H2_rightpath->Right?H2_rightpath->Right->Npl+1:0;//update Npl
    }
    return H1;
}
PriorityQueue Insert_(ElementType X,PriorityQueue H)//Note that insertion is just a special case of merge
//ie.. merge a single node (which is also a leftist heap) with the original leftist heap.O(logN)
{
    PriorityQueue SingleNode;
    SingleNode=(PriorityQueue)malloc(sizeof(struct TreeNode));
    if(!SingleNode)
        oom();
    SingleNode->Element=X;
    SingleNode->Left=SingleNode->Right=NULL;
    SingleNode->Npl=0;
    H=Non_recur_merge(SingleNode, H); //insetion is just a special case of merge
    return H;
}
PriorityQueue DeleteMin_(PriorityQueue H)//O(logN)
{
    PriorityQueue LeftHeap,RightHeap;
    if(!H)
    {
        printf("Priority queue is empty\n");
        return NULL;
    }
    LeftHeap=H->Left;
    RightHeap=H->Right;
    printf("DeleteMin:%d\n",H->Element);
    free(H);
    return Non_recur_merge(LeftHeap, RightHeap);
}
