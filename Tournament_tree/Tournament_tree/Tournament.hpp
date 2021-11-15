//
//  Tournament.hpp
//  Tournament_tree
//
//  Created by PorUnaCabeza on 2021/11/3.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 Tournament tree is a kind of complete tree which can be stored in an array properly.
 This data structure is used for K way merging sort. Time complexity is O(nlogn)
 */
#ifndef Tournament_hpp
#define Tournament_hpp

#include <stdio.h>
#include <iostream>

#define KeyType int
#define Capacity 5
#define K 6 //K way merge
//Initialize the Tournament tree by the first keys of each way(we have K ways)
//O(KlogK)
void Init_tree(KeyType* Tree);
//Get the final winner of the tournament tree and fix the tree to maintain Tournament tree's property.
//O(logK)
KeyType getWinner(KeyType* Tree);
#endif /* Tournament_hpp */
