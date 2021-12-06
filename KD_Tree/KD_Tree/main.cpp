//
//  main.cpp
//  KD_Tree
//
//  Created by PorUnaCabeza on 2021/12/5.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "KD_Tree.hpp"

void check_Insert(){
    KD_Tree kd_tree;
    int points[][K] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
        {9, 1}, {2, 7}, {10, 19}};
    
    int n = sizeof(points)/sizeof(points[0]);
    
    for (int i=0; i<n; i++)
        kd_tree.Insert(points[i]);
    
    int point1[] = {10, 19};
    (kd_tree.Search(point1))? cout << "Found\n": cout << "Not Found\n";
    
    int point2[] = {12, 19};
    (kd_tree.Search(point2))? cout << "Found\n": cout << "Not Found\n";
    
    return ;
}
void check_FindMin(){
    int points[][K] = { { 30, 40 }, { 5, 25 },
        { 70, 70 }, { 10, 12 }, { 50, 30 }, { 35, 45 } };
    
    int n = sizeof(points) / sizeof(points[0]);
    KD_Tree kd_tree;
    for (int i = 0; i < n; i++)
       kd_tree.Insert(points[i]);
    
    cout << "Minimum of 0'th dimension is " << kd_tree.FindMin(0) << endl;
    cout << "Minimum of 1'th dimension is " << kd_tree.FindMin(1) << endl;
}
void check_Delete()
{
    int points[][K] = {{30, 40}, {5, 25}, {70, 70},
        {10, 12}, {50, 30}, {35, 45}};
    
    int n = sizeof(points)/sizeof(points[0]);
    KD_Tree kd_tree;
    for (int i=0; i<n; i++)
        kd_tree.Insert(points[i]);
    
    // Delete (30, 40);
    kd_tree.Delete(points[0]);
    
    cout << "Root after deletion of (30, 40)\n";
    cout << kd_tree.getroot()->getKeys(0)<< ", " <<kd_tree.getroot()->getKeys(1)<< endl;
}
int main(int argc, const char * argv[]) {
    check_Delete();
    return 0;
}
