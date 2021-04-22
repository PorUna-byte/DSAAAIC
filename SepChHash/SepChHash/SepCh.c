//
//  SepCh.c
//  SepChHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "SepCh.h"
struct ListNode{
    ElementType key;
    struct ListNode* next;
};
struct Hashtbl{
    int TableSize;
    struct ListNode* Lists;
};
//return the smallest prime that bigger than N
int NextPrime(int N){
    if(N%2==0)  //a prime must be an odd number
        N++;
    int i;
    while(1) {
        for(i=3;i*i<=N;i+=2)  //the routine to judege if N is a prime or not
        {
            if(N%i==0)  //Not a prime
                goto out;
        }
        return N;  //if the program comes here,we can say N is a prime . return it.
    out:
        N+=2;
    }
}
int Hash_Func(int TableSize,ElementType key) //needs optimization
{
    return key%TableSize;
};
HashTable Initialize(int TableSize)
{
    HashTable table=(HashTable)malloc(sizeof(struct Hashtbl));
    if(table==NULL)
    {
        printf("out of space!\n");
        exit(1);
    }
    table->TableSize=NextPrime(TableSize);
    table->Lists=(struct ListNode*)malloc(sizeof(struct ListNode)*table->TableSize);
    if(table->Lists==NULL)
    {
        printf("Out of space!\n");
        exit(1);
    }
    for(int i=0;i<table->TableSize;i++)
    {
        table->Lists[i].next=NULL;
        table->Lists[i].key=-1;
    }
    return table;
}
Position FindKeyPre(ElementType key,HashTable table)
{
    Position pre=&table->Lists[Hash_Func(table->TableSize, key)];
    while(pre->next!=NULL && pre->next->key!=key)
        pre=pre->next;
    return pre;
}
void Insert(ElementType key,HashTable table)
{
    Position pre=FindKeyPre(key, table);
    if(pre->next==NULL) //key not exist,needs to insert
    {
        Position header=&table->Lists[Hash_Func(table->TableSize, key)];
        Position new_node=(Position)malloc(sizeof(struct ListNode));
        if(new_node==NULL)
        {
            printf("Out of space!\n");
            exit(1);
        }           //insert the new node into the front of the list,locality principle.
        new_node->key=key;
        new_node->next=header->next;
        header->next=new_node;
    }
    else
    {
        printf("Element is already in the table,can't insert\n");
        return;
    }
}
void Delete(ElementType key,HashTable table)
{
    Position Pre=FindKeyPre(key, table);
    if(Pre->next!=NULL){ //exist,needs to delete
        Position cur=Pre->next;
        Pre->next=cur->next;
        free(cur);
    }
    else{
        printf("The key not exist,can't delete\n");
        return ;
    }
}
void DropTable(HashTable table)
{
    for(int i=0;i<table->TableSize;i++)
    {
        Position P=&table->Lists[i];
        Position Q=NULL;
        while(P->next!=NULL)
        {
            Q=P;
            P=P->next;
            free(Q);
        }
        free(P);
    }
}
void ShowTable(HashTable table)
{
    printf("number\t|\tkeys\n");
    for(int i=0;i<table->TableSize;i++)
    {
        printf("%d\t\t|\t",i);
        Position cur=table->Lists[i].next;
        while(cur!=NULL)
        {
            printf("%d ",cur->key);
            cur=cur->next;
        }
        printf("\n");
    }
}
