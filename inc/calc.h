#ifndef STRING
#define STRING
#include<string>
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif
#ifndef TRIE
#define TRIE
#include"trie.h"
#endif

using std::string;

int FindLastSymbol(const string opt);                                                       //without symbol return -1;
Number Calculate
(const string opt, const int last_calc_pos,const int scale,Trie &variable, bool &runtime_error);           //last_calc_pos: the last symbol involved in calculation
Number CalcFunc(const string opt,const int &scale, Trie &variable);    //deal with functions