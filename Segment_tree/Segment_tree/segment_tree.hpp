//
//  segment_tree.hpp
//  Segment_tree
/*Let us consider the following problem to understand Segment Trees.
We have an array arr[0 . . . n-1]. We should be able to
1 Find the sum of elements from index l to r where 0 <= l <= r <= n-1
2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.
 
 A solution is to create another array and store sum from start to i at the ith index in this array. The sum of a given range can now be calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations is large and very few updates.
 What if the number of query and updates are equal? Can we perform both the operations in O(log n) time once given the array? We can use a Segment Tree to do both operations in O(Logn) time.
 */
 //  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef segment_tree_hpp
#define segment_tree_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>
typedef int Datatype;
#define SUM 1
#define MIN 2
#define INFINITY_MAX 0x7fffffff
using namespace std;
class Segment_tree
{
private:
    Datatype* raw_arr;
    Datatype* seg_tree;
    int size_of_raw;
    int size_of_seg;
    int flag;
    /* A recursive function to get the target of values in the given range
     of the array. The following are parameters for this function.
     
     si --> Index of current node in the segment tree. Initially
     0 is passed as root is always at index 0
     ss & se --> Starting and ending indexes of the segment represented
     by current node, i.e., st[si]
     qs & qe --> Starting and ending indexes of query range */
    Datatype getTargetUtil(int ss, int se, int qs, int qe, int si);
    
    /* A recursive function to update the nodes which have the given
     index in their range. The following are parameters
     si, ss and se are same as getSumUtil()
     i --> index of the element to be updated. This index is
     in the raw_arr.
     diff --> Value to be added to all nodes which have i in range */
    void updateValueUtil_sum(int ss, int se, int i, int diff, int si);
    // A recursive function that constructs Segment Tree for raw_arr[ss..se].
    // si is index of current node in segment tree seg_tree.
    Datatype constructSTUtil(int ss, int se, int si);

    void updateValueUtil_min(int ss, int se, int i, int old_val,int si);
public:
    // The function to update a value in input array and segment tree.
    // It uses updateValueUtil() to update the value in segment tree
    // logn
    void updateValue(int i, int new_val);
    
    
    // Return target of elements in range from index qs (query start)
    // to qe (query end). It mainly uses getTargetUtil()
    //logn
    Datatype getTarget(int qs, int qe);
    
    //constructor of segment_tree.
    //Allocate memory & fill the memory.
    Segment_tree(Datatype* raw_arr,int size_of_raw,int flag)
    {
        if(flag!=MIN&&flag!=SUM)
        {
            cout<<"Flag error"<<endl;
            exit(-1);
        }
        this->flag=flag;
        this->raw_arr=raw_arr;
        this->size_of_raw=size_of_raw;
        this->size_of_seg=(1<<((int)(ceil(log2(size_of_raw)))+1))-1;
        this->seg_tree=new Datatype[this->size_of_seg];
        memset(seg_tree, 0, size_of_seg*sizeof(Datatype));
        constructSTUtil(0, size_of_raw-1, 0);
    }
};
#endif /* segment_tree_hpp */
