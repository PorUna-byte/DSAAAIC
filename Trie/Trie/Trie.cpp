//
//  Trie.cpp
//  Trie
//
//  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Trie.hpp"
#define Index(i) \
(key[i]-'a')

bool IsEmpty(TrieNode* pt)
{
    for(int i=0;i<ALPHABET_SIZE;i++)
        if(pt->children[i])
            return false;
    return true;
}
void Trie::insert(string key)
{
    TrieNode* pCrawl=root;
    for(int i=0;i<key.length();i++)
    {
        if(!pCrawl->children[Index(i)])
            pCrawl->children[Index(i)]=new TrieNode();
        pCrawl=pCrawl->children[Index(i)];
    }
    pCrawl->IsEndofNode=true;
}
bool Trie::search(string key)
{
    TrieNode* pCrawl=root;
    for(int i=0;i<key.length();i++)
    {
        if(!pCrawl->children[Index(i)])
            return false;
        pCrawl=pCrawl->children[Index(i)];
    }
    return pCrawl->IsEndofNode;
}
TrieNode* Trie::remove_util(TrieNode* cur,string key, int depth)
{
    if(!cur)  //if current node does not exist,we know the key is not in the trie ,just return(do nothing).
        return NULL;
    if(depth==key.length()) //the key is in the trie(we have searched it)
    {
        if(IsEmpty(cur))  //the key is not a prefix of another key,just delete current node.
        {
            delete cur;
            return NULL;
        }
        else
            cur->IsEndofNode=false;
    }
    else  //we are searching down the key
    {
        cur->children[Index(depth)]=remove_util(cur->children[Index(depth)], key, depth+1);
        if(IsEmpty(cur)&&!cur->IsEndofNode)  //current node may become empty after deletion of child.
        {
            delete cur;
            return NULL;
        }
    }
    return cur;
}
void Trie::remove(string key)
{
    remove_util(root, key, 0);
}
