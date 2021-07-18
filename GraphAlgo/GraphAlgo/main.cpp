//
//  main.cpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Graph.hpp"
void test1(){
    Table T=InitTable(1, "graph");
    WeightedNegative(T,1);
    cout<<"The shortest path from "<<1<<"to "<<6<<" is:"<<T->Entries[6].Dist<<endl;
    PrintPath(6, T);
    cout<<endl;
    cout<<"The shortest path from "<<1<<"to "<<4<<" is:"<<T->Entries[4].Dist<<endl;
    PrintPath(4, T);
    cout<<endl;
}
void test2()
{
    Table T=InitTable(1, "graph");
    Dijkstra(T);
    cout<<"The shortest path from "<<1<<"to "<<6<<" is:"<<T->Entries[6].Dist<<endl;
    PrintPath(6, T);
    cout<<endl;
    cout<<"The shortest path from "<<1<<"to "<<4<<" is:"<<T->Entries[4].Dist<<endl;
    PrintPath(4, T);
    cout<<endl;
}
void test3()
{
    Table T=InitTable(1, "graph");
    Prim(T);
    cout<<"The minimum spanning tree is:"<<endl;
    Print_MST_Prim(T);
}
void test4()
{
    Table T=InitTable(1, "graph");
    cout<<"The minimum spanning tree is:"<<endl;
    Kruskal(T);
}
void test5()
{
    Table T=InitTable(1, "Art");
    FindArt(T,root); //start from 1 to find the articulation points in DFS
}
void test6()
{
    Table T=InitTable(1, "Art");
    DFS(T);
}
void test7()
{
    Table T=InitTable(1, "Art");
    BFS(T);
}
int main(int argc, const char * argv[]) {
    test7();
    return 0;
}
