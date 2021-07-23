//
//  main.cpp
//  RB_tree
//
//  Created by PorUnaCabeza on 2021/7/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "RB_tree.hpp"
#include <time.h>
#include <fstream>
#define N 240000
#define range 100000000
#define test_random
#define test_delete
#define ROUND 10
int main(int argc, const char * argv[]) {
   int array[N]={4323,1048,5322,8043,2414,1160,3007,6407,5666,9922,2677,1361,8561,6422,4607,
       3180,5551,6842,6515,2768,1959,6690,8127,714};
//      int array[N]={6449,3884,2575,7424,8929,6305,7107,9831,9449,4193,
//          2521,4867,9523,8501,4784,5053,7023,7221,7220,8789,8219,1450,2640,2030};
#ifdef test_random
    srand(time(NULL));
    int random;
    for(int round=0;round<ROUND;round++)
    {
#endif
    Tree* T=Init_RBT();
    for(int i=0;i<N;i++)
    {
#ifdef test_random
        random=rand()%range;
        array[i]=random;
#endif
        Insert(T, array[i], array[i]);
#ifndef test_random
        cout<<"Insert "<<array[i]<<endl;
#endif
    }
#ifndef test_random
    Print_tree(T);
        cout<<"Insertion verify:"<<(verify_RBT(T)==true?"verify success":"verify error")<<endl;
#endif
#ifdef test_delete
#ifndef test_random
    cout<<"After deletion of:";
#endif
    for(int i=0;i<N;i++)
    {
        if(i%4==0)
        {
            Delete(T, array[i]);
#ifndef test_random
            cout<<array[i]<<"  ";
            cout<<(verify_RBT(T)==true?"verify success":"verify error")<<endl;
            Print_tree(T);
#endif
        }
    }
    cout<<endl;
#ifndef test_random
    Print_tree(T);
#endif
#endif
    if(!verify_RBT(T))
    {
        ofstream outfile("error_tree.txt",ios::trunc);
        if(!outfile.is_open())
            cout<<"not open:"<<endl;
        else
        {
        outfile<<"the array elements:"<<endl;
        for(int i=0;i<N;i++)
            outfile<<array[i]<<",";
            outfile<<endl;
        }
        Print_tree(T);
        exit(-1);
    }
#ifndef test_random
        cout<<"Deletetion verify:"<<(verify_RBT(T)==true?"verify success":"verify error")<<endl;
#endif
        free_tree(T);
#ifdef test_random
    }
#endif
}
