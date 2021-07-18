//
//  Sort.hpp
//  SortingAlgo
//
//  Created by PorUnaCabeza on 2021/7/9.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Sort_hpp
#define Sort_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define ElementType int
using namespace std;
/*
 A is a pointer to the array needs sorting
 N is the number of elements in A
 best-case :O(N) ,when the input array A is already sorted
 average-case : \theta(N^2)
 worst-case : \theta(N^2)
 */
void Insertion_sort(ElementType* A,int N);
/*
 Shellsort,named after its inventor Donald shell
 Shellsort uses a sequence,h_1,h_2,...h_t,called the increment sequence where h_1=1
 After a phase,using some increment h_k,for every i, we have A[i]<=A[i+h_k].
 All elements spaced h_k apart are sorted.The array is then said to be h_k-sorted.
 An important property of Shellsort is that an h_k-sorted array is then h_(k-1) sorted
 remains h_k-sorted.
 Hibbard suggested a increment sequence of the form:1,3,7,..2^k-1
 Worst-case of Shellsort using Hibbard's increments is \theta(N^(3/2))
 */
void Shellsort(ElementType* A,int N);
/*
 Priority queues can be used to sort in O(NlogN) time.
 The basic strategy is:
 1.Build a binary heap of N elements which takes O(N) time
 2.Perform N DeleteMin operations.The elements leave the heap smallest first, in sorted order.
which takes O(NlogN) time.
 */
void Heapsort(ElementType* A,int N);
/*
 Mergesort runs in O(NlogN) worst-case running time, and the number of comparison
 used is nearly optimal.
 The fundamental operation in this algorithm is merging two sorted lists.
 This algorithm is a classic divide-and-conquer strategy.
 */
void Mergesort(ElementType* A,int N);
/*
 As its name implies, quicksort is the fastest known sorting algorithm in practice.
 Average-case:O(NlogN), It is very fast, mainly due to a very tight
 and highly optimized inner loop
 Worst-case:O(N^2), It can be made exponentially unlikely with a little effort.
 \Omega(NlogN), Every algorithm that uses only comparison has this lower bound in worst-case.
 */
void Quicksort(ElementType* A,int N);
/*
 Quicksort can be modified to solve the selection problem.
 The steps of quickselect are:
 1.if |S|<=Cutoff, then sort S and return the kth smallest element.
 2.pick a pivot element, v \in S.
 3.partition S-{v} into S_1 and S_2, as was done with quicksort
 4.if k<=|S_1|, then the kth smallest element must be in S_1. In this case, return
 quickselect(S_1,k). if k==1+|S_1| ,then the pivot is the kth smallest element, just return it.
 Otherwise, the kth smallest element lies in S_2, and it is the (k-|S_1|-1)st smallest element
 in S_2. In this case, return quickselect(S_2,k-|S_1|-1).
 */
void Qselect(ElementType* A,int k,int left,int right);
//show all elements in A
void Show(ElementType *A,int N);
#endif /* Sort_hpp */
