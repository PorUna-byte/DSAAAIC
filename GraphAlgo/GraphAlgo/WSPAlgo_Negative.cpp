//
//  WSPAlgo_Negative.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#include <queue>
void WeightedNegative(Table T,Vertex start)
{
    queue<Vertex> queue;  //It's just a normal queue, not a priority queue which we have used in dijkstra's.
    Vertex V,W;
    int weight;
    queue.push(start);
    T->Entries[start].Known=true;
    while(!queue.empty())
    {
        V=queue.front();
        queue.pop();
        T->Entries[V].Known=false;
        //Traversal all vertices that are adjacent to V
        for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
        {
            W=w_node->cp->vertex;
            weight=w_node->cp->weight;
            if(T->Entries[V].Dist+weight<T->Entries[W].Dist)//use V to slack W, we don't care wheather w is known or not
            {
                T->Entries[W].Dist=T->Entries[V].Dist+weight;
                T->Entries[W].Path=V;//V is the last vertex that cause a change in W
                if(!T->Entries[W].Known)  //since known is unused, we can reuse known as an indication to wheather the vertex is in the queue or not.
                {
                    queue.push(W);
                    T->Entries[W].Known=true;
                }
            }
        }
    }
}
