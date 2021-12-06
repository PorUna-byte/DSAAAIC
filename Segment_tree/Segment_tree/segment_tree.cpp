//
//  segment_tree.cpp
//  Segment_tree
//
//  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "segment_tree.hpp"
int getmid(int start,int end)
{
    return (start+end)/2;
}
Datatype Segment_tree::constructSTUtil(int ss, int se, int si)
{
    if(ss==se)
        return seg_tree[si]=raw_arr[ss];
    else
    {
        int mid=getmid(ss, se);
        if(flag==SUM)
        seg_tree[si]=constructSTUtil(ss, mid,2*si+1)+constructSTUtil(mid+1, se, 2*si+2);
        else if(flag==MIN)
        seg_tree[si]=min(constructSTUtil(ss, mid,2*si+1),constructSTUtil(mid+1, se, 2*si+2));
        
        return seg_tree[si];
    }
}
Datatype Segment_tree::getTargetUtil(int ss, int se, int qs, int qe, int si)
{
    if(qs>se||qe<ss) //This range has nothing to do with current node
    {
        if(flag==SUM)
            return 0;
        else if(flag==MIN)
            return INFINITY_MAX;
    }
    else if(ss>=qs&&se<=qe)//The segment is in the range of query
        return seg_tree[si];
    else  //overlap
    {
        int mid=getmid(ss, se);
        if(flag==SUM)
             return getTargetUtil(ss, mid, qs, qe, 2*si+1)+getTargetUtil(mid+1, se, qs, qe, 2*si+2);
        else if(flag==MIN)
            return min(getTargetUtil(ss, mid, qs, qe, 2*si+1),getTargetUtil(mid+1, se, qs, qe, 2*si+2));
    }
    return NULL;
}
Datatype Segment_tree::getTarget(int qs, int qe)
{
    if(qs<0||qe>size_of_raw-1)
    {
        cout<<"Invalid range!"<<endl;
        return -1;
    }
    return getTargetUtil(0, size_of_raw-1, qs, qe, 0);
}
void Segment_tree::updateValueUtil_sum(int ss, int se, int i, int diff, int si)
{
    if(si>size_of_seg-1)
        return ;
    if(ss<=i&&i<=se)
    {
        int mid=getmid(ss, se);
        seg_tree[si]+=diff;
        updateValueUtil_sum(ss, mid, i, diff, 2*si+1);
        updateValueUtil_sum(mid+1, se, i, diff, 2*si+2);
    }
    return ;
}

void Segment_tree::updateValueUtil_min(int ss, int se, int i,int old_val, int si)
{
    if(si>size_of_seg-1)
        return ;
    if(ss<=i&&i<=se)
    {
        int mid=getmid(ss, se);
        if(seg_tree[si]!=old_val)  //if the value changed is not minimum in this segment
        seg_tree[si]=min(raw_arr[i],seg_tree[si]);
        else
        {
            seg_tree[si]=raw_arr[ss];
            for(int j=ss+1;j<=se;j++)
                seg_tree[si]=min(seg_tree[si],raw_arr[j]);
        }
        updateValueUtil_min(ss, mid, i, old_val,2*si+1);
        updateValueUtil_min(mid+1, se, i,old_val,2*si+2);
    }
    return ;
}

void Segment_tree::updateValue(int i, int new_val)
{
    if(i<0||i>size_of_raw-1)
    {
        cout<<"Invalid index!"<<endl;
        return;
    }
    Datatype diff=new_val-raw_arr[i];
    Datatype old_val=raw_arr[i];
    raw_arr[i]=new_val;
    if(flag==SUM)
    updateValueUtil_sum(0, size_of_raw-1, i, diff, 0);
    else if(flag==MIN)
    updateValueUtil_min(0, size_of_raw-1, i, old_val,0);
}
