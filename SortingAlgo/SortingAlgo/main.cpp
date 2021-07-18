//
//  main.cpp
//  SortingAlgo
//
//  Created by PorUnaCabeza on 2021/7/9.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <time.h>
#include "Sort.hpp"
#define N 100
#define Range 1000
#define Quickselect(A,K) \
Qselect(A,K,0,N-1)
int main(int argc, const char * argv[]) {
    int A[N];
    srand(time(NULL));
    for(int i=0;i<N;i++)
        A[i]=rand()%Range;
    //Insertion_sort(A, N);
    //Shellsort(A, N);
    //Heapsort(A, N);
    //Mergesort(A, N);
    int k=10;
    Quickselect(A,k);
    printf("the %dth smallest element in Array is:%d\n",k,A[k-1]);
    Quicksort(A, N);
    Show(A, N);
}
