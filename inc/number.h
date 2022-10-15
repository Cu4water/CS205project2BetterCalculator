#ifndef STRING
#define STRING
#include<string>
#endif

using std::string;

const int kLengthMax=510;

struct Number{
    int meaning[kLengthMax<<1],len;    // <<1 for add, backward, [0,tail)
    int pow;                        // format: a.be+c
    bool f;                         // +:true /-:false

    Number();
    Number(const string str,const int left,const int right); // [left,right)

    Number & operator +(const Number &b);
    Number & operator -(const Number &b);
    Number & operator *(const Number &b);
    Number & operator /(const Number &b);                   // this/=b,with scale
};
void Print();
Number DivisionGetQuotient(const Number &b);            //round(this/b)
Number DivisionGetMod(const Number &b);                 //this-round(this/b)*b