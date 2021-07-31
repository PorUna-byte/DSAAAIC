//
//  main.cpp
//  AA_tree
//
//  Created by PorUnaCabeza on 2021/7/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <iostream>
#include "AA_tree.hpp"
#include <time.h>
#define Insert_AA(T,key,element) (T=Insert(T,key,element))
#define Remove_AA(T,key)  (T=Remove(T,key))
#define NumofNode 100
#define Range 10000
int main(int argc, const char * argv[]) {
    // insert code here...
    int array[NumofNode];
    AATree T=Initialize();
    srand(time(NULL));
    for(int i=0;i<NumofNode;i++)
    {
        int random=rand()%Range;
        array[i]=random;
        Insert_AA(T, random, random);
    }
    for(int i=0;i<NumofNode;i++)
    {
        if(i%5==0)
        Remove_AA(T,array[i]);
    }
    cout<<"success"<<endl;
    return 0;
}
