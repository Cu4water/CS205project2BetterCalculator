#ifndef CSTDIO
#define CSTDIO
#include<cstdio>
#endif
#ifndef CSTRING
#define CSTRING
#include<cstring>
#endif
#ifndef CSTDLIB
#define CSTDLIB
#include<cstdlib>
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif

void Fail(char *err_msg,int *opt)	// opt[0]:operator, operator[1...n]:arguments
{
	switch (opt[0]){
		default:
			exit(opt[0]);
			break;
	}

}
int StringNumIsZero(const char *str, const int left, const int right){
	int pos_start=0;
	if(str[left]=='-') pos_start++;
	bool has_num=false;
	for(int i=left+pos_start; i<=right&&(!has_num); ++i){
		if(str[i]>'0'&&str[i]<='9') has_num=true;
		if(str[i]=='e') break;
	}
	return !has_num;
}
int ScienceNumIsZero(const Number number,const int left,const int right){
	if(number.pow!=0){
		return 0;
	}
	int pos_start=0;
	if(number.meaning[left]=='-') pos_start++;
	int has_num=0;
	for(int i=left+pos_start; i<=right&&(!has_num); ++i){
		if(number.meaning[i]>'0'&&number.meaning[i]<='9') has_num=true;
	}
	return !has_num;
}
int StrIsScienceNum(const char *str, const int left, const int right){	// return: 1:is; 0:no -1:illegal input format
	int start_pos=0;
	if(str[left]=='-') start_pos++;
	if(left+start_pos>right) return -1;
	int num_of_point=0, num_of_e_add=0;
	for(int i=left+start_pos; i<=right; ++i)
	{
		if(str[i]=='e')
		{
			if(i!=left&&str[i-1]=='.') return -1;                  	// 1.e+200
			if(i==right) return -1;                                	// 123e
			if(str[i+1]!='+'&&str[i+1]!='-') return false;     	 	// 123e*456 or "eight"
			if(num_of_e_add!=0) return -1;                         	// 123e+e+200
			++num_of_e_add;
			num_of_point=0;
			continue;
			// e+200 = 1e+200
		}
		if(str[i]=='.')
		{
			if(num_of_point!=0) return -1;                         // 1.1.
			++num_of_point;
			continue;
			// .9 = 0.9
		}
		if(str[i]>='0'&&str[i]<='9')   
		{
			continue;
		}
		if(str[i]=='-')
		{
			if(str[i-1]=='e') continue;
			return -1;											//-123-456e+23
		}
	}
	return true;
}