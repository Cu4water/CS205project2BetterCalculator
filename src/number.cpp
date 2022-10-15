#ifndef CSTDIO
#define CSTDIO
#include<cstdio>
#endif
#ifndef STRING
#define STRING
#include<string>
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif
#ifndef NUMBER_JUDGE
#define NUMBER_JUDGE
#include"number_judge.h"
#endif

using std::string;

struct Number{
	int meaning[kLengthMax<<1],len;
	int pow;
	bool f;

    Number(){
        
    }
	Number(const string str,const int left,const int right){ //format: A'.'B['E','e']['+','-']C  '.', 'e+' <=1
	    len=0;
	    int start_pos=left,end_pos=right;
	    int point_pos=-1,e_pos=-1;
	}

	void Print(){
		if(!f) putchar('-');
		pow+=len-1;
		for(int i=len-1; i>=0; i--){
			if(i==len-2){
				printf(".");
			}
			printf("%d",meaning[i]);
		}
		if(pow!=0){
			printf("e");
			if(pow>0){
				printf("+%d",pow);
            }
			else{
				printf("-%d",-pow);
			}
		}
        pow-=len-1;
    }
		Number DivisionGetQuotient(const Number &b);            //round(this/b)
		Number DivisionGetMod(const Number &b);                 //this-round(this/b)*b

		Number & operator +(const Number &b);
		Number & operator -(const Number &b);
		Number & operator *(const Number &b);
		Number & operator /(const Number &b);                   // this/=b,with scale
};
