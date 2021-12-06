//
//  Xor_linklist.hpp
//  Xor_linklist
//
//  Created by PorUnaCabeza on 2021/11/23.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Xor_linklist_hpp
#define Xor_linklist_hpp

typedef int ElementType;
typedef unsigned long DisType;
#include <stdio.h>
#include <iostream>
using namespace std;
//A representation of node in list
class Node{
public:
    ElementType data;
    DisType diff;  //the XOR between the previous node'address and the next node's address
    Node(ElementType data)
    {
        this->data=data;
        this->diff=NULL;
    }
};
class List{
private:
    Node* head;
    Node* tail;
public:
    List()
    {
        head=new Node(-1);
        tail=new Node(-1);
        head->diff=NULL^((unsigned long)tail);
        tail->diff=NULL^((unsigned long)head);
    }
    /*
     Insert a node at the front or tail of linklist and update.
     if the h_t is true, then means front
     if the h_t is false, then means tail
     O(1)
     */
    void Insert(bool h_t,ElementType data);
    
    /*
     Insert a new node with value 'new_data' after the node with value 'ref_data'
     if the ref_data is not found in the list,new_data will not be inserted.
     if the h_t is true, then means forwardly
     if the h_t is false, then means backwardly
     NOTE:if h_t is false,the traverse from the tail to front,and the after actually means before.
     O(n)
     */
    void Insert_after(bool h_t,ElementType ref_data,ElementType new_data);
    
    /*
     Traverse the list forwardly or backwardly while printing the list.
     if the h_t is true, then means forwardly
     if the h_t is false, then means backwardly
     O(n)
     */
    void Traverse(bool h_t);
    
    /*
     Delete the node with value 'del_data' forwardly or backwardly
     if del_data is not found,the deletion will not make any change to the list.
     if the h_t is true, then means forwardly
     if the h_t is false, then means backwardly
     NOTE:if forward means the first node with value 'del_data',backward means the last node.
     O(n)
     */
    void Delete(bool h_t,ElementType del_data);
};
#endif /* Xor_linklist_hpp */
