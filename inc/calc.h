#ifndef STRING
#define STRING
#include<string>
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif

using std::string;

int kScale=0;   //allow fix, SCALE=number, for a float number, scale will be round(number), and less than 100

void FixScale(const string num);
int FindLastSymbol(const string opt, const int left, const int right);                                              //without symbol return -1;
Number Calculate(const string opt, const int left, const int right, const int last_calc_pos, bool &runtime_error);  //last_calc_pos: the last symbol involved in calculation
Number CalcFunc(const string opt, const int left, const int right, bool &runtime_error);                                                 //deal with functions