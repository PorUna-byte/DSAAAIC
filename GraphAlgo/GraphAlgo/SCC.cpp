//
//  SCC.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/11/15.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#include <stack>
#include <queue>
#define MaxVertex 20
int counter_=0;
Vertex Index[MaxVertex];
Vertex Lowlink[MaxVertex];
bool on_stack[MaxVertex];
void strong_connect(Vertex v,stack<Vertex>& S,Table T);
void FindSCC(Table T)
{
    stack<Vertex> S;
    memset(on_stack, 0, MaxVertex);
    for(int v=1;v<=T->VertexNum;v++) //traverse all vertices
    {
        if(!Index[v])
            strong_connect(v, S, T);
    }
}
void strong_connect(Vertex v,stack<Vertex>& S,Table T)
{
    Index[v]=Lowlink[v]=++counter_;
    S.push(v);
    on_stack[v]=true;
    //consider successors of v
    for(Node* w_node=T->Entries[v].Adjacent->first;w_node!=NULL;w_node=w_node->next)
    {
        Vertex w=w_node->cp->vertex;
        if(!Index[w])
        {
            strong_connect(w, S, T);
            Lowlink[v]=min(Lowlink[v], Lowlink[w]);
        }
        else if(on_stack[w])
            Lowlink[v]=min(Lowlink[v],Index[w]);
    }
    //we can generate an SCC under this case
    if(Lowlink[v]==Index[v])
    {
        Vertex w;
        do{
            w=S.top();
            S.pop();
            on_stack[w]=false;
            cout<<w<<"\t";
        }while(w!=v);
        cout<<endl;
    }
}

