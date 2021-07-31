//
//  main.cpp
//  Pairing-heap
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Pairing-heap.hpp"
#include <time.h>
#define N 20
#define Range 1000
int main(int argc, const char * argv[]) {
    int array[N];
    int random;
    int Minkey;
    Position Loc;
    PairHeap heap=NULL;
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        random=rand()%Range;
        array[i]=random;
        heap=Insert(random, random, heap, Loc);
        cout<<"Insert "<<random<<endl;
    }
    for(int i=0;i<N;i++)
    {
        heap=DeleteMin(Minkey, heap);
        cout<<"DleteMin "<<Minkey<<endl;
    }
    return 0;
}
