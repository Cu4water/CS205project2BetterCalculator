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

class Trie{
    public:
        vector<string> name;
        vector<Number> num;
        int tail;
        Trie();
        void insert(const string new_name, const Number new_number);
        void Output();
        Number Find(const string given_name, bool &founded);
};