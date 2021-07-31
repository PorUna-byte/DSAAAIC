//
//  Skip_Lists.hpp
//  Skip_List
//
//  Created by PorUnaCabeza on 2021/7/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 Skip lists are a data structure that can be used in place of balanced trees. Skip lists use probabilistic balancing rather than strictly enforced balancing and as a result the algorithms for insertion and deletion in skip lists are much simpler and significantly faster than equivalent algorithms for balanced trees.
 The following code was formed from the paper that issued by William Pugh in 1990. For convenience, that paper is included in this directory, please refer to "pugh-skiplists-cacm1990.pdf" for more detail.
 */
#ifndef Skip_Lists_hpp
#define Skip_Lists_hpp

#include <stdio.h>
#include <iostream>
#include <time.h>
#define KeyType int
#define ElementType int
const int Min=1<<31;
const int Max=RAND_MAX;
using namespace std;
typedef struct node{
    KeyType key;
    ElementType element;
    struct node** forwards;
}Node;
typedef struct skip_list
{
    int List_Level;
    Node* Header;
    Node* NIL;
}Skip_List;
/*
 Initialize the skip lists, that is create header & NIL
 O(1)
 */
void InitSkip_list(Skip_List* &lists);
/*
 Search for element assciated with key 'key' .
 Time complexity in average/probabilistic case:O(logN)
 The proof is in the "pugh-skiplists-cacm1990.pdf"
 */
ElementType Search(Skip_List* lists,KeyType searchKey);
/*
 Insert a node with key 'key' & element 'element', if there is a node with key 'key' already then update the node's
 element to 'element' .
 Time complexity is dominated by Search routine, hence O(logN) for average/probabilistic case.
 */
void Insert(Skip_List* lists,KeyType key,ElementType element);
/*
  Delete the node with key 'key'.
  if the node doesn't exist, do nothing but print a message.
  Time complexity is dominated by Search routine, hence O(logN) for average/probabilistic case.
 */
void Delete(Skip_List* lists,KeyType key);
/*
   Print the skip lists level by level.
   Time complexity in average/probabilistic case:O(N/p)
 */
void PrintLists(Skip_List* lists);

/*
  Drop the skip lists and free space.
 */
void DropLists(Skip_List* lists);

/*
   Verify the skip lists.
 */
void verify(Skip_List* lists);
#endif /* Skip_Lists_hpp */
