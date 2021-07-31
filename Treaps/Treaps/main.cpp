//
//  main.cpp
//  Treaps
//
//  Created by PorUnaCabeza on 2021/7/31.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Treaps.hpp"
#include <time.h>
#define N 120
#define KeyRange 100000000
#define step 10
#define test_random
#define round 1000000
int main(int argc, const char * argv[]) {
    int array[N]={478,309,273,483,588,666,452,879,583,168,478,509};
    int ran;
    Treap* T;
    Initialize(T);
    bool flag=true;
#ifdef test_random
    srand(time(NULL));
    for(int r=0;r<round;r++)
    {
        for(int i=0;i<N;i++)
        {
            ran=rand()%KeyRange;
            array[i]=ran;
            T=Insert(T, ran, ran);
        }
        for(int i=0;i<N;i++)
        {
            if(i%step==0)
            {
                T=Delete(T, array[i],flag);
//                cout<<"Delete array["<<i<<"]="<<array[i]<<endl;
            }
            if(!flag)
            {
                for(int j=0;j<N;j++)
                    cout<<array[j]<<endl;
                break;
            }
        }
        if(flag)
        cout<<"succ"<<endl;
        else
            break;
    }
#endif
    return 0;
}
