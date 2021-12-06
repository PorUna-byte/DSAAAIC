//
//  main.cpp
//  Xor_linklist
//
//  Created by PorUnaCabeza on 2021/11/23.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Xor_linklist.hpp"

int main(int argc, const char * argv[]) {
    List list;
    for(int i=0;i<10;i++)
    list.Insert(false, 5*i);
    list.Insert_after(true, 30, 32);
    list.Insert_after(true, 32, 34);
    list.Insert_after(false, 25, 23);
    list.Traverse(true);
    list.Delete(true, 10);
    list.Delete(false, 32);
    list.Traverse(true);
    return 0;
}
