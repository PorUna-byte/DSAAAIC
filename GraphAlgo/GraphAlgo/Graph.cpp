//
//  Graph.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/17.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#include <stack>
#include <queue>
void dioom(){
    printf("out of memory\n");
    exit(-1);
}
void Insert(Header* h,CP cp)
{
    struct node* new_node=(struct node*)malloc(sizeof(struct node));
    if(new_node==NULL)
        dioom();
    new_node->cp=cp;
    if(h->first)
        new_node->next=h->first;
    else
        new_node->next=NULL;
    h->first=new_node;
    h->size++;
}

Table InitTable(Vertex start,string filename)
{
    char ch;
    int num,from,to,weight;
    bool Directed=false;
    Table T=(Table)malloc(sizeof(struct table));
    if(T==NULL)
        dioom();
    ifstream infile(filename);
    if(!infile.is_open())
    {
        printf("open file failed\n");
        exit(-1);
    }
    infile>>num;
    T->VertexNum=num;
    infile>>num;
    T->EdgeNum=num;
    T->Entries=(TableEntryptr)malloc(sizeof(struct TableEntry)*(T->VertexNum+1));//The index of vertex start from 1.
    if(T->Entries==NULL)
        dioom();
    for(int i=1;i<T->VertexNum+1;i++) //Initialize the graph
    {
        T->Entries[i].Dist=Infinity;
        T->Entries[i].Known=false;
        T->Entries[i].Path=NotAVertex;
        T->Entries[i].Adjacent=(Header*)malloc(sizeof(Header));
        T->Entries[i].Adjacent->size=0;
        T->Entries[i].Adjacent->first=NULL;
    }
    T->Entries[start].Dist=0; //the distance from start to start is 0.
    while(!infile.eof()) //read edges
    {
        infile>>ch;
        if(ch=='U')
            Directed=false;
        else if(ch=='D')
            Directed=true;
        else if(ch=='(') //start of (u,v,w)
        {
            infile>>from;  //the 'from' vertex of edge
            infile>>ch; // ,
            infile>>to; //the 'to' vertex of edge
            infile>>ch; // ,
            infile>>weight; //the weight of edge
            infile>>ch; // )
            CP cp=(CP)malloc(sizeof(struct couple));
            if(cp==NULL)
                dioom();
            cp->vertex=to;
            cp->weight=weight; //construct a couple
            Insert(T->Entries[from].Adjacent,cp);
            if(!Directed)  //for Undirected graph ,we add another edge.
            {
                CP cp=(CP)malloc(sizeof(struct couple));
                if(cp==NULL)
                    dioom();
                cp->vertex=from;
                cp->weight=weight; //construct a couple
                Insert(T->Entries[to].Adjacent,cp);
            }
        }
    }
    return T;
}
void DFS(Table T)
{
    Vertex V=1;
    Vertex W;
    stack<Vertex> sta;
    sta.push(V);
    T->Entries[V].Known=true;
    while(!sta.empty())
    {
        V=sta.top();
        sta.pop();
        cout<<V<<" ";
        for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            W=w_node->cp->vertex;
            if(!T->Entries[W].Known) //not visited
            {
                sta.push(W);
                T->Entries[W].Known=true;
            }
        }
    }
}
//BFS almost the same as DFS except that BFS use a queue while DFS use a stack.
void BFS(Table T)
{
    Vertex V=1;
    Vertex W;
    queue<Vertex> que;
    que.push(V);
    T->Entries[V].Known=true;
    while(!que.empty())
    {
        V=que.front();
        que.pop();
        cout<<V<<" ";
        for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            W=w_node->cp->vertex;
            if(!T->Entries[W].Known) //not visited
            {
                que.push(W);
                T->Entries[W].Known=true;
            }
        }
    }
}

