//
//  Graph.hpp
//  GraphAlgo
//
//  Created by PorUnaCabeza on 2021/7/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <fstream>
#include "../../BinHeap/BinHeap/BinHeap.hpp"
#include "../../Disjoint_set/Disjoint_set/Disjoint_set.hpp"
//Vertices are numbered from 0
#define NotAVertex -1
//the total number of vertices
#define Infinity 1<<30
#define root 1
using namespace std;

typedef int Vertex;
typedef int DistType;
typedef struct couple
{
    Vertex vertex;
    DistType weight;
}*CP;
typedef struct node{
    CP cp;
    struct node* next;
}Node;
typedef struct Head
{
    int size;
    Node* first;
}Header;
typedef struct TableEntry //A vertex has the following related information
{
    bool Known; //the vertex is known(Dist has been determined) or not
    DistType Dist;//The shortest path from source to this vertex using only known vertices as intermediates
    Vertex Path;//The previous vertex in the current shortest path.
    Header* Adjacent;//the adjacency list
}*TableEntryptr;
typedef struct table{
    int VertexNum;
    int EdgeNum;
    TableEntryptr Entries;
}*Table;
//extern int IsEmpty(PriorityQueue H);//O(1)
//extern Edge* DeleteMin(PriorityQueue H);//O(logN)
//extern void BuildHeap(PriorityQueue H);
//extern void UpdateKey(PriorityQueue H,int Position,KeyType new_key);
//extern PriorityQueue Initialize(int MaxElements);//O(1)
/*
Initialize the Table T using a file,which contains all vertices and edges.
 The file should be in the following form:
 NumofVertices NumofEdges
 D/U (D for directed graph, U for undirected graph)
 (v1,v2) (v2,v3) ...(vi,vj)...
 Time:O(max(|V|,|E|))=O(|V|+|E|).
 */
Table InitTable(Vertex start,string filename);

/*
 Print shortest path from source to V after Dijkstra has run
 Assume the path exists
 O(|V|)
 */
void PrintPath(Vertex V,Table T);
/*
 Perform the single source shortest path algorithm.
 O(|E|log|V|+|V|log|V|)=O(|E|log|V|) if use a priority queue, suits sparse graph(|E|=\theta(|V|)).
 O(|V|^2+|E|)=O(|V|^2)     if not use a priority queue, suits dense graph(|E|=\theta(|V|^2)).
 Note that Dijkstra works iff all edges are non-negative(>=0) .
 Why Dijkstra's can not handle the negative edge?
 Dijkstra's is an instance of greedy-algorithm.
 when we choose the current unknown vertex with minimum distance from source at each iteration,
  we mark it known and we assume it's distance would not change any more. So, we process one vertex per iteration and would not modify its distance later if it has been marked known.
 But, if the existence of negative edges are allowed, things are different.
 We CAN NOT guarantee that the known vertex's distance would not be modified later by other vertices if negative edges are allowed !
 */
void Dijkstra(Table T);
/*
 This Algorithm still works when negative cost edges exist,but the efficiency is frustrating.
 Note that negative cost edges are allowed, but negative cycle are not allowed,Since the existence of negative
 cycle will lead to undefined -oo .
 Time complexity:O(|E||V|)
 Why WeightedNegative can handle the negative edges?
 Note that the reason that the Dijkstra's can not work with negative edges lies in the known vertices' distance may
 be modified later.(even if they are marked known before.)
 So, one of the simple and brutal method to solve this problem is ignore the known information, that is we don't maintian known information any more.Every time we have an opportunity to slack a vertex, just slack it !
 You need convince yourself that this algorithm actually converges/terminates given enough time.
 */
void WeightedNegative(Table T,Vertex start);
/*
 This algorithm aims to find a minimum spanning tree in an undirected graph.
 A minimum spanning tree of an undirected graph G is a tree formed from graph edges that connects all the vertices
 of G at lowest total cost.
 We can see that Prim's is essentially identical to Dijkstra's.But, there is slight difference in the meaning(hence the update)of distance. Here, distance is the weight of the shortest arc from a known vertex to this vertex.(In dijkstra's distance is the total cost of shortest path from source to this vertex)
 Complexity is the same as dijkstra's:
 O(|E|log|V|+|V|log|V|)=O(|E|log|V|) if use a priority queue, suits sparse graph(|E|=\theta(|V|)).
 O(|V|^2+|E|)=O(|V|^2)     if not use a priority queue, suits dense graph(|E|=\theta(|V|^2)).
 */
void Prim(Table T);
//print the minimum spanning tree constructed by Prim's
void Print_MST_Prim(Table T);
/*
  This algorithm aims to find a minimum spanning tree in an undirected graph.
  Kruskal's is another example of greedy algorithm which continually to select the edges in order of smallest weight
 and accept an edge if it does not cause a cycle.
 Formally, Kruskal's maintains a forest.Initially, there are |V| single-node trees.Adding an edge merges two trees into one. When the algorithm terminates, there is only one tree, and this is the minimum spanning tree.
 So, the appropriate data structure is Disjoint set.
 Time complexity for Kruskal's is:O(ElogE)
 */
void Kruskal(Table T);
/*
 The vertices whose removal would disconnect the graph(more pricisely, increase the number of connected components) are known as articulation points.
 This routine aims to find the articulation points in given graph.
 O(|V|+|E|)
 */
void FindArt(Table T,Vertex V);
/*
 This is a simple routine to perform deep-first-search in Graph G(which is stored in T)
 We provide a non-recursive fashion.
 O(|V|+|E|)
 */
void DFS(Table T);
/*
 This is a simple routine to perform breadth-first-search in Graph G(which is stored in T)
 We provide a non-recursive fashion.
 O(|V|+|E|)
 */
void BFS(Table T);
#endif /* Graphstra_hpp */
