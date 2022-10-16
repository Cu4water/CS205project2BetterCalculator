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

using std::vector;
using std::string;
using std::ostream;

class Number
{
public:
	int digit_=0;			//max length
	bool sign_ = 1;					//is add
	bool overflow_ = 0;				//overflowed?
	bool is_divided_ = 1;			//divideable
	int pos_ = 0;					//position of point
	int size_ = 1;
	vector<short>num_;				//store of number

	Number();
	Number(const int &x);
	Number(const int &x,const int scale);
	Number(const long long &x,const int scale);
	Number(const double &x,const int scale);
	Number(const string x,const int scale);

	void ToBig(int x);
	void ToBig(long long x);
	void ToBig(double x);
	void ToBig(string x);
	void SetScale(const int &scale);

	friend ostream& operator<<(ostream& output,const Number &obj);
	Number & operator + (const Number &obj);
	Number & operator - (const Number &obj);
	Number & operator * (const Number &obj);
	Number & operator / (const Number obj);

	bool operator < (const Number &obj);
	bool operator > (const Number &obj);
	bool operator == (const Number &obj);
	bool operator <= (const Number &obj);
	bool operator >= (const Number &obj);
	
	void PrintArray(const vector<short> &vec);
	static Number BigPow(const Number &obj,const int &n);
};