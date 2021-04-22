//
//  main.c
//  Splay_tree_topdown
//
//  Created by PorUnaCabeza on 2021/3/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <stdio.h>
#include "Splay_ADT.h"
int main(int argc, const char * argv[]) {
    SplayTree T=Initialize();
    for(int i=1;i<17;i++)
    T=Insert(i, T);
    T=Remove(1, T);
    T=Find(3, T);
}
