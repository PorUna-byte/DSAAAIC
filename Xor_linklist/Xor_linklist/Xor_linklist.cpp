//
//  Xor_linklist.cpp
//  Xor_linklist
//
//  Created by PorUnaCabeza on 2021/11/23.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Xor_linklist.hpp"

void List::Insert(bool h_t,ElementType data)
{
    if(h_t)  //insert a node at the front
    {
        DisType next=head->diff^0;
        Node* new_node=new Node(data);
        new_node->diff=(DisType)head ^ next;
        head->diff=(DisType)new_node ^ 0;
        ((Node*)next)->diff=((Node*)next)->diff ^ (DisType)head ^ (DisType)new_node ;
    }
    else
    {
        DisType next=tail->diff^0;
        Node* new_node=new Node(data);
        new_node->diff=(DisType)tail ^ next;
        tail->diff=(DisType)new_node ^ 0;
        ((Node*)next)->diff=((Node*)next)->diff ^ (DisType)tail ^ (DisType)new_node ;
    }
}

void List::Insert_after(bool h_t,ElementType ref_data,ElementType new_data)
{
    if(h_t)  //search from the front
    {
        Node* prev=head;
        Node* current=(Node*)(head->diff^0);
        Node* next;
        while(current->data!=ref_data&&current!=tail)
        {
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        if(current==tail)
        {
            cout<<ref_data<<" not found! Insertion abort."<<endl;
            return ;
        }
        //ref_data has been found, insert a new node after it.
        Node* new_node=new Node(new_data);
        next=(Node*)(current->diff ^ (DisType)prev) ;
        new_node->diff=(DisType)current ^ (DisType)next ;
        current->diff=(DisType)prev ^ (DisType)new_node ;
        next->diff=next->diff ^ (DisType)current ^ (DisType)new_node ;
    }
    else
    {
        Node* prev=tail;
        Node* current=(Node*)(tail->diff^0);
        Node* next;
        while(current->data!=ref_data&&current!=head)
        {
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        if(current==head)
        {
            cout<<ref_data<<" not found! Insertion abort."<<endl;
            return ;
        }
        //ref_data has been found, insert a new node after it.
        Node* new_node=new Node(new_data);
        next=(Node*)(current->diff ^ (DisType)prev) ;
        new_node->diff=(DisType)current ^ (DisType)next ;
        current->diff=(DisType)prev ^ (DisType)new_node ;
        next->diff=next->diff ^ (DisType)current ^ (DisType)new_node ;
    }
}
void List::Traverse(bool h_t)
{
    if(h_t)
    {
        Node* prev=head;
        Node* current=(Node*)(head->diff^0);
        Node* next;
        while(current!=tail)
        {
            cout<<current->data<<"   ";
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        cout<<endl;
    }
    else
    {
        Node* prev=tail;
        Node* current=(Node*)(tail->diff^0);
        Node* next;
        while(current!=head)
        {
            cout<<current->data<<"   ";
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        cout<<endl;
    }
}
void List::Delete(bool h_t,ElementType del_data)
{
    if(h_t)
    {
        Node* prev=head;
        Node* current=(Node*)(head->diff^0);
        Node* next;
        while(current->data!=del_data&&current!=tail)
        {
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        if(current==tail)
        {
            cout<<del_data<<" not found! Deletion abort."<<endl;
            return ;
        }
        //del_data has been found, delete the node.
        next=(Node*)(current->diff ^ (DisType)prev) ;
        prev->diff=prev->diff ^ (DisType)current ^ (DisType)next;
        next->diff=next->diff ^ (DisType)current ^ (DisType)prev;
        delete current;
    }
    else
    {
        Node* prev=tail;
        Node* current=(Node*)(tail->diff^0);
        Node* next;
        while(current->data!=del_data&&current!=head)
        {
            next=(Node*)(current->diff ^ (DisType)prev);
            prev=current;
            current=next;
        }
        if(current==head)
        {
            cout<<del_data<<" not found! Deletion abort."<<endl;
            return ;
        }
        //del_data has been found, delete the node.
        next=(Node*)(current->diff ^ (DisType)prev) ;
        prev->diff=prev->diff ^ (DisType)current ^ (DisType)next;
        next->diff=next->diff ^ (DisType)current ^ (DisType)prev;
        delete current;
    }
}
