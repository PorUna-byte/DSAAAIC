//
//  main.c
//  Queue_ADT
//
//  Created by PorUnaCabeza on 2021/3/16.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Queue_ADT.h"

int main(int argc, const char * argv[]) {
    Queue Q=CreateQueue(10);
    for(int i=0;i<10;i++)
        Enqueue(i, Q);
    for(int i=0;i<5;i++)
        printf("%d ",FrontandDequeue(Q));
    for(int i=0;i<5;i++)
        Enqueue(i, Q);
    while(!IsEmpty(Q))
        printf("%d ",FrontandDequeue(Q));
    return 0;
}
