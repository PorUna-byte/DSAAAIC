//
//  main.cpp
//  Tournament_tree
//
//  Created by PorUnaCabeza on 2021/11/3.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Tournament.hpp"
using namespace std;
void show(KeyType* Tree)
{
    for(int i=0;i<K;i++)
        cout<<Tree[i]<<'\t';
}
int main(int argc, const char * argv[]) {
    KeyType Tree[2*K];
    for(int i=0;i<2*K;i++)
      Tree[i]=-1;
    Init_tree(Tree);
    show(Tree);
    cout<<endl;
    int final_win;
    while(true)
    {
        final_win=getWinner(Tree);
        if(final_win!=0x7fffffff)
        {
        cout<<final_win<<endl;
        show(Tree);
        cout<<endl;
        }
        else
            break;
    }
    return 0;
}
