//
//  RB_tree.cpp
//  RB_tree
//
//  Created by PorUnaCabeza on 2021/7/20.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//
/*
 The following code are formed from the pseudocode of Introduction to Algorithm
 Please refer to that book for more detail.
 */
#include "RB_tree.hpp"
#include <stack>
enum Direction{none,l,r};
typedef struct pioneer  //Used to verify a red-black tree.
{
    Node* node;
    enum Direction direction;
}Pioneer;
void oom(){
    printf("out of memory\n");
    exit(-1);
}
void *Malloc(size_t size)//A simple warpper to simplify the code
{
    void *ptr=malloc(size);
    if(ptr==NULL)
        oom();
    return ptr;
}
Tree* Init_RBT(){
    Tree* T=(Tree*)Malloc(sizeof(Tree));
    T->nil=(Node*)Malloc(sizeof(Node));
    T->nil->color=black;//color is black
    T->nil->key=sentinel;//key is sentinel for convenience
    T->nil->parent=T->nil->left=T->nil->right=NULL;//parent,left,right can be arbitrary value
    T->nil->element=0;//element can be arbitrary value
    T->root=T->nil; //This means an empty tree
    return T;
}
static void print_node(int level, Node *x) {
    for(int i=0;i<level;i++)
        cout<<"  ";
    cout<<x->key<<" ";
    if(x->color==black)
        cout<<"black";
    else if(x->color==red)
        cout<<"red";
    cout<<endl;
}

void Print_tree(Tree* T)
{
    Node* x=T->root;
    int this_level=0;
    stack<Node*>sta;
    stack<int>level;
    while(!sta.empty()||x!=T->nil)
    {
        while(x!=T->nil)
        {
            sta.push(x);
            level.push(this_level);
            print_node(this_level++, x);
            x=x->left;
        }
        while(!sta.empty())
        {
            x=sta.top();
            this_level=level.top();
            level.pop();
            sta.pop();
            if(x->right!=T->nil)
            {
                sta.push(x->right);
                level.push(this_level+1);
                break;
            }
        }
        if(!sta.empty())
        {
            x=sta.top();
            this_level=level.top();
            sta.pop();
            level.pop();
        }
        else
            x=T->nil; //stop here.
    }
}
/*
 That is rotate x anti-clockwise relative to the right children of x.
 */
void Left_Rotate(Tree* T,Node* x)
{
    Node* y=x->right;
    x->right=y->left;
    if(y->left!=T->nil)
        y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==T->nil) //x is the root
        T->root=y;
    else if(x==x->parent->left)// x is the left children of its parent
        x->parent->left=y;
    else
        x->parent->right=y;
    y->left=x;
    x->parent=y;
}
/*
 Rotate x clockwise relative to the left children of x
 */
void Right_Rotate(Tree* T,Node* x)
{
    Node* y=x->left;
    x->left=y->right;
    if(y->right!=T->nil)
        y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==T->nil) //x is the root
        T->root=y;
    else if(x==x->parent->left)// x is the left children of its parent
        x->parent->left=y;
    else
        x->parent->right=y;
    y->right=x;
    x->parent=y;
}
void Insert_fixup(Tree* T,Node *z)
{
    Node* uncle;
    while(z->parent!=T->nil&&z->parent->parent!=T->nil&&z->parent->color==red)
    {
        if(z->parent==z->parent->parent->left)
        {
            uncle=z->parent->parent->right;
            if(uncle->color==red)
            {
                z->parent->color=black;  //case 1
                uncle->color=black;      //case 1
                z->parent->parent->color=red;//case 1
                z=z->parent->parent;  //continue to fix up at grandparent. case 1
            }
            else if(z==z->parent->right)
            {
                z=z->parent;  //case 2
                Left_Rotate(T, z);//case 2
            }
            else  //after this operation,we get a legal red-black tree.
            {
                z->parent->color=black;  //case 3
                z->parent->parent->color=red;//case 3
                Right_Rotate(T, z->parent->parent);//case 3
                z=T->root;
            }
        }
        else //symmetrical to the left situation
        {
            uncle=z->parent->parent->left;
            if(uncle->color==red)
            {
                z->parent->color=black;  //case 1
                uncle->color=black;      //case 1
                z->parent->parent->color=red;//case 1
                z=z->parent->parent;  //continue to fix up at grandparent. case 1
            }
            else if(z==z->parent->left)
            {
                z=z->parent;  //case 2
                Right_Rotate(T, z);//case 2
            }
            else  //after this operation,we get a legal red-black tree.
            {
                z->parent->color=black;  //case 3
                z->parent->parent->color=red;//case 3
                Left_Rotate(T, z->parent->parent);//case 3
            }
        }
    }
    T->root->color=black;
}
void Insert(Tree* T,KeyType key,ElementType element)
{
    Node* new_node=(Node*)Malloc(sizeof(Node));
    new_node->color=red; //To satisfy property 5th of RBT
    new_node->key=key;
    new_node->element=element;
    new_node->left=new_node->right=new_node->parent=T->nil;
    Node* y=T->nil;
    Node* x=T->root;
    while(x!=T->nil)
    {
        y=x;
        if(new_node->key<x->key)
            x=x->left;
        else if(new_node->key>x->key)
            x=x->right;
        else    //A node with key "key" has already exist
        {
//            printf("Insertion abort:The key %d is already exist\n",key);
            return ;
        }
    }
    new_node->parent=y;
    if(y==T->nil)  //This means an empty tree
        T->root=new_node;
    else if(new_node->key<y->key)
        y->left=new_node;
    else
        y->right=new_node;
    Insert_fixup(T, new_node); //fix the tree bottom-up.
    return ;
}
/*
 Transplant v to u's position that is: replace u by v
 */
void Transplant(Tree* T,Node* u,Node* v)
{
    if(u->parent==T->nil)//u is root
        T->root=v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
}
Node* findMin(Tree* T,Node* start)
{
    Node* x=start;
    while(x!=T->nil&&x->left!=T->nil)
        x=x->left;
    return x;
}
void Delete_fixup(Tree* T,Node* x)
{
    Node* sibling;
    while(x!=T->root&&x->color==black)//Now x has double black !!! please Always keep it in your mind.
    {
        if(x==x->parent->left)
        {
            sibling=x->parent->right;
            if(sibling->color==red) //case 1 will be transformed into case 2,3,or 4 after this routine.
            {
                sibling->color=black;  //case 1
                x->parent->color=red;  //case 1
                Left_Rotate(T, x->parent);//case 1
                sibling=x->parent->right;//case 1
            }
            if(sibling->left->color==black&&sibling->right->color==black)
            {
                /*
                 We take one black off both x and w,leaving x with only one black and leaving w red.
                 To compensate it, we would like to add one extra black to x->parent,which was originally either
                 red or black.We do so by repeating the while loop with x->parent as the new node x.
                 If x->parent was red originally, after this loop iteration, the next loop will fail,and we just mark
                 it black.
                 If x->parent was black originally, after this loop iteration, the next loop will continue,and we
                 just mark it double black!
                 */
                sibling->color=red;   //case 2
                x=x->parent;//continue at x->parent ,case 2
            }
            else if(sibling->right->color==black)//After this routine we transform the red black tree into case 4
            {
                sibling->left->color=black; //case 3
                if(sibling->right==T->nil&&sibling->left->right==T->nil)
                sibling->color=black;//case 3
                else
                sibling->color=red;
                Right_Rotate(T, sibling);//case 3
                sibling=x->parent->right;//case 3
            }
            else //After this routine the red black tree is legal, so we can terminate the while-loop
                //by setting x=T->root
            {
                sibling->color=x->parent->color;
                x->parent->color=black;
                sibling->right->color=black;
                Left_Rotate(T, x->parent);
                x=T->root;  //An ad-hoc to terminate the while-loop.
            }
        }
        else  //symmetrical to the left situation.
        {
            sibling=x->parent->left;
            if(sibling->color==red) //case 1 will be transformed into case 2,3,or 4 after this routine.
            {
                sibling->color=black;  //case 1
                x->parent->color=red;  //case 1
                Right_Rotate(T, x->parent);//case 1
                sibling=x->parent->left;//case 1
            }
            if(sibling->right->color==black&&sibling->left->color==black)
            {
                sibling->color=red;   //case 2
                x=x->parent;//continue at x->parent ,case 2
            }
            else if(sibling->left->color==black)//After this routine we transform the red black tree into case 4
            {
                sibling->right->color=black; //case 3
                if(sibling->left==T->nil&&sibling->right->left==T->nil)
                    sibling->color=black;//case 3
                else
                    sibling->color=red;
                Left_Rotate(T, sibling);//case 3
                sibling=x->parent->left;//case 3
            }
            else //After this routine the red black tree is legal, so we can terminate the while-loop
                //by setting x=T->root
            {
                sibling->color=x->parent->color;
                x->parent->color=black;
                sibling->left->color=black;
                Right_Rotate(T, x->parent);
                x=T->root;  //An ad-hoc to terminate the while-loop.
            }
        }
    }
    x->color=black;
}
bool Only_onechild(Tree* T,Node* x)
{
    return (x->left==T->nil&&x->right!=T->nil)||(x->left!=T->nil&&x->right==T->nil);
}
void Delete(Tree* T,KeyType key)
{
    Node* parent_of_deleted;
    Node* z=T->root;
    Node *y,*x;
    Color y_origin_color;
    bool no_child=false;
    bool parent_only_child=false;
    while(z!=T->nil)//find the node with key 'key' if the it exists.
    {
        if(key<z->key)
            z=z->left;
        else if(key>z->key)
            z=z->right;
        else
            break;
    }
    if(z==T->nil)
    {
//        printf("Dlete abort:The key %d is not found\n",key);
        return ;
    }
    y=z;  //y is the one to be deleted (It may be a victim.)
    y_origin_color=y->color;
    if(y->left==T->nil&&y->right==T->nil)
    {
        no_child=true;
        if(y->parent!=T->nil&&Only_onechild(T, y->parent))
            parent_only_child=true;
    }
    parent_of_deleted=y->parent;
    if(z->left==T->nil)
    {
        x=z->right;
        Transplant(T, z, z->right);
    }
    else if(z->right==T->nil)
    {
        x=z->left;
        Transplant(T, z, z->left);
    }
    else
    {
        y=findMin(T,z->right); //Note that y has no left child since y is the minimum in subtree, y is the victim
        y_origin_color=y->color;//record the origin color of y
        no_child=false;  //recompute these two flags
        parent_only_child=false;
        if(y->left==T->nil&&y->right==T->nil)
        {
            no_child=true;
            if(y->parent!=T->nil&&Only_onechild(T, y->parent))
                parent_only_child=true;
        }
        parent_of_deleted=y->parent;
        x=y->right;
        if(y->parent==z)
            x->parent=y;
        else  //we need some transformation to make y in the right child position of z.
        {
            Transplant(T, y, y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        Transplant(T, z, y);//replace z by y that is to delete z.
        y->left=z->left;
        y->left->parent=y;
        y->color=z->color; //y must extends z's color.
    }
    free(z);
    if(y_origin_color==black&&x!=T->nil)//if y's original color is red, nothing need to do, since all 5 properties still hold.
        Delete_fixup(T, x);
    if(y_origin_color==black&&no_child&&parent_only_child)//if y(z) has no child and it
        //is the only child of its parent, than the parent of y(z) has double black
        Delete_fixup(T, parent_of_deleted);
}
bool verify_RBT(Tree* T)
{
    int black_count=0;
    int black_ref=0;
    stack<Pioneer*>sta;
    Pioneer* x=(Pioneer*)Malloc(sizeof(Pioneer));
    x->node=T->root;
    x->direction=none;
    if(x->node->color!=black) //property 2
    {
        cout<<"root is not black!"<<endl;
        return false;
    }
    sta.push(x);
    //we preorder the tree somehow.
    while(!sta.empty())
    {
        x=sta.top();
        if(x->node->color==black&&x->direction!=none)
            black_count--;
        sta.pop();
        while(x->node!=T->nil)
        {
            if(x->node->left!=T->nil&&x->node->color==red&&x->node->left->color==red) //check property 4 as much(soon) as possible
            {
                cout<<"Two red nodes are adjacent"<<endl;
                return false;
            }
            if(x->node->right!=T->nil&&x->node->color==red&&x->node->right->color==red)//check property 4 as much(soon) as possible
            {
                cout<<"Two red nodes are adjacent"<<endl;
                return false;
            }
            if(x->node->color==black)  //record the number of black nodes in the path
                black_count++;
            sta.push(x);
            if(x->direction<l)
            {
                x->direction=l; //mark that left direction has already been tried.
                Node* left=x->node->left;
                x=(Pioneer*)Malloc(sizeof(Pioneer));
                x->direction=none;
                x->node=left;
            }
            else
                break;
        }
        if(!sta.empty())
           x=sta.top();
        else
            break;
        if(x->node->right!=T->nil&&x->direction<r)
        {
            x->direction=r; //mark that right direction has been tried
            Pioneer* tmp=(Pioneer*)Malloc(sizeof(Pioneer));
            tmp->direction=none;
            tmp->node=x->node->right;
            sta.push(tmp);
        }
        else 
        {
            if(x->node->right==T->nil&&x->node->left==T->nil)//we come to the bottom
            {
                if(black_ref==0)
                    black_ref=black_count;
                else if(black_ref!=black_count)//check property 5 at the bottom
                {
                    cout<<"black height error!"<<endl;
                    return false;
                }
            }
            if(x->node->color==black)
                black_count--;
            sta.pop();
        }
    }
    return true;
}
void free_tree(Tree* T)
{
    if(T->root==T->nil)
    {
        printf("empty tree!\n");
        return ;
    }
    Node* P=T->root;
    stack<Node*>sta;
    bool flag=true;
    Node* pre=T->nil;
    Node* R=T->nil;
    //An indication for left subtree.
    //if left subtree was visited before then flag=1,else 0.
    do{
        while(P!=T->nil)  //push all left subtrees
        {
            sta.push(P);
            P=P->left;
        }
        flag=true; //left subtree has been visited
        while(!sta.empty()&&flag)
        {
            R=sta.top();
            if(R->right!=T->nil&&R->right!=pre)//if has right subtree and right subtree was not visited before!
            {
                P=R->right; //traverse right subtree
                flag=false; //now,the right subtree's left subtree is not visited.
            }
            else
            {
                free(R);
                pre=R;  //set current node as pre,since current node is being visited!
                sta.pop();
            }
        }
    }
    while(!sta.empty());
    return ;
}
