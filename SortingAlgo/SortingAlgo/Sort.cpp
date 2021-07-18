//
//  Sort.cpp
//  SortingAlgo
//
//  Created by PorUnaCabeza on 2021/7/9.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#define span(k) ((1<<k)-1)
#define leftchild(i) (2*i+1)
#define Cutoff 3
#include "Sort.hpp"
//In ascending order
void Insertion_sort(ElementType* A,int N)
{
    int i,j;
    ElementType Tmp;
    for(i=1;i<N;i++)
    {
        Tmp=A[i];
        for(j=i;j>=1&&A[j-1]>Tmp;j--)
                A[j]=A[j-1];
        A[j]=Tmp;
    }
}
void Shellsort(ElementType* A,int N)
{
    int i,j,k,Increment,count=0;
    ElementType Tmp;
    for(Increment=1;Increment<N/2;Increment<<=1) count++;//finding the count
    for(k=count;k>=1;k--)//using the span 2^k-1
    {
        for(i=span(k);i<N;i++) //An insertion sort which span 2^k-1
        {
            Tmp=A[i];
            for(j=i;j>=span(k)&&A[j-span(k)]>Tmp;j-=span(k))
                A[j]=A[j-span(k)];
            A[j]=Tmp;
        }
    }
}
/*
 percolate down to build a max heap
 i is the start node that needs to percolate down
 N is the size of heap (the number of nodes in heap)
 O(logN)
 */
void Percdown(ElementType* A,int i,int N)
{
    ElementType Tmp=A[i];
    int child;
    for(;leftchild(i)<N;i=child)//when i is non-leaf
    {
        child=leftchild(i);
        if(child!=N-1&&A[child]<A[child+1])//find the bigger child
            child++;
        if(A[child]>Tmp) //percolate Tmp down to appropriate space
            A[i]=A[child];
        else
            break;
    }
    A[i]=Tmp;
}
void Heapsort(ElementType* A,int N)
{
    for(int i=N/2-1;i>=0;i--)//start from the last non-leaf to build the max heap
        Percdown(A, i, N);
    for(int j=N-1;j>0;j--)//After this loop, A is sorted in ascending order
    {
        swap(A[0], A[j]);//swap the max element with the last element in heap
        Percdown(A, 0, j);//fix the heap and decrement the size of heap by 1
    }
}
void oom(){
    printf("out of memory\n");
    exit(-1);
}
//This routine merge two sorted lists into one list,O(N)
void Merge(ElementType* A,ElementType* TmpArray,int Lstart,int LeftEnd,int Rstart,int RightEnd)
{
    int TmpPos=Lstart;
    int Lcur=Lstart;
    int Rcur=Rstart;
    while(Lcur<=LeftEnd&&Rcur<=RightEnd)//merge two lists until one of them is empty
    {
        if(A[Lcur]<A[Rcur])
            TmpArray[TmpPos++]=A[Lcur++];
        else
            TmpArray[TmpPos++]=A[Rcur++];
    }
    while(Lcur<=LeftEnd)  //copy the remaining elements from left list,note that only one
        //while-loop will excute
        TmpArray[TmpPos++]=A[Lcur++];
    while(Rcur<=RightEnd)//copy the remaining elements from right list
        TmpArray[TmpPos++]=A[Rcur++];
    for(int k=Lstart;k<=RightEnd;k++)//copy elements back from TmpArray to A
        A[k]=TmpArray[k];
}
//Msort runs in divide-and-conquer way,it's a recursive routine.
//O(NlogN)
void Msort(ElementType* A,ElementType* TmpArray,int left,int right)
{
    int center;
    if(left<right)
    {
        center=(left+right)/2;
        Msort(A, TmpArray, left, center);//O(log N/2)
        Msort(A, TmpArray, center+1, right);//O(log N/2)
        Merge(A,TmpArray,left,center,center+1,right);//O(N)
    }
}
//This routine is just a driver for the true Msort
void Mergesort(ElementType* A,int N)
{
    ElementType* TmpArray;//An auxilary array for merge sort.
    TmpArray=(ElementType*)malloc(sizeof(ElementType)*N);
    if(TmpArray==NULL)
        oom();
    Msort(A, TmpArray, 0, N-1);
    free(TmpArray);
}
ElementType Median_3(ElementType* A,int left,int right)
{
    int center=(left+right)/2;
    if(A[left]>A[center])
        swap(A[left], A[center]);
    if(A[left]>A[right])
        swap(A[left], A[right]);
    if(A[center]>A[right])
        swap(A[center], A[right]);
    //Invariant:A[left]<=A[center]<=A[right], A[center] is chosen as pivot
    swap(A[center], A[right-1]);//hide pivot
    return A[right-1]; //return pivot
}
void Qsort(ElementType* A,int left,int right)
{
    int i,j;
    ElementType pivot;
    if(left+Cutoff<=right)//use quicksort
    {
        pivot=Median_3(A, left, right);
        i=left;
        j=right-1;
        while(true)
        {
            while(A[++i]<pivot) ;//skip elements in left that < pivot
            while(A[--j]>pivot) ;//skip elements in right that > pivot
            if(i<j)
                swap(A[i], A[j]);
            else
                break;
        }
        swap(A[i], A[right-1]);//restore pivot
        //now all elements that has index < i is smaller-or-equal than pivot==A[i]
        //all elements that has index > i is bigger-or-equal than pivot==A[i]
        Qsort(A, left, i-1);
        Qsort(A, i+1, right);
    }
    else  //use insertion sort
        Insertion_sort(A+left, right-left+1);
}
//This routine is just a driver for the true Qsort
void Quicksort(ElementType* A,int N)
{
    Qsort(A,0,N-1);
}
//This routine put the kth smallest element in position k(index k-1)
void Qselect(ElementType* A,int k,int left,int right)
{
    int i,j;
    ElementType pivot;
    if(left+Cutoff<=right)//use Qselect
    {
        pivot=Median_3(A, left, right);
        i=left;
        j=right-1;
        while(true)
        {
            while(A[++i]<pivot) ;//skip elements in left that < pivot
            while(A[--j]>pivot) ;//skip elements in right that > pivot
            if(i<j)
                swap(A[i], A[j]);
            else
                break;
        }
        swap(A[i], A[right-1]);//restore pivot
        //now all elements that has index < i is smaller-or-equal than pivot==A[i]
        //all elements that has index > i is bigger-or-equal than pivot==A[i]
        if(i>k-1)
            Qselect(A, k, left, i-1);
        else if(i<k-1)
            Qselect(A, k-i-1, i+1, right);
    }
    else  //use insertion sort
        Insertion_sort(A+left, right-left+1);
}
void Show(ElementType *A,int N)
{
    for(int i=0;i<N;i++)
    {
        if(i%10==0&&i)
            printf("\n");
        printf("%d\t",A[i]);
    }
    printf("\n");
}
