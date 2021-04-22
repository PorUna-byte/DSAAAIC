//
//  main.c
//  SepChHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "SepCh.h"

int main(int argc, const char * argv[]) {
    HashTable table=Initialize(14);
    for(int i=0;i<100;i++)
     Insert(i,table);
    ShowTable(table);
    for(int i=0;i<100;i+=4)
    Delete(i,table);
    ShowTable(table);
    return 0;
}
