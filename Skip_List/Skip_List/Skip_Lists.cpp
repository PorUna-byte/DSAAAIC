//
//  Skip_Lists.cpp
//  Skip_List
//
//  Created by PorUnaCabeza on 2021/7/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Skip_Lists.hpp"
#define InitLevel 4
#define error_val -1
#define p 0.5
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
void *Realloc(void* old_ptr,size_t size)
{
    void *ptr=realloc(old_ptr, size);
    if(ptr==NULL)
        oom();
    return ptr;
}
int randomLevel(Skip_List* &lists)
{
    int level=1;
    while(rand()*1.0/RAND_MAX<p)
        level++;
    if(lists->List_Level<level)
    {
        lists->List_Level++;
        lists->Header->forwards=(Node**)Realloc(lists->Header->forwards, lists->List_Level*sizeof(Node*));
        lists->Header->forwards[lists->List_Level-1]=lists->NIL;
        return lists->List_Level;
    }
    else
        return level;
}
void InitSkip_list(Skip_List* &lists)
{
    srand(time(NULL));
    lists=(Skip_List*)Malloc(sizeof(Skip_List));
    lists->Header=(Node*)Malloc(sizeof(Node));
    lists->List_Level=InitLevel;  //Initialize the level to be InitLevel,
    //which can hold 2^InitLevel nodes in the list(Statistically)
    lists->Header->key=Min; //Header should has the smallest key
    lists->Header->element=Min;
    lists->Header->forwards=(Node**)Malloc(sizeof(Node*)*InitLevel);
    //Initialize NIL, which has the largest key.
    lists->NIL=(Node*)Malloc(sizeof(Node));
    lists->NIL->element=Max;
    lists->NIL->key=Max;
    lists->NIL->forwards=NULL;
    for(int i=0;i<InitLevel;i++)
        lists->Header->forwards[i]=lists->NIL;
}
ElementType Search(Skip_List* lists,KeyType searchKey)
{
    Node* x=lists->Header;
    //----loop invariant: x->key < searchKey
    for(int i=lists->List_Level-1;i>=0;i--)
    {
        while(x->forwards[i]->key<searchKey)
            x=x->forwards[i];
    }
    //---- x->key<searchKey<=x->forward[0]->key
    x=x->forwards[0];
    if(x->key==searchKey)
        return x->element;
    else
        return error_val;
}
void Insert(Skip_List* lists,KeyType key,ElementType element)
{
    int oldlevel=lists->List_Level;
    Node** update=(Node**)Malloc(sizeof(Node*)*lists->List_Level);
    /*
      A vector update is maintained so that when the search is complete (and we are ready to perform the splice), update[i] contains a pointer to the rightmost node of level i or higher that is to the left of the location of the inser- tion/deletion.     */
    Node* x=lists->Header;
    for(int i=lists->List_Level-1;i>=0;i--)
    {
       while(x->forwards[i]->key<key)
           x=x->forwards[i];
    //---- x->key<key<=x->forward[i]->key
        update[i]=x;
    }
    x=x->forwards[0];
    if(x->key==key)  //The node is already exist, just update its element.
        x->element=element;
    else
    {
        int level=randomLevel(lists);//may change the level of the list.
        //create a new node
        x=(Node*)Malloc(sizeof(Node));
        x->key=key;
        x->element=element;
        x->forwards=(Node**)Malloc(sizeof(Node*)*level);
        if(lists->List_Level==oldlevel+1)  //the level of skip lists has changed
        {
            x->forwards[oldlevel]=lists->NIL;
            lists->Header->forwards[oldlevel]=x;
        }
        int update_level=oldlevel+1==lists->List_Level?oldlevel:level;
        for(int i=0;i<update_level;i++)
        {
            x->forwards[i]=update[i]->forwards[i];
            update[i]->forwards[i]=x;
        }
    }
}
void Delete(Skip_List* lists,int key)
{
    Node** update=(Node**)Malloc(sizeof(Node*)*lists->List_Level);
    Node* x=lists->Header;
    int loopcount=0;
    for(int i=lists->List_Level-1;i>=0;i--)
    {
        while(x->forwards[i]->key<key)
            x=x->forwards[i];
        update[i]=x;
    }
    x=x->forwards[0];
    if(x->key==key)//found it
    {
        for(int i=0;i<lists->List_Level;i++)
        {
            if(update[i]->forwards[i]!=x)  //we can stop here, no need to check higher level
                break;
            update[i]->forwards[i]=x->forwards[i];
        }
        free(x->forwards);
        free(x);
        int oold_level=lists->List_Level;
        //Delete x may cause the change of the level of skip lists.
        while(lists->List_Level>InitLevel&&lists->Header->forwards[lists->List_Level-1]==lists->NIL)
            lists->List_Level--;
        if(oold_level!=lists->List_Level)
            lists->Header->forwards=(Node**)Realloc(lists->Header->forwards, lists->List_Level*sizeof(Node*));
    }
}
void PrintLists(Skip_List* lists)
{
    Node* x;
    for(int i=lists->List_Level-1;i>=0;i--)
    {
        x=lists->Header->forwards[i];
        cout<<"level "<<i+1<<":";
        while(x!=lists->NIL)
        {
            cout<<x->key<<" ";
            x=x->forwards[i];
        }
        cout<<endl;
    }
}
void DropLists(Skip_List* lists)
{
    Node* tmp;
    Node* x=lists->Header->forwards[0];
    while(x!=lists->NIL)
    {
        tmp=x;
        x=x->forwards[0];
        free(tmp->forwards);
        free(tmp);
    }
    free(lists->Header->forwards);
    free(lists->Header);
    free(lists->NIL);
    free(lists);
}
void verify(Skip_List* lists)
{
    Node* x=lists->Header;
    for(int i=lists->List_Level-1;i>=0;i--)
    {
        x=lists->Header;
        while(x!=lists->NIL)
        {
            if(x->forwards[i]==NULL)
            {
                cout<<"forward to null ptr"<<endl;
                exit(240);
            }
            if(x==x->forwards[i])
            {
                cout<<"forward to itself"<<endl;
                exit(242);
            }
            x=x->forwards[i];
        }
    }
}
