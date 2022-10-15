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

struct TrieVar{
    vector<string> name;
    vector<Number> num;
    int tail;

    TrieVar(){
        tail=0;
    }

    void Insert(const string new_name, const Number new_number){
        name[tail]=new_name;
        num[tail]=new_number;
        tail++;
        return;
    }
    void Output(){
        for(int i=0;i<tail;i++){
            std::cout<<name[i]<<" ";
            num[i].Print();
            std::cout<<std::endl;
        }
        return;
    }
    Number Find(const string given_name){
        for(int i=0;i<tail;i++){
            if(name[i]==given_name) return num[i];
        }
        Number not_find;
        not_find.meaning[0]=-1;
        return not_find;
    }
};

struct TrieFunc{
    vector<string> name,function;
    int tail;

    TrieFunc();

    void Insert(const string new_name, const string new_func){
        name[tail]=new_name;
        function[tail]=new_func;
        tail++;
        return;
    }
    void Output(){
        for(int i=0;i<tail;i++){
            std::cout<<name[i]<<" "<<function[i]<<std::endl;
        }
        return;
    }
    string Find(const string given_name,bool &finded){
        finded=true;
         for(int i=0;i<tail;i++){
            if(name[i]==given_name) return function[i];
        }
        finded=false;
        return string("Hello");
    }
};