#ifndef VECTOR
#define VECTOR
#include<vector>
#endif
#ifndef STRING
#define STRING
#include<string>
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

    TrieVar();

    void Insert(const string new_name, const Number new_number);
    void Output();
    Number Find(const string given_name);
};

struct TrieFunc{
    vector<string> name,function;
    int tail;

    TrieFunc();

    void Insert(const string new_name, const string new_func);
    void Output();
    string Find(const string given_name,bool &finded);
};