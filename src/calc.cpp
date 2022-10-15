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

int kScale=0;   //allow fix, SCALE=number, for a float number, scale will be round(number), and less than 100

void FixScale(const string num){
    int len=num.length();
    int x=0,pos=0;
    while(num[pos]>'9'||num[pos]<'0'){
        if(num[pos]=='-'){
            printf("minus scale!\n");
            return;
        }
        pos++;
    }
    while(num[pos]>'0'&&num[pos]<'9'){
        x=x*10+num[pos]-'0';
        pos++;
    }
    kScale=x;
}

int GetPriority(const char ch){
    if(ch=='+'||ch=='-') return 1;
    if(ch=='*'||ch=='/') return 2;
    return 3;
}
int FindLastSymbol(const string opt, const int left, const int right){
    bool has_sym=false;
    for(int i=left;i<right;i++){
        if(opt[i]=='+'||opt[i]=='-'||opt[i]=='*'||opt[i]=='/') has_sym=true;
    }
    if(!has_sym) return -1;
    //have +-*/
    int tmpans=left;
    int bracket_stack=0,lowest_stack=100;
    int lowest_priority=2;

    for(int i=left;i<right;i++){    //get lowest priority
        if(opt[i]=='+'||opt[i]=='-'){
            lowest_priority=1;
        }
        if(opt[i]=='('){
            bracket_stack++;
        }
        if(opt[i]==')'){
            bracket_stack--;
        }
        if(bracket_stack < lowest_stack) lowest_stack = bracket_stack;
    }
    bracket_stack=0;

    for(int i=left;i<right;i++){
        if(opt[i]=='(') bracket_stack++;
        if(opt[i]==')') bracket_stack--;
        if( bracket_stack == lowest_stack && GetPriority(opt[i])==lowest_priority) tmpans=i;
    }
    return tmpans;
}
Number Calculate(const string opt, const int left, const int right,const int last_calc_pos, bool &runtime_error){
    if(runtime_error) return Number();
    Number ans;
    if(last_calc_pos==-1){// basic part 
    }
    Number l_part=Calculate(opt,left,last_calc_pos,FindLastSymbol(opt,left,last_calc_pos),runtime_error);
    Number r_part=Calculate(opt,last_calc_pos+1,right,FindLastSymbol(opt,last_calc_pos+1,right),runtime_error);
    if(runtime_error) return Number();
    switch(opt[last_calc_pos]){
        case '+':
            return l_part+r_part;
        case '-':
            return l_part-r_part;
        case '*':
            return l_part*r_part;
        case '/':
            if(StringNumIsZero(r_part,0,r_part.len)){
                runtime_error=true;
                return Number();
            }
            return l_part/r_part;
        default:
            runtime_error=true;
            return Number();
    }
}