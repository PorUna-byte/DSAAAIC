//
//  Suffix_tree.cpp
//  Suffix_tree
//
//  Created by PorUnaCabeza on 2021/11/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Suffix_tree.hpp"

#define Unmark -1
#define MarkX -2
#define MarkY -3
#define MarkXY -4
int SuffixTreeNode::edgeLength()
{
    return *end-start+1;
}
bool SuffixTreeNode::walkDown()
{
    /*activePoint change for walk down (APCFWD) using
     Skip/Count Trick (Trick 1). If activeLength is greater
     than current edge length, set next internal node as
     activeNode and adjust activeEdge and activeLength
     accordingly to represent same activePoint*/
    if (HomeTree->activeLength >= edgeLength())
    {
        //Actually,there is no need to adjust activeEdge here!
        HomeTree->activeLength -= edgeLength();
        HomeTree->activeNode = this;
        return true;
    }
    return false;
}
/*
Rule 1 adds a new character on existing leaf edge
Rule 2 creates a new leaf edge (And may also create new internal node, if the path label ends in between an edge)
Rule 3 ends the current phase (when current character is found in current edge being traversed
 activeNode: This could be root node or an internal node.
 activeEdge: When we are on root node or internal node and we need to walk down, we need to know which edge to choose. activeEdge will store that information. In case, activeNode itself is the point from where traversal starts, then activeEdge will be set to next character being processed in next phase.
 activeLength: This tells how many characters we need to walk down (on the path represented by activeEdge) from activeNode to reach the activePoint where traversal starts. In case, activeNode itself is the point from where traversal starts, then activeLength will be ZERO.
 */
void SuffixTree::extendSuffixTree(int pos)
{
    /*Extension Rule 1, this takes care of extending all
     leaves created so far in tree*/
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode=NULL;
    //Add all suffixes (yet to be added) one by one in tree
    while(remainingSuffixCount > 0) {
        if(activeLength==0)  //APCFALZ
            activeEdge=(int)text[pos];
        // There is no outgoing edge starting with
        // activeEdge from activeNode
        if (activeNode->children[activeEdge] == NULL)
        {
            //Extension Rule 2 (A new leaf edge gets created)
            activeNode->children[activeEdge] =new SuffixTreeNode(pos,&leafEnd,this);
            if(lastNewNode!=NULL)
            {
                lastNewNode->suffixLink=activeNode;
                lastNewNode=NULL;
            }
        }
        else
        {
            SuffixTreeNode* next=activeNode->children[activeEdge];
            if(next->walkDown())
                continue; // start from next node (the new activeNode)
            
            /*Extension Rule 3 (current character being processed
             is already on the edge)*/
            if (text[next->start + activeLength] == text[pos])
            {
                //If a newly created node waiting for it's
                //suffix link to be set, then set suffix link
                //of that waiting node to current active node
                if(lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                
                //APCFER3
                activeLength++;
                /*STOP all further processing in this phase
                 and move on to next phase*/
                break;
            }
            /*We will be here when activePoint is in middle of
             the edge being traversed and current character
             being processed is not on the edge (we fall off
             the tree). In this case, we add a new internal node
             and a new leaf edge going out of that new node. This
             is Extension Rule 2, where a new leaf edge and a new
             internal node get created*/
            splitEnd=new int;
            *splitEnd=next->start+activeLength-1;
            //new internal node
            SuffixTreeNode* split=new SuffixTreeNode(next->start,splitEnd,this);
            activeNode->children[activeEdge]=split;
            
            //New leaf coming out of new internal node
            split->children[(int)text[pos]] =new SuffixTreeNode(pos, &leafEnd,this);
            
            next->start += activeLength;
            split->children[(int)text[*splitEnd+1]] = next;
            if(lastNewNode!=NULL)
                lastNewNode->suffixLink=split;
            lastNewNode=split;
        }
        remainingSuffixCount--;
        if(activeNode==root&&activeLength>0) //APCFER2C1
        {
            activeLength--;
            activeEdge=(int)text[pos-remainingSuffixCount+1];
        }
        else if(activeNode!=root) //APCFER2C2
            activeNode=activeNode->suffixLink;
    }
}
void SuffixTree::print(int i, int j)
{
    for(int k=i;k<=j;k++)
        printf("%c",text[k]);
    cout<<endl;
}
//Print the suffix tree as well along with setting suffix index
//So tree will be printed in DFS manner
//Each edge along with it's suffix index will be printed
void SuffixTree::setSuffixIndexByDFS(SuffixTreeNode *n, int labelHeight)
{
    if(n==NULL) return;
//    if(n->start!=-1) //a non-root node
//        print(n->start,*(n->end));
    bool leaf = true;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
//            if (leaf == 1 && n->start != -1)
//                printf(" [%d]\n", n->suffixIndex);
            
            //Current node is not a leaf as it has outgoing
            //edges from it.
            leaf =false;
            setSuffixIndexByDFS(n->children[i],
                                labelHeight + n->children[i]->edgeLength());
        }
    }
    if (leaf)
    {
        //prune the second string
        for(int i=n->start;i<=*(n->end);i++)
        {
            if(text[i]=='#')
            {
                n->end=new int;
                *(n->end)=i;
            }
        }
        n->suffixIndex = size - labelHeight;
//        printf(" [%d]\n", n->suffixIndex);
    }
}
void SuffixTree::freeSuffixTreeByPostOrder(SuffixTreeNode *n)
{
    if(n==NULL)
        return;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if(n->suffixIndex==-1)
        delete n->end;
    delete n;
}
//This takes time O(n) where n is the length of text to build a suffix tree.
SuffixTree::SuffixTree(string text)
{
    this->text=text;
    size=(int)text.length();
    rootEnd=new int;
    *rootEnd=-1;
    root=new SuffixTreeNode(-1,rootEnd,this);
    activeNode=root;
    for(int i=0;i<size;i++) //m phase,one for each character
        extendSuffixTree(i);
    setSuffixIndexByDFS(root, 0);
}
SuffixTree::~SuffixTree()
{
    freeSuffixTreeByPostOrder(root);
}
int SuffixTreeNode::search_down()
{
    if(suffixIndex!=-1) //Leaf node
    {
        cout<<"Found at position "<<suffixIndex<<endl;
        return 1;
    }
    else //internal node
    {
        int count=0;
        for(int i=0;i<MAX_CHAR;i++)
            if(children[i])
                count+=children[i]->search_down();
        return count;
    }
}
int SuffixTree::search(string pattern)
{
    int index_p=0;
    int index_e=0;
    int length=(int)pattern.length();
    SuffixTreeNode* current_node=root->children[pattern[index_p]];
    while(current_node!=NULL)
    {
        index_e=0;
        while((current_node->start+index_e<=*(current_node->end))&&index_p<length)
        {
            if(text[current_node->start+index_e]==pattern[index_p])
            {
                index_p++;
                index_e++;
            }
            else
                return 0; //mismatch
        }
        if(index_p<length)
        current_node=current_node->children[pattern[index_p]];
        else  //the pattern has been found in the suffix tree.
            return current_node->search_down();
    }
    return 0;
}
void SuffixTreeNode::do_longest_repeat(int levelHeight,int &maxHeight,int &startIndex)
{
    if(suffixIndex==-1)  //current node is an internal node.
    {
        for(int i=0;i<MAX_CHAR;i++)
            if(children[i])
                children[i]->do_longest_repeat(levelHeight+children[i]->edgeLength(), maxHeight, startIndex);
    }
    else        //current node is a leaf
    {
        if(levelHeight-edgeLength()>maxHeight)
        {
            maxHeight=levelHeight-edgeLength();
            startIndex=suffixIndex;
        }
    }
}
void SuffixTree::longest_repeat()
{
    int maxHeight=0,startIndex=-1;
    root->do_longest_repeat(0, maxHeight, startIndex);
    if(startIndex!=-1)
    {
        cout<<"The longest repeated substring is:"<<endl;
        print(startIndex, startIndex+maxHeight-1);
    }
    else
        cout<<"There is no repeated substring"<<endl;
}
void SuffixTree::set_size_x(int size_x)
{
    this->size_x=size_x;
}
int SuffixTreeNode::do_longest_common(int levelHeight,int &maxHeight,int &startIndex)
{
    int ret=Unmark;
    if(suffixIndex<0) //An internal node
    {
        for(int i=0;i<MAX_CHAR;i++)
        {
            if(children[i])
            {
                ret=children[i]->do_longest_common(levelHeight+children[i]->edgeLength(), maxHeight, startIndex);
            }
            if(suffixIndex==Unmark)
                suffixIndex=ret;
            else if(suffixIndex!=ret)
            {
                suffixIndex=MarkXY;
                //keep track of deepest node
                if(maxHeight<levelHeight)
                {
                    maxHeight=levelHeight;
                    startIndex=*end-levelHeight+1;
                }
            }
        }
    }
    else if(suffixIndex<HomeTree->size_x)  //leaf node
        return MarkX;
    else if(suffixIndex>=HomeTree->size_x)
        return MarkY;
    return suffixIndex;
}
void SuffixTree::longest_common()
{
    int maxHeight=0,startIndex=-1;
    root->do_longest_common(0, maxHeight, startIndex);
    if(startIndex!=-1)
    {
        cout<<"The longest common substring is:"<<endl;
        print(startIndex, startIndex+maxHeight-1);
    }
    else
        cout<<"There is no common substring"<<endl;
}
