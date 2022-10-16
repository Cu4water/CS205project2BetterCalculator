#ifndef STRING
#define STRING
#include<string>
#endif
#ifndef CSTRING
#define CSTRING
#include<cstring>
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

int kScale=0;   //allow fix, SCALE=number, for a float number, scale will be round(number), and less than 100

int GetPriority(const char ch){
    if(ch=='+'||ch=='-') return 1;
    if(ch=='*'||ch=='/') return 2;
    return 3;
}
int FindLastSymbol(const string opt){
    int left=0;
    int right=opt.length();
    bool has_sym=false;
    for(int i=left;i<right;i++){
        if(opt[i]=='+'||opt[i]=='-'||opt[i]=='*'||opt[i]=='/') has_sym=true;
    }
    if(!has_sym) return -1;
    //have +-*/
    int tmpans=left;
    int bracket_stack=0,lowest_stack=100;
    int lowest_priority=3;

    for(int i=left;i<right;i++){    //get lowest priority
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
        if(bracket_stack==lowest_stack && GetPriority(opt[i])<=lowest_priority) 
            tmpans=i,lowest_priority=GetPriority(opt[i]);
    }
    return tmpans;
}
Number Calculate
(const string opt, const int last_calc_pos,const int scale, Trie &variable, bool &runtime_error){
    if(runtime_error){
        return NULL;
    }
    if(last_calc_pos==-1){
        
    }
    Number l_part=Calculate(opt.substr(0,last_calc_pos)
    ,FindLastSymbol(opt.substr(0,last_calc_pos)),scale,variable,runtime_error);
    Number r_part=Calculate(opt.substr(last_calc_pos+1,opt.length()-last_calc_pos-1)
    ,FindLastSymbol(opt.substr(last_calc_pos+1,opt.length()-last_calc_pos-1)),
    scale,variable,runtime_error);
    if(runtime_error) return NULL;
    switch(opt[last_calc_pos]){
        case '+':
            return l_part+r_part;
        case '-':
            return l_part-r_part;
        case '*':
            return l_part*r_part;
        case '/':
            if(r_part==Number(0)||r_part==Number(-0)){
                runtime_error=true;
                return NULL;
            }
            return l_part/r_part;
        default:
            runtime_error=true;
            return NULL;
    }
}