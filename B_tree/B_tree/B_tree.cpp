//
//  B_tree.cpp
//  B_tree
//
//  Created by PorUnaCabeza on 2021/4/1.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "B_tree.hpp"
#define M 5  //at most M children and M-1 keys for each interior node
#define EmptyValue 0x7fffffff
struct BTreeNode{
    int key_length;
    BTree Children[M+1];  //allocate one more redundant space for insertion
    ElementType Keys[M];  //...
};
struct PathRecord{
    int index;
    Position THIS;
};
typedef PathRecord *Path;
Path Create_a_path()
{
    Path new_point=(Path)malloc(sizeof(struct PathRecord));
    if(new_point==NULL)
    {
        printf("Out of space.\n");
        exit(0);
    }
    return new_point;
}
//Find a path to the node that X reside (if X does exist)
//Find a path to the node that X should be inserted into(if X does not exist)
//return the index(position) of X in its node (if X does exist)
//return the index(position) of X in the node that it should be inserted into(if X does not exist)
Path FindSubTree(ElementType X,Position P,stack<Path>& path,int &exist)
{
    int i;
    int found=0;
    do{
        found=0;
    for(i=0;i<P->key_length;i++)
    {
        if(X<P->Keys[i])
            break;
        else if(X==P->Keys[i])
            {
                found=1;
                exist=1;
                break;
            }
    }
    if(found||P->Children[0]==NULL)  //We have found the key or we have reached a leaf
    {
        Path destination=Create_a_path();
        destination->index=i;
        destination->THIS=P;
        return destination;
    }
    else    //record the path
    {
    Path new_point=Create_a_path();
    new_point->index=i;  //The index to insert a new key if necessiary
    new_point->THIS=P;   //Save the pointer to the current node
    path.push(new_point);
    P=P->Children[i];
    }
    }while(true);
}
static Position FindLeftMax(Position P)
{
    while(P->Children[P->key_length]!=NULL)
    {
        P=P->Children[P->key_length];
    }
    return P;
}
static Position FindRightMin(Position P)
{
    while(P->Children[0]!=NULL)
    {
        P=P->Children[0];
    }
    return P;
}
void move_back_k(int startkey,int endkey,int startchild,int endchild,int k,Position P)
{
    for(int i=endkey;i>=startkey;i--)
        P->Keys[i+k]=P->Keys[i];
    for(int i=endchild;i>=startkey;i--)
    P->Children[i+k]=P->Children[i];
}
void move_front_k(int startkey,int endkey,int startchild,int endchild,int k,Position P)
{
    for(int i=startkey;i<=endkey;i++)
        P->Keys[i-k]=P->Keys[i];
    for(int i=startchild;i<=endchild;i++)
        P->Children[i-k]=P->Children[i];
}
static void Create_node(BTree &T) {
    T=(BTree)malloc(sizeof(struct BTreeNode));
    if(T==NULL)
    {
        printf("Out of Space.\n");
        exit(0);
    }
    for(int i=0;i<M+1;i++)
        T->Children[i]=NULL;
    for(int i=0;i<M;i++)
        T->Keys[i]=-1;
}

static void clear(Position &current) {
    for(int i=current->key_length;i<M;i++)
    {
        current->Keys[i]=-1;
        current->Children[i+1]=NULL;
    }
}

static void split(Position &current, Path &father) {
    Position splitout;
    Create_node(splitout);
    for(int i=M/2+1;i<M;i++)
    {
        splitout->Keys[i-M/2-1]=current->Keys[i];
        splitout->Children[i-M/2-1]=current->Children[i];
    }
    splitout->Children[M-M/2-1]=current->Children[M];
    splitout->key_length=M-1-M/2;
    current->key_length=M/2;
    move_back_k(father->index, father->THIS->key_length-1,
                father->index+1,father->THIS->key_length,1,father->THIS);
    father->THIS->Keys[father->index]=current->Keys[M/2];
    father->THIS->Children[father->index+1]=splitout;
    father->THIS->key_length++;
    clear(current);
}

BTree Insert(ElementType X,BTree T)
{
    if(T==NULL)
    {
        Create_node(T);
        T->key_length=1;
        T->Keys[0]=X;
        return T;
    }
    else
    {
        stack<Path>path;
        Position P=T;
        int exist=0;
        Path destination=FindSubTree(X,P,path,exist);
        if(exist)
        {
            printf("The element has already in the tree.\n");
            return T;
        }
        else{    //insert first
               move_back_k(destination->index, destination->THIS->key_length-1,
                           destination->index+1, destination->THIS->key_length,1, destination->THIS);//insert into the leaf
               destination->THIS->Keys[destination->index]=X;
               destination->THIS->key_length++;
            if(destination->THIS->key_length==M) //we need to split
            {
                Position current=destination->THIS;
                Path father=NULL;
                bool flag=true;
                while(!path.empty())
                {
                    father=path.top();
                    path.pop();
                    split(current, father);
                    if(father->THIS->key_length<M)  //once the property of Btree holds we have finished the work!
                    {
                        flag=false;
                        break;
                    }
                    current=father->THIS;
                }
                if(flag) //special case ,we need to split the root(The only way to increase the height of the BTree)
                {
                    BTree new_root;
                    Create_node(new_root);
                    new_root->key_length=0;
                    Path New_root=Create_a_path(); //The reason I introduce New_root is to call the split function
                    //Not to be confused !!!
                    New_root->THIS=new_root;
                    New_root->index=0;
                    split(current, New_root);
                    new_root->Children[0]=current;
                    T=new_root;
                }
            }
        }
    }
    return T;
}
static void borrow_left(Path destination, Path father) {
    Position leftsibling=father->THIS->Children[father->index-1];
    move_back_k(0, destination->index-1,0, destination->index-1,1, destination->THIS);
    destination->THIS->Keys[0]=father->THIS->Keys[father->index-1];
    father->THIS->Keys[father->index-1]=leftsibling->Keys[leftsibling->key_length-1];
    destination->THIS->Children[0]=leftsibling->Children[leftsibling->key_length];
    leftsibling->key_length--;
    clear(leftsibling);
}

static void borrow_right(Path destination, Path father) {
    Position rightsibling=father->THIS->Children[father->index+1];
    move_front_k(destination->index+1, destination->THIS->key_length-1,
                 destination->index+1, destination->THIS->key_length,1,destination->THIS);
    destination->THIS->Keys[destination->THIS->key_length-1]=father->THIS->Keys[father->index];
    father->THIS->Keys[father->index]=rightsibling->Keys[0];
    destination->THIS->Children[destination->THIS->key_length]=rightsibling->Children[0];
    move_front_k(1, rightsibling->key_length-1,1, rightsibling->key_length,1, rightsibling);
    rightsibling->key_length--;
    clear(rightsibling);
}

static void merge_left(Path &destination, Path father) {
    Position leftsibling=father->THIS->Children[father->index-1];
    move_back_k(0, destination->index-1,0, destination->index-1,1, destination->THIS);
    destination->THIS->Keys[0]=father->THIS->Keys[father->index-1];
    move_back_k(0, destination->THIS->key_length-1,1, destination->THIS->key_length,leftsibling->key_length,destination->THIS);
    for(int i=0;i<leftsibling->key_length;i++)
        //copy the leftsibling's keys and children to the destination(current)
    {
        destination->THIS->Keys[i]=leftsibling->Keys[i];
        destination->THIS->Children[i]=leftsibling->Children[i];
    }
    destination->THIS->Children[leftsibling->key_length]=leftsibling->Children[leftsibling->key_length];
    destination->THIS->key_length+=leftsibling->key_length;
    free(leftsibling);
    father->THIS->Children[father->index-1]=NULL;
    father->THIS->Keys[father->index-1]=-1;
    father->index--;  //we must ensure that after merging the key and
    //child to be deleted from father has index index.
}

static void merge_right(Path destination, Path &father) {
    Position rightsibling=father->THIS->Children[father->index+1];
    move_front_k(destination->index+1,destination->THIS->key_length-1,destination->index+1,
             destination->THIS->key_length,1, destination->THIS);
    destination->THIS->Keys[destination->THIS->key_length-1]=father->THIS->Keys[father->index];
    move_back_k(0, rightsibling->key_length-1,0, rightsibling->key_length,destination->THIS->key_length,rightsibling);
    for(int i=0;i<destination->THIS->key_length;i++)
        //copy the rightsibling's keys and children to the destination(current)
    {
        rightsibling->Keys[i]=destination->THIS->Keys[i];
        rightsibling->Children[i]=destination->THIS->Children[i];
    }
    rightsibling->key_length+=destination->THIS->key_length;
    free(destination->THIS);
    father->THIS->Children[father->index]=NULL;
    father->THIS->Keys[father->index]=-1;
}

BTree Delete(ElementType X ,BTree T)
{
    int minnumkey=(M%2?M/2+1:M/2)-1 ;
    if(T==NULL)
    {
        printf("Error,the tree T is empty.\n");
        return T;
    }
    stack<Path>path;
    Position P=T;
    int exist=0;
    Path destination=FindSubTree(X,P,path,exist);
    if(!exist)
    {
        printf("Error,The element to be deleted is not in the tree.\n");
        exit(0);
    }
    if(destination->THIS->Children[0]==NULL)//if the element to be deleted is in a leaf
    {
    do
        {
            if(destination->THIS->key_length>minnumkey) //the number of keys in the leaf is grater than minnumkey(so                                             the property of BTree holds!)
            {
                //index is to be deleted wheater key or child
                if(destination->THIS->Children[destination->index]!=NULL)
                {
                free(destination->THIS->Children[destination->index]);
                    destination->THIS->Children[destination->index]=NULL;
                }
                move_front_k(destination->index+1, destination->THIS->key_length-1,destination->index+1, destination->THIS->key_length,1,destination->THIS);
                destination->THIS->key_length--;
                clear(destination->THIS);
                break;
            }
            else
            {
                if(path.empty())  //The node is root
                {
                    if(destination->THIS->key_length>1)//The root has more than one keys,Btree property holds!
                    {
                        move_front_k(destination->index+1, destination->THIS->key_length-1,
                                     destination->index+1, destination->THIS->key_length,1,destination->THIS);
                        destination->THIS->key_length--;
                        clear(destination->THIS);
                        return destination->THIS;
                    }
                    else  //the node has only one key,shrink the tree(the only way to lose height)
                    {
                        Position right=destination->THIS->Children[1];
                        return right;
                    }
                }
                Path father=path.top();
                path.pop();
                if(father->index>0&&   //the current node has left sibling
                   father->THIS->Children[father->index-1]->key_length>minnumkey) //borrow from left sibling
                {
                    borrow_left(destination, father);
                    break;
                }
                else if(father->index<father->THIS->key_length&& //the current node has right sibling
                     father->THIS->Children[father->index+1]->key_length>minnumkey   )//borrow from right sibling
                {
                    borrow_right(destination, father);
                    break;
                }
                else if(father->index>0)  //the current node has left sibling,merge with the left sibling to current
                {
                    merge_left(destination, father);
                    destination=father;
                    
                }
                else if(father->index<father->THIS->key_length)//the current node has right sibling,
                    //merge with the right sibling to right sibling
                {
                    merge_right(destination, father);
                    destination=father;
                }
            }
        }while(true);
    }
    else  //deal with interior node ,we transform it into deleting leaf node
    {
        Position current=destination->THIS;
        int index=destination->index;
        Position rightmin=FindRightMin(current->Children[index+1]);
        
        if(rightmin->key_length>minnumkey)  //we try our best to delete the key from the node that has more than minnumkey
        {
            ElementType alternation=rightmin->Keys[0];
            Delete(alternation, T);
            current->Keys[index]=alternation;//It's safe to do so
        }
        else{
            stack<Path>path;
            int exist;
            //if the right try has failed,we must use left wheater it has more than minnum
            Position leftmax=FindLeftMax(current->Children[index]);
            ElementType tobedelete=current->Keys[index];
            ElementType alternation=leftmax->Keys[leftmax->key_length-1];
            Delete(alternation, T);
            Path destination=FindSubTree(tobedelete, T, path, exist);
            destination->THIS->Keys[destination->index]=alternation;
        }
    }
    return T;
}
