//
//  main.cpp
//  Skip_List
//
//  Created by PorUnaCabeza on 2021/7/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include <iostream>
#include "Skip_Lists.hpp"
#define NumofNodes 10000
#define range 1000000
#define round 10000
int main(int argc, const char * argv[]) {
    for(int r=0;r<round;r++)
    {
        int array[NumofNodes];
        Skip_List* skip_lists;
        InitSkip_list(skip_lists);
        int random;
        for(int i=0;i<NumofNodes;i++)
        {
            random=rand()%range;
            array[i]=random;
//            cout<<"Insert "<<random<<endl;
            Insert(skip_lists, random, random);
        }
        for(int i=0;i<NumofNodes;i++)
        {
            if(i%5==0)
            {
//               cout<<"Delete "<<array[i]<<endl;
               Delete(skip_lists, array[i]);
            }
        }
        verify(skip_lists);
        DropLists(skip_lists);
   }
    cout<<"success !"<<endl;
    return 0;
}
