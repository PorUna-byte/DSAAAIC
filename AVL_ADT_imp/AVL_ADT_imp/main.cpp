//
//  main.c
//  AVL_ADT_imp
//
//  Created by PorUnaCabeza on 2021/3/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "AVL.hpp"

int main(int argc, const char * argv[]) {
    SearchTree T=NULL;
    printf("Test for insertion:\n");
    printf("we insert 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 sequentially\n");
    for(int i=3;i>=1;i--)
        T=Insert(T, i);
    for (int i=4;i<=7;i++)
        T=Insert(T, i);
    for(int i=16;i>=10;i--)
        T=Insert(T, i);
     T=Insert(T, 8);
     T=Insert(T, 9);
    printf("Preorder this AVL:\n");
    PreOrder(T);
    printf("Success!\n");
    printf("Inorder this AVL:\n");
    InOrder(T);
    printf("Success!\n");
    printf("Postorder_recursive this AVL:\n");
    PostOrder_recursive(T);
    printf("Success!\n");
    printf("Postorder_nonrecursive this AVL:\n");
    PostOrder_nonrecursive(T);
    printf("Success!\n");
    printf("Test for deletion:\n");
    printf("We delete 6,5,7,1 sequentially from the AVL above!\n");
    T=Delete(T, 6);
    T=Delete(T, 5);
    T=Delete(T, 7);
    T=Delete(T, 1);
    printf("Preorder this AVL:\n");
    PreOrder(T);
    printf("Success!\n");
    printf("We next delete 9,12,16,15,13 sequentially from the AVL above!\n");
    T=Delete(T, 9);
    T=Delete(T, 12);
    T=Delete(T, 16);
    T=Delete(T, 15);
    T=Delete(T, 13);
    printf("Preorder this AVL:\n");
    PreOrder(T);
    printf("Success!\n");
    printf("We next delete 3,11,4,2,14 sequentially from the AVL above!\n");
    T=Delete(T, 3);
    T=Delete(T, 11);
    T=Delete(T, 4);
    T=Delete(T, 2);
    T=Delete(T, 14);
    printf("Preorder this AVL:\n");
    PreOrder(T);
    printf("Success!\n");
    printf("We finally delete 10,8 sequentially from the AVL above!\n");
    T=Delete(T, 10);
    T=Delete(T, 8);
    printf("Preorder this AVL:\n");
    PreOrder(T);
    printf("Success!\n");
}
