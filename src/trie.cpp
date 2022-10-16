#ifndef VECTOR
#define VECTOR
#include<vector>
#endif
#ifndef STRING
#define STRING
#include<string>
#endif
#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif
#ifndef TRIE
#define TRIE
#include"trie.h"
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif

using std::vector;
using std::string;

Trie::Trie() {
    tail=0;
}

void Trie::insert(const string new_name, const Number new_number) {
    name.push_back(new_name);
    num.push_back(new_number);
    tail++;
    return;
}
void Trie::Output() {
    for(int i=0;i<tail;i++) {
        std::cout<<name[i]<<" "<<num[i]<<std::endl;
    }
    return;
}
Number Trie::Find(const string given_name, bool &founded) {
    for(int i=0;i<tail;i++) {
        if(name[i]==given_name) return num[i];
    }
    return NULL;
}