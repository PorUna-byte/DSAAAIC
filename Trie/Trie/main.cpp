//
//  main.cpp
//  Trie
//
//  Created by PorUnaCabeza on 2021/11/26.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "Trie.hpp"

int main(int argc, const char * argv[]) {
    Trie trie;
    // Input keys (use only 'a' through 'z'
    // and lower case)
    string keys[] = { "the", "a", "there",
        "answer", "any", "by",
        "bye", "their", "hero", "heroplane" };
    int n = sizeof(keys) / sizeof(keys[0]);
    // Construct trie
    for (int i = 0; i < n; i++)
        trie.insert(keys[i]);
    
    // Search for different keys
    trie.search("the") ? cout << "Yes\n" : cout << "No\n";
    trie.search("these") ? cout << "Yes\n" : cout << "No\n";
    
    trie.remove("heroplane");
    trie.search("hero") ? cout << "Yes\n" : cout << "No\n";
    trie.remove("the");
    trie.search("there") ? cout << "Yes\n" : cout << "No\n";
    return 0;
}
