//
//  main.cpp
//  Segment_tree
//
//  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "segment_tree.hpp"

int main(int argc, const char * argv[]) {
    Datatype array[6]={1,3,5,7,9,11};
    Segment_tree seg_tree(array, 6,MIN);
    cout<<seg_tree.getTarget(3, 4)<<endl;
    cout<<seg_tree.getTarget(0, 2)<<endl;
    cout<<seg_tree.getTarget(1, 4)<<endl;
    seg_tree.updateValue(0, 10);
    cout<<seg_tree.getTarget(3, 4)<<endl;
    cout<<seg_tree.getTarget(0, 2)<<endl;
    cout<<seg_tree.getTarget(1, 4)<<endl;
    return 0;
}
