//
//  OpenAddrHash.c
//  OpenAddrHash
//
//  Created by PorUnaCabeza on 2021/4/22.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "OpenAddrHash.h"
#define MinTableSize 5
enum KindOfEntry{Legitimate,Empty,Deleted};
struct HashEntry{
    ElementType Element;
    enum KindOfEntry Info;
};
typedef struct HashEntry Cell;
struct HashTbl {
    int TableSize;
    int Counts;  //the number of Entry that marked as legitimate or deleted
    Cell *TheCells;
};
int Hash_Func(int TableSize,ElementType key) //needs optimization
{
    return key%TableSize;
};
//return the smallest prime that bigger than N
int NextPrime(int N){
    if(N%2==0)  //a prime must be an odd number
        N++;
    int i;
    while(1) {
        for(i=3;i*i<=N;i+=2)  //the routine to judege if N is a prime or not
        {
            if(N%i==0)  //Not a prime
                goto out;
        }
        return N;  //if the program comes here,we can say N is a prime . return it.
    out:
        N+=2;
    }
}
//return the largest prime that smaller than N
int PrePrime(int N){
    N=N-1;
    if(N%2==0)  //a prime must be an odd number
        N--;
    int i;
    while(1) {
        for(i=3;i*i<=N;i+=2)  //the routine to judege if N is a prime or not
        {
            if(N%i==0)  //Not a prime
                goto out;
        }
        return N;  //if the program comes here,we can say N is a prime . return it.
    out:
        N-=2;
    }
}
HashTable Initialize(int TableSize)
{
    HashTable H;
    if(TableSize<MinTableSize)
    {
        printf("Table Size should bigger than %d\n",MinTableSize);
        return NULL;
    }
    H=(HashTable)malloc(sizeof(struct HashTbl));
    if(H==NULL)
    {
        printf("Out of Space.\n");
        exit(1);
    }
    H->TableSize=NextPrime(TableSize);
    H->Counts=0;
    H->TheCells=(Cell*)malloc(sizeof(Cell)*H->TableSize);
    if(H->TheCells==NULL)
    {
        printf("Out of Space\n");
        exit(1);
    }
    for(int i=0;i<H->TableSize;i++)
    {
        H->TheCells[i].Info=Empty;
        H->TheCells[i].Element=-1;
    }
    return H;
}
void DropTable(HashTable H)
{
    free(H->TheCells);
    free(H);
}
Position Find_quadratic(ElementType Key,HashTable H) //quadratic probing
{
    Position Cur;
    int CollisionNum;
    CollisionNum=0;
    Cur=Hash_Func(H->TableSize,Key);
    while(H->TheCells[Cur].Info!=Empty&&H->TheCells[Cur].Element!=Key)
    {
        Cur+=2 * ++CollisionNum -1;
        if(Cur>=H->TableSize)
            Cur-=H->TableSize;
    }
    return Cur;
}
Position Find_doublehash(ElementType Key,HashTable H) //double hash  probing
{
    Position Cur;
    int origin=Hash_Func(H->TableSize,Key);
    int R=PrePrime(H->TableSize);
    int Hash2=R-(Key%R);
    Cur=origin;
    while(H->TheCells[Cur].Info!=Empty&&H->TheCells[Cur].Element!=Key)
    {
        Cur+=Hash2;
        if(Cur>=H->TableSize)
            Cur-=H->TableSize;
    }
    return Cur;
}

HashTable Rehash(HashTable H)
{
    int legitimate_num=0;
    for(int i=0;i<H->TableSize;i++)
    {
        if(H->TheCells[i].Info==Legitimate)
            legitimate_num++;
    }
    HashTable new_Table=Initialize(4*legitimate_num);//4 is a magic number
    for(int i=0;i<H->TableSize;i++)
    {
        if(H->TheCells[i].Info==Legitimate)
            new_Table=Insert(H->TheCells[i].Element, new_Table);
    }
    DropTable(H);
    return new_Table;
}
HashTable Insert(ElementType key,HashTable H)
{
    Position position=Find_doublehash(key, H);
    if(H->TheCells[position].Info==Empty)
    {
        H->TheCells[position].Element=key;
        H->TheCells[position].Info=Legitimate;
        H->Counts++;
    }
    else if(H->TheCells[position].Info==Deleted){
        H->TheCells[position].Info=Legitimate;
    }
    else
    {
        printf("The key:%d is already in the table.",key);
        return H;
    }
    if(H->Counts==H->TableSize/2)//once the counts reachs the half of tablesize we need to rehash!
    {
        H=Rehash(H);
    }
    return H;
}
HashTable Delete(ElementType key,HashTable H)//Delete will never change the value of counts,so delete routine doesn't contain rehash operation(which is in contrast of insert)
{
    Position position=Find_doublehash(key, H);
    if(H->TheCells[position].Info==Empty||H->TheCells[position].Info==Deleted)
    {
        printf("The key:%d is not in the hashtable",key);
        return H;
    }
    else if(H->TheCells[position].Info==Legitimate)
    {
        H->TheCells[position].Info=Deleted;
    }
    return H;
}
void ShowTable(HashTable H)
{
    printf("number\t|\tkey\tinfo\n");
    for(int i=0;i<H->TableSize;i++)
    {
        printf("%d\t\t|\t%d ",i,H->TheCells[i].Element);
        if(H->TheCells[i].Info==Empty)
            printf("Empty");
        else if(H->TheCells[i].Info==Deleted)
            printf("Deleted");
        else
            printf("Legitimate");
        printf("\n");
    }
}
