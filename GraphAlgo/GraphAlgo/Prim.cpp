//
//  Prim.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/17.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
void Prim(Table T)
{
    Vertex V,W;
    PriorityQueue P=Initialize(T->VertexNum);
    for(int i=1;i<T->VertexNum+1;i++)  //Initialize the heap
    {
        ++P->Size;
        P->Elements[P->Size].key=T->Entries[i].Dist; //something we need to compare
        P->Elements[P->Size].element->weight=i;//the true value
    }
    BuildHeap(P);
    while(!IsEmpty(P))
    {
        V=DeleteMin(P)->weight;  //The unknown vertex with the smallest distance
        T->Entries[V].Known=true;
        //for each W adjacent to V
        for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            W=w_node->cp->vertex;
            DistType weight=w_node->cp->weight;
            if(!T->Entries[W].Known&&weight<T->Entries[W].Dist) //the update of T->Entries[W].Dist is differ from Dijkstra's
            {
                T->Entries[W].Dist=weight;//use V to slack W
                T->Entries[W].Path=V; //record the previous vertex for printing the path.
                UpdateKey(P, W, T->Entries[W].Dist); //update the heap
            }
        }
    }
}
void Print_MST_Prim(Table T)
{
    for(int i=1;i<T->VertexNum+1;i++) //vertices index starts from 1
    {
        if(T->Entries[i].Path!=NotAVertex)
            cout<<'('<<i<<','<<T->Entries[i].Path<<')'<<endl;
    }
}
