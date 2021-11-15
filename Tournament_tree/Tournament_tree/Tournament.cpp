//
//  Tournament.cpp
//  Tournament_tree
//
//  Created by PorUnaCabeza on 2021/11/3.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Tournament.hpp"
#define first_key(m) (candidate[m][Index[m]])
#define MaxInt 0x7fffffff
KeyType candidate[K][Capacity+1]={{10,15,31,MaxInt,MaxInt,MaxInt},{9,20,MaxInt,MaxInt,MaxInt,MaxInt},
{22,34,37,MaxInt,MaxInt,MaxInt},{6,15,42,MaxInt,MaxInt,MaxInt},{12,37,MaxInt,MaxInt,MaxInt,MaxInt},{84,95,MaxInt,MaxInt,MaxInt,MaxInt}}; //Hold K way's keys
int Index[K];//record each way's index
#define swap(a,b) \
{     \
KeyType temp;\
temp=a;\
a=b;\
b=temp;\
}
//O(logK),choose the cadidate of jth way,and let it battle up(battle with its parent), the loser stay in the parent node, the winner continue to battle up with grand parent and so on.
static void Battle_up(int *Tree, int &j, int &temp_win) {
    while(j)
    {
        if(Tree[j/2]==-1)
        {
            Tree[j/2]=temp_win;
            break;
        }
        else if(first_key(temp_win)>first_key(Tree[j/2]))
        {
            swap(temp_win, Tree[j/2]);
        }
        j/=2;
    }
}

void Init_tree(KeyType* Tree)
{
    memset(Index, 0, K*sizeof(int));
    for(int i=K;i<2*K;i++)
        Tree[i]=i-K;
    for(int i=2*K-1;i>=K;i--)
    {
        int j=i;
        int temp_win=Tree[j];
        Battle_up(Tree, j, temp_win);
    }
}
KeyType getWinner(KeyType* Tree)
{
    int way_of_win=Tree[0];
    Tree[0]=-1;
    KeyType final_win=first_key(way_of_win); //This needs return
    Index[way_of_win]=Index[way_of_win]==Capacity?Capacity:Index[way_of_win]+1;
    int j=way_of_win+K;
    int temp_win=Tree[j];
    Battle_up(Tree, j, temp_win);
    
    return final_win;
}

