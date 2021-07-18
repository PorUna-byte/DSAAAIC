//
//  main.cpp
//  BinHeap
//
//  Created by PorUnaCabeza on 2021/7/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#include <time.h>
#include "BinHeap.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    PriorityQueue P=Initialize(100);
    int random;
    Edge* delnum;
    srand(time(NULL));
    for(int i=1;i<11;i++)
    {
        random=rand()%1000;
        ++P->Size;
        P->Elements[P->Size].key=random;
        P->Elements[P->Size].element=(Edge*)malloc(sizeof(Edge));
        P->Elements[P->Size].element->weight=random;
        printf("Insert %d\n",random);
    }
    printf("\n");
    BuildHeap(P);
    P->Elements[2].element->weight=3;
    UpdateKey(P, 2, 3);
    for(int i=0;i<10;i++)
    {
        delnum=DeleteMin(P);
        printf("DeleteMin %d\n",delnum->weight);
    }
    printf("\n");
    return 0;
}
