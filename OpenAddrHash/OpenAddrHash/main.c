//
//  main.c
//  OpenAddrHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "OpenAddrHash.h"

int main(int argc, const char * argv[]) {
    HashTable table=Initialize(20);
    for(int i=0;i<10;i++)
    table=Insert(i*23,table);
    ShowTable(table);
    printf("--------------------------------------------\n");
    for(int i=1;i<5;i++)
    table=Insert(i*47,table);
    ShowTable(table);
    printf("--------------------------------------------\n");
    for(int i=1;i<5;i++)
    table=Delete(i*47,table);
    ShowTable(table);
    printf("--------------------------------------------\n");
    for(int i=0;i<10;i++)
    table=Delete(i*23,table);
    ShowTable(table);
    printf("--------------------------------------------\n");
    for(int i=0;i<10;i++)
    table=Insert(i*19,table);
    ShowTable(table);
    return 0;
}
