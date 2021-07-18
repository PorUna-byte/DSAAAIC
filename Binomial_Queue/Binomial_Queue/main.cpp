//
//  main.cpp
//  Binomial_Queue
//
//  Created by PorUnaCabeza on 2021/6/25.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "Binomial_Queue.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    BinQueue P=Initialize();
    int random;
    srand(time(NULL));
    for(int i=0;i<10;i++)
    {
        random=rand()%1000;
        Insert(P,random);
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
