//
//  SepCh.h
//  SepChHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef SepCh_h
#define SepCh_h
#define ElementType int
#include <stdio.h>
#include <stdlib.h>
struct ListNode;
typedef struct ListNode *Position;
struct Hashtbl;
typedef struct Hashtbl *HashTable;
int Hash_Func(int TableSize,ElementType key);
//Initialize the hashtable(includes initialize header for each list)
HashTable Initialize(int TableSize);
//Find the pre position of the key
//if the key does not exist return null.
Position FindKeyPre(ElementType key,HashTable H);
//Insert a key into the hash table
//if the key already exists,do nothing
void Insert(ElementType key,HashTable H);
//Delete the key from the hashtable
//if not exist,do nothing.
void Delete(ElementType key,HashTable H);
//drop the hash table
void DropTable(HashTable table);
//print the table
void ShowTable(HashTable table);
#endif /* SepCh_h */
