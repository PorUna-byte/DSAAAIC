//
//  main.c
//  B_tree
//
//  Created by PorUnaCabeza on 2021/4/1.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include"B_tree.hpp"
int main(int argc, const char * argv[]) {
    BTree T=NULL;
    int a[]={4,5,6,10,14,
        15,16,20,23,27,
        50,51,52,60,64,
        65,68,70,72,73,
        75,77,78,79,80,
        81,82,89,90,92,
        93,95,100,110,111
    };
    for(int i=0;i<35;i++)
        T=Insert(a[i], T);
    for(int i=0;i<10;i++)
      T=Delete(a[i], T);
    for(int i=34;i>20;i--)
    T=Delete(a[i], T);
    for(int i=10;i<15;i++)
     T=Delete(a[i], T);
}
