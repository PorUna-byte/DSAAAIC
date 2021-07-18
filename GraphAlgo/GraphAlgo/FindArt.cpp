//
//  FindArt.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/17.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
#define MaxVertexNum 20
int counter=0;
Vertex Low[MaxVertexNum];
Vertex Num[MaxVertexNum];
/*
 The rule to assign Low[V] to each vertex:
 Low[V] is the minimum of following:
 1.Num(V)
 2.the lowest Num[W] among all back edge (V,W)
 3.the lowest Low[W] among all tree edges (V,W)
 
 what makes a point an articulation?
 theorem:
 A point V is an articulation point iff V(not root) has a child W in DFS and Low[W]>=Num[V]
 if V is root ,the check is simple: V is articulation point iff V has more than one children
 */
void FindArt(Table T,Vertex V)
{
    Vertex W; //the adjacent vertex
    T->Entries[V].Known=true;
    Low[V]=Num[V]=++counter;  //assign Num[V] and use rule 1 to assign Low[V]
    //traversal all adjacent vertices of V
    for(Node* w_node=T->Entries[V].Adjacent->first;w_node!=NULL;w_node=w_node->next)
    {
        W=w_node->cp->vertex;
        if(!T->Entries[W].Known) //tree edges(forward edges)
        {
            T->Entries[W].Path=V;//W becomes a child of V in DFS
            FindArt(T,W);
            if(Low[W]>=Num[V]&&V!=root) //by theorem
                printf("%d is an articulation point\n",V);
            Low[V]=min(Low[V], Low[W]); //rule 3
        }
        else if(T->Entries[V].Path!=W) //back edge
            Low[V]=min(Low[V],Num[W]);//rule 2
    }
    if(V==root)//check root specially
    {
        int childNum=0;
        for(int i=1;i<T->VertexNum+1;i++)
        {
            if(T->Entries[i].Path==V)
                childNum++;
        }
      if(childNum>1)
        printf("%d is an articulation point\n",V);//theorem
    }
}
