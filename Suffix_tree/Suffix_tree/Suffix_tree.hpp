//
//  Suffix_tree.hpp
//  Suffix_tree
/*
 Please refer to https://www.geeksforgeeks.org/ukkonens-suffix-tree-construction-part-6
 for more detail.
 The construct algorithm of suffix tree is proposed by Ukkonen in 1995.
 A Suffix Tree for a given text is a compressed trie for all suffixes of the given text.
 Problem Statement: Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[]. You may assume that n > m.
 As discussed in the previous post, we discussed that there are two ways efficiently solve the above problem.
 1) Preprocess Pattern: KMP Algorithm, Rabin Karp Algorithm, Finite Automata, Boyer Moore Algorithm.
 2) Preprocess Text: Suffix Tree
 
 The best possible time complexity achieved by first (preprocssing pattern) is O(n) and by second (preprocessing text) is O(m) where m and n are lengths of pattern and text respectively.

 Note that the second way does the searching only in O(m) time and it is preferred when text doesn’t doesn’t change very frequently and there are many search queries.
 */
//  Created by PorUnaCabeza on 2021/11/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#ifndef Suffix_tree_hpp
#define Suffix_tree_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
const int MAX_CHAR=256;
class SuffixTreeNode;
class SuffixTree{
private:
    string text;
    SuffixTreeNode* root=NULL;
    SuffixTreeNode* lastNewNode=NULL;
    SuffixTreeNode* activeNode=NULL;
    int count=0;
    int activeEdge=-1;
    int activeLength=0;
    int remainingSuffixCount=0;
    int leafEnd=-1;
    int *rootEnd=NULL;
    int *splitEnd=NULL;
    int size=-1;
    int size_x=-1;
    //Print the suffix tree as well along with setting suffix index
    //So tree will be printed in DFS manner
    //Each edge along with it's suffix index will be printed
    void setSuffixIndexByDFS(SuffixTreeNode *n, int labelHeight);
    void extendSuffixTree(int pos);
    void print(int i, int j);
    void freeSuffixTreeByPostOrder(SuffixTreeNode* n);
public:
    friend class SuffixTreeNode;
    //search for the pattern in the (suffix tree of)text,return all its occurrence.
    //O(M+C) M is the length of pattern, and C is the times of its occurrence.
    //Note that we don't take the time to build a suffix tree,which is O(N), into account.
    int search(string pattern);
    //search for the longest repeated substring
    //O(N) N is the length of text,which is the time to build a suffix tree.
    void longest_repeat();
    //search for the longest common substring in two strings
    //O(N) N is the addition of two string's length.
    void longest_common();
    void set_size_x(int size_x);
    SuffixTree(string text);
    ~SuffixTree();
};
class SuffixTreeNode{
private:
    SuffixTreeNode* children[MAX_CHAR];
    SuffixTreeNode* suffixLink;
    SuffixTree* HomeTree;
    int start;
    int *end;
    int suffixIndex;
    SuffixTreeNode(int start,int* end,SuffixTree* HomeTree){
        HomeTree->count++;
        memset(children, 0, sizeof(SuffixTreeNode*)*MAX_CHAR);
        suffixLink=HomeTree->root;
        this->HomeTree=HomeTree;
        this->start=start;
        this->end=end;
        suffixIndex=-1;
    }
    int edgeLength();
    bool walkDown();
    int search_down();
    void do_longest_repeat(int levelHeight,int &maxHeight,int &startIndex);
    int do_longest_common(int levelHeight,int &maxHeight,int &startIndex);
public:
    friend class SuffixTree;
};

#endif /* Suffix_tree_hpp */
