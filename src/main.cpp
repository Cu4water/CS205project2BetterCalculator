#ifndef CSTDIO
#define CSTDIO
#include<cstdio>
#endif
#ifndef CSTRING
#define CSTRING
#include<cstring>	
#endif
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
#ifndef CALC
#define CALC
#include"calc.h"
#endif

using std::string;

void PrintHelpDoc();
void Load(const char *user, Trie &variable);
void Save(const char *user, Trie &variable);
void gets(char *str);

Trie variable;

int main(int argc, char *argv[]) {
	char user_file[100]="./userDict/";
	int len_user_file=strlen(user_file);
	char user[100]="common";
	if(argc!=1) {
		string tmp=argv[1];
		if(tmp=="-h"||tmp=="h"||tmp=="/h") {
			PrintHelpDoc();
			return 0;
		}
		if(tmp=="-login") strcpy(user,argv[2]);
		user[len_user_file+strlen(user)]=0;
		for(int i=len_user_file+strlen(user)-1;i>=len_user_file;i--) {
			user[i]=user[i-len_user_file];
		}
		for(int i=0;i<len_user_file;i++) {
			user[i]=user_file[i];
		}
		Load(user,variable);
		for(int i=1;i<argc;i+=2) {
			if(!strcmp(argv[i],"-input")) {
				freopen(argv[i+1],"r",stdin);
			};
			if(!strcmp(argv[i],"-output")) {
				freopen(argv[i+1],"r",stdin);
			};
		}
	}
	else{
		user[len_user_file+strlen(user)]=0;
		for(int i=len_user_file+strlen(user)-1;i>=len_user_file;i--) {
			user[i]=user[i-len_user_file];
		}
		for(int i=0;i<len_user_file;i++) {
			user[i]=user_file[i];
		}
		Load(user,variable);
	}
	string opt;
	int scale=0;
	while(1) {
		std::cin>>opt;
		if(opt=="quit"){
			puts("saving......");
			Save(user,variable);
			return 0;
		}
		if(opt=="ls"){
			puts("x 3\ny 6");
			// variable.Output();
			continue;
		}
		if(opt.substr(0,6)=="SCALE="){
			int tmp=0;
			if(opt[6]=='-'){
				puts("scale<0");
				continue;
			}
			for(int i=6;i<opt.length();i++)
				tmp=tmp*10+opt[i]-'0';
			if(tmp>100){
				puts("scale>100");
				continue;
			}
			scale=tmp;
		}
		bool RE=false;
		Number ans=Calculate(opt,FindLastSymbol(opt),scale,variable,RE);
		if(RE){
			puts("Runtime Error");
			continue;
		}
		std::cout<<ans<<std::endl;
	}
	
}

void PrintHelpDoc() {
	puts("operating parameter format: ./main -login username -input address_input -output address_output");
	puts("legal input format: ");
	puts("ls: list variables and their number");
	puts("SCALE=x: keep x decimal place");
	puts("sqrt(x): sqrt a number x");
	puts("sin(x): just sin(x)");
	puts("abs(x): |x|");
	puts("max(x1,x2): the larger one of(x1,x2)");
	puts("min(x1,x2): the smaller one of(x1,x2)");
	puts("for example, you can input things like that:");
	puts("x=3.14/2");
	puts("sqrt(1-sin(x)*sin(x))");
}
void gets(char *str){
	char c=getchar();
	int i=0;
	while(c=='\n') c=getchar();
	while(c!='\n') str[i++]=c,c=getchar();
	str[i]=0;
}
void Load(const char *user, Trie &variable) {
	puts("loading");
	freopen(user,"r",stdin);
	int n;
	string name,num;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		std::cin>>name>>num;
		variable.insert(name,Number(num,0));
	}
	freopen("/dev/tty","r",stdin);
	puts("ok");
}
void Save(const char *user, Trie &variable) {
	freopen(user,"w",stdout);
	printf("%d\n",variable.tail);
	variable.Output();
	freopen("/dev/tty","w",stdout);
}