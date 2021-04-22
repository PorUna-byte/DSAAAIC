//
//  OpenAddrHash.h
//  OpenAddrHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef OpenAddrHash_h
#define OpenAddrHash_h

#include <stdio.h>
#include <stdlib.h>
typedef unsigned int Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
#define ElementType int
//Initialize the hashtable
HashTable Initialize(int TableSize);
//Drop the table,free sapce
void DropTable(HashTable H);
//Find the position of the key Key if the key exist
//Find the position of an empty cell that can hold the key if the key not exist
Position Find_quadratic(ElementType Key,HashTable H);//quadratic probing
Position Find_doublehash(ElementType Key,HashTable H);//double hash probing
//Insert the key into the hash table
//if the key already exist ,do nothing
HashTable Insert(ElementType key,HashTable H);
//Delete the key from hash table
//if the key does not exist,do nothing
HashTable Delete(ElementType key,HashTable H);
//extend the table once the load factor reachs 1/2 after insert a new element.
HashTable Rehash(HashTable H);
//print the table
void ShowTable(HashTable H);
#endif /* OpenAddrHash_h */
