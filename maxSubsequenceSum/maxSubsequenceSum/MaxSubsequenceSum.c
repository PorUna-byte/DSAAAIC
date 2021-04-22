//
//  main.c
//  maxSubsequenceSum
//
//  Created by PorUnaCabeza on 2021/3/9.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//problem description:
//Given (possibly negative) integers A1,A2,...,An,find the maximum value of (A_i+A_(i+1)+...A_j).we also define the subsequence
//sum is 0 if it is calculated as a negative number.
#define MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

#include <stdio.h>

// The first brutal force algorithm has a complexity of time in O(N^3)
int algo1(const int A[],int N)
{
    int ThisSum,MaxSum,i,j,k;
    MaxSum=0;
    for (i=0;i<N;i++)
        for(j=i;j<N;j++)
        {      //fix i and j ,sum all digits between them.
            ThisSum=0;
            for(k=i;k<=j;k++)
                ThisSum+=A[k];
            
            if(ThisSum>MaxSum)
                MaxSum=ThisSum;
        }
    return MaxSum;
}
//The second algorithm is relatively more efficient than the first one by using the fact that:(A_i+A_(i+1)+...+A_j)=A_j+(A_i+...A_(j-1))
//The time complexity is O(N^2)
int algo2(const int A[],int N)
{
    int ThisSum,MaxSum,i,j;
    MaxSum=0;
    for (i=0;i<N;i++)
    {             //fix i,consider all possible sum that starts from i
        ThisSum=0;
        for(j=i;j<N;j++)
        {
            ThisSum+=A[j];
            if(ThisSum>MaxSum)
                MaxSum=ThisSum;
        }
    }
    return MaxSum;
}
//The third algorithm is an example of divide&conquer algorithm
//The time complexity is O(NlogN)
int algo3(const int A[],int left,int right)
{
    int MaxleftSum,MaxrightSum;
    int i,j;
    if(left==right)
        return A[left]>0?A[left]:0 ;

    int mid=(left+right)/2;
    MaxleftSum=algo3(A, left,mid);
    MaxrightSum=algo3(A, mid+1,right);
    
    int This_left_sum=0;
    int MaxleftborderSum=0;
    for(i=mid;i>=left;i--)   //evaluate the Maxleftbordersum
    {
        This_left_sum+=A[i];
        if(This_left_sum>MaxleftborderSum)
            MaxleftborderSum=This_left_sum;
    }
    int This_right_sum=0;
    int MaxrightborderSum=0;
    for(j=mid+1;j<=right;j++)   //evaluate the Maxrightbordersum
    {
        This_right_sum+=A[i];
        if(This_right_sum>MaxrightborderSum)
            MaxrightborderSum=This_right_sum;
    }
    return MAX(MaxleftSum,MaxrightSum,MaxleftborderSum+MaxrightborderSum);
}
//The fourth algorithm is a little tricky although it has a simple implementation
//The time complexity is O(N)
//The procedure of processing an array must set the This_sum to zero
//at the digit exactly before The sequence which has Max sum.(This can be proved by contradiction)
int algo4(const int A[],int N)
{
    int i;
    int MaxSum,This_Sum;
    MaxSum=This_Sum=0;
    for( i=0;i<N;i++)
    {
        This_Sum+=A[i];
        if(This_Sum>MaxSum)
            MaxSum=This_Sum;
        else if(This_Sum<0)
            This_Sum=0;//Must execute at the digit exactly before The sequence which has Max sum.
    }
    return MaxSum;
}
int main(int argc, const char * argv[])
{
    int A[8]={4,-3,5,-2,-1,2,6,-2};
    printf("The max sum of {4,-3,5,-2,-1,2,6,-2} is %d:",algo4(A, 8));

    return 0;
}
