//
//  main.c
//  BST_ADT_Imp
//
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <stdio.h>
#include "BST_ADT.h"
int main(int argc, const char * argv[]) {
    SearchTree S=NULL;
    S=Insert(S, 5);
    S=Insert(S, 3);
    S=Insert(S, 2);
    S=Insert(S, 4);
    S=Insert(S, 7);
    S=Insert(S, 6);
    S=Insert(S, 8);
    printf("initial ...\n");
    PreOrder(S);
    printf("\n");
    InOrder(S);
    printf("\n");
    PostOrder(S);
    printf("\n");
    S=Delete(S, 8);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 7);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 3);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 5);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 6);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 4);
    PreOrder(S);
    printf("\n");
    S=Delete(S, 2);
    PreOrder(S);
}
