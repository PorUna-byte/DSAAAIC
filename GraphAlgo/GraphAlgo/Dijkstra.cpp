//
//  Dijkstra.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#include "../../BinHeap/BinHeap/BinHeap.cpp"
void PrintPath(Vertex V,Table T)
{
    if(T->Entries[V].Path!=NotAVertex)
        PrintPath(T->Entries[V].Path, T);
    
    printf("%d ",V);
}
void Dijkstra(Table T)
{
    Vertex V,W;
    PriorityQueue P=Initialize(T->VertexNum);
    for(int i=1;i<T->VertexNum+1;i++)  //Initialize the heap
    {
        ++P->Size;
        P->Elements[P->Size].key=T->Entries[i].Dist; //something we need to compare
        P->Elements[P->Size].element=(Edge*)malloc(sizeof(Edge));//the true value
        P->Elements[P->Size].element->weight=i;
    }
    BuildHeap(P);
    while(!IsEmpty(P))
    {
        V=(DeleteMin(P))->weight;  //The unknown vertex with the smallest distance
        T->Entries[V].Known=true;
        //for each W adjacent to V
        for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            W=w_node->cp->vertex;
            DistType weight=w_node->cp->weight;
            if(!T->Entries[W].Known&&
               T->Entries[V].Dist+weight<T->Entries[W].Dist)
            {
                T->Entries[W].Dist=T->Entries[V].Dist+weight;//use V to slack W
                T->Entries[W].Path=V; //record the previous vertex for printing the path.
                UpdateKey(P, W, T->Entries[W].Dist); //update the heap
            }
        }
    }
}
