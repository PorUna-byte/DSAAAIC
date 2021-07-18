//
//  Kruskal.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/17.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#include "../../Disjoint_set/Disjoint_set/Disjoint_set.cpp"
void Kruskal(Table T)
{
    int EdgesAccepted=0;
    DisjSet S=Dis_Initialize(NumSets);
    PriorityQueue H=Initialize(T->EdgeNum+1);
    Vertex U,V;
    SetType Uset,Vset;
    Edge* E;
    for(int i=1;i<T->VertexNum+1;i++)//traversal all vertices
    {
        //traversal the adjacency list of this vertex
        for(Node* w_node=T->Entries[i].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            Edge* tmpedge=(Edge*)malloc(sizeof(Edge));
            tmpedge->from=i;
            tmpedge->to=w_node->cp->vertex;
            tmpedge->weight=w_node->cp->weight;
            H->Size++;
            H->Elements[H->Size].key=w_node->cp->weight;
            H->Elements[H->Size].element=tmpedge;
        }
    }
    BuildHeap(H);//Build the heap
    while(EdgesAccepted<T->VertexNum-1)
    {
        E=DeleteMin(H);
        U=E->from;
        V=E->to;
        Uset=Find(U, S);
        Vset=Find(V,S);
        if(Uset!=Vset) //Accept this edge
        {
            Unite(Uset, Vset, S);
            cout<<'('<<U<<','<<V<<')'<<endl;
            EdgesAccepted++;
        }
    }
}
