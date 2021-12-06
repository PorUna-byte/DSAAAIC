//
//  Trie.hpp
//  Trie
/*
Trie (also named prefix tree) is an efficient information reTrieval data structure. Using Trie, search complexities can be brought to optimal limit (key length).
 */
//  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
const int ALPHABET_SIZE=26;
class TrieNode{
public:
    TrieNode* children[ALPHABET_SIZE];
    bool IsEndofNode;
    TrieNode(){
        IsEndofNode=false;
        memset(children,0,sizeof(TrieNode*)*ALPHABET_SIZE);
    }
};
class Trie{
private:
    TrieNode* root;
    /*
     Recursive function to delete a key from given Trie
     During delete operation we delete the key in bottom up manner using recursion. The following are possible conditions when deleting key from trie,
     Key may not be there in trie. Delete operation should not modify trie.
     Key present as unique key (no part of key contains another key (prefix), nor the key itself is prefix of another key in trie). Delete all the nodes.
     Key is prefix key of another long key in trie. Unmark the leaf node.
     Key present in trie, having atleast one other key as prefix key. Delete nodes from end of key until first leaf node of longest prefix key.
     */
    TrieNode* remove_util(TrieNode* parent,string key, int depth);
public:
    Trie(){
        root=new TrieNode();
    }
    // If not present, inserts key into trie
    // If the key is prefix of trie node, just marks leaf node
    // O(|key|)
    void insert(string key);
    
    // Returns true if key presents in trie, else false
    // O(|key|)
    bool search(string key);
    
    //mainly calls remove_util
    void remove(string key);
    
    
};
#endif /* Trie_hpp */
