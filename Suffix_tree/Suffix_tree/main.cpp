//
//  main.cpp
//  Suffix_tree
//
//  Created by PorUnaCabeza on 2021/11/27.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Suffix_tree.hpp"
void checkForSubString(const string& str,SuffixTree& tree)
{
    int search=tree.search(str);
    if(search != 0)
        cout<<"Pattern <"<<str<<"> is a Substring\n";
    else
        cout<<"Pattern <"<<str<<"> is NOT a Substring\n";
}
void check_exist(){
    string text="THIS IS A TEST TEXT$";
    SuffixTree suffix_tree(text);
    
    checkForSubString("TEST",suffix_tree);
    checkForSubString("A",suffix_tree);
    checkForSubString(" ",suffix_tree);
    checkForSubString("IS A",suffix_tree);
    checkForSubString(" IS A ",suffix_tree);
    checkForSubString("TEST1",suffix_tree);
    checkForSubString("THIS IS GOOD",suffix_tree);
    checkForSubString("TES",suffix_tree);
    checkForSubString("TESA",suffix_tree);
    checkForSubString("ISB",suffix_tree);
}
void check_longest(){
    string text=" GEEKSFORGEEKS$";
    SuffixTree suffix_tree(text);
    suffix_tree.longest_repeat();
}
void check_common(){
    SuffixTree suffix_tree("xabxac#abcabxabcd$");
    suffix_tree.set_size_x(7);
    suffix_tree.longest_common();
}
int main(int argc, const char * argv[]) {
//    SuffixTree suffix_tree("abcabxabcd$");
//    cout<<suffix_tree.search("bxab")<<endl;
    check_common();
    return 0;
}
