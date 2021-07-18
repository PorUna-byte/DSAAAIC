//
//  main.cpp
//  Disjoint_set
//
//  Created by PorUnaCabeza on 2021/7/10.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
#include "Disjoint_set.hpp"
#include <time.h>
int main(int argc, const char * argv[]) {
    DisjSet Diset= Dis_Initialize(NumSets);
    srand(time(NULL));
    for(int i=0;i<NumSets/2;i++)
    {
        int a=rand()%NumSets+1;
        int b=rand()%NumSets+1;
        printf("Unite %d and %d\n",a,b);
        Unite(a, b, Diset);
    }
    Show(Diset);
    return 0;
}
