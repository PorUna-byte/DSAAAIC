//
//  main.cpp
//  Leftist_Heaps
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Leftist_Heaps.hpp"
#include <time.h>
int main(int argc, const char * argv[]) {
    // insert code here...
    PriorityQueue P=NULL;
    int random;
    srand(time(NULL));
    for(int i=0;i<10;i++)
    {
        random=rand()%1000;
        Insert(random, P);
        printf("Insert %d\n",random);
    }
    printf("\n");
    for(int i=0;i<10;i++)
    {
        DeleteMin(P);
    }
    printf("\n");
    return 0;
}
