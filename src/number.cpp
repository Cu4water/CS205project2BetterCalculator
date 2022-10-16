#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif
#ifndef SSTREAM
#define SSTREAM
#include<sstream>
#endif
#ifndef IOMANIP
#define IOMANIP
#include<iomanip>
#endif
#ifndef CMATH
#define CMATH
#include<cmath>
#endif
#ifndef NUMBER
#define NUMBER
#include"number.h"
#endif

using std::string;
using std::vector;
using std::stringstream;

vector<string> split(const string &s, const string &delim) {
	vector<string> elems;
	size_t pos_ = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos_ < len)
	{
		int find_pos = s.find(delim, pos_);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos_, len - pos_));
			break;
		}
		elems.push_back(s.substr(pos_, find_pos - pos_));
		pos_ = find_pos + delim_len;
	}
	return elems;
}

Number::Number() {
	num_.resize(digit_);
}
Number::Number(const int &x) {
	num_.resize(digit_);
	ToBig(x);
}
Number::Number(const int &x,const int &scale) {
	SetScale(scale);
	num_.resize(digit_);
	ToBig(x);
}
Number::Number(const long long &x,const int &scale) {
	SetScale(scale);
	num_.resize(digit_);
	ToBig(x);
}
Number::Number(const double &x,const int &scale) {
	SetScale(scale);
	num_.resize(digit_);
	ToBig(x);
}
Number::Number(const string &x,const int &scale) {
	SetScale(scale);
	num_.resize(digit_);
	ToBig(x);
}

void Number::ToBig(int x) {
	Number obj;
	*this = obj;
	if(!x) return;
	if(x<0) sign_=false, x=-x;
	num_.clear();
	while(x) {
		num_.push_back(x%10);
		x/=10;
	}
	if (num_.size()>digit_) num_.erase(num_.begin(),num_.begin()+num_.size()-digit_),overflow_=1;
	size_=num_.size();
	num_.resize(digit_);
}
void Number::ToBig(long long x) {
	Number obj;
	*this = obj;
	if (!x) return;
	if (x<0) sign_=false,x=-x;
	num_.clear();
	while(x) {
		num_.push_back( x % 10);
		x /= 10;
	}
	if (num_.size()>digit_) num_.erase(num_.begin(),num_.begin()+num_.size()-digit_),overflow_=1;
	size_=num_.size();
	num_.resize(digit_);
}
void Number::ToBig(double x) {
	string str;
	stringstream ss;
	ss<<std::fixed<<std::setprecision(digit_) << x;
	ss>>str;
	ToBig(str);	
}
void Number::ToBig(string x){
	Number obj;
	*this = obj;
	if(x[0]=='-') sign_=0,x=x.substr(1,x.size()-1);
	vector<string>vec=split(x,".");
	string str;
	for(auto it:vec) {
		str+=it;
	}
	if(vec.size()==2&&vec[0].size()>digit_) overflow_=1;
	size_=str.size()>digit_?digit_:str.size();
	pos_=size_-vec.front().size();
	if(pos_<0) pos_=0;
	for(int i=0;i<size_;i++) {
		num_[size_-1-i]=str[i]-'0';
	}
	while(num_[0]==0&&pos_>0) num_.erase(num_.begin()),size_--,pos_--;
}

string Number::Attribute() {
	return "("+std::to_string(sign_)+","+std::to_string(size_)+","+std::to_string(pos_)+","+std::to_string(overflow_) + ")";
}
void Number::SetScale(const int &scale){
	if(scale<0){
		puts("scale<0");
		return;
	}
	if(scale>100){
		puts("scale>100");
		return ;
	}
	digit_=scale;
	return;
}

ostream& operator<<(ostream& output,const Number &obj) {
	if(!obj.sign_) output<<'-';
	for(int i=obj.size_-1;i>0;i--) {
		output<<obj.num_[i];
		if (i==obj.pos_) output<<'.';
	}
	output<<obj.num_[0];
	return output;
}

Number & Number::operator+(const Number &obj) {
	Number obj0;
	obj0.overflow_=overflow_||obj.overflow_;
	Number round;
	bool judge=false;
	Number obj1=*this, obj2=obj;
	if (obj1.sign_==1&&obj2.sign_==0){
		obj2.sign_ = 1;
		return obj1-obj2;
	}
	if (obj1.sign_ == 0 && obj2.sign_ == 1){
		obj1.sign_ = 1;
		return obj2 - obj1;
	}
	vector<short>vec0;
	vector<short>vec1=num_;
	vector<short>vec2=obj.num_;
	int size0,size1=size_,size2=obj.size_,pos0,pos1=pos_,pos2=obj.pos_;
	int overflow0=0;
	if (pos1>=pos2){
		pos0=pos1;
		vec2.insert(vec2.begin(),pos1-pos2,0);
		size2+=pos1-pos2;
	}
	else{
		pos0=pos2;
		vec1.insert(vec1.begin(),pos2-pos1,0);
		size1+=pos2-pos1;
	}
	size0=size1>=size2?size1:size2;
	vec1.resize(size0);
	vec2.resize(size0);
	int carry=0;
	for (int i=0;i<size0;i++){
		int sum=vec1[i]+vec2[i]+carry;
		vec0.push_back(sum%10);
		if (sum/10) carry=1;
		else carry=0;
	}
	if(carry) vec0.push_back(1),size0++;
	while (vec0[0]==0&&pos0>0) vec0.erase(vec0.begin()),size0--,pos0--;
	if (size0 > digit_) {
		if(size0-pos0>digit_) obj0.overflow_ = 1;
		pos0 -= size0 - digit_;
		if (pos0 < 0) pos0 = 0;
		judge = vec0[size0 - digit_ - 1] > 4;
		vec0.erase(vec0.begin(), vec0.begin() + size0 - digit_ );
		size0 = digit_;
	}
	vec0.resize(digit_);
	obj0.size_=size0;
	obj0.pos_=pos0;
	obj0.num_=vec0;
	if (sign_==0&&obj.sign_==0) obj0.sign_=0;
	if (judge) round.size_=obj.size_,round.pos_=obj0.pos_,round.num_[0]=1;
	return judge?obj0+round:obj0;
}

Number & Number::operator - (const Number &obj) {
	int sign0=1,size0,pos0;
	Number obj0, obj1, obj2;
	Number zero=Number(0);
	obj0.overflow_=overflow_||obj.overflow_;
	if(sign_) {
		if(obj.sign_) {
			if(*this==obj) return zero;
			if(*this>obj) obj1=*this,obj2=obj,sign0=1;
			if(*this<obj) obj1=obj,obj2=*this,sign0=0;
		}
		else {
			obj0=obj;
			obj0.sign_=1;
			return *this+obj0;
		}
	}
	else {
		if(obj.sign_) {
			obj0=*this;
			obj0.sign_=1;
			return Number(0)-(obj0+obj);
		}
		else {
			obj1=*this,obj1.sign_=1;
			obj2=obj,obj2.sign_=1;
			return obj2-obj1;
		}
	}
	pos0=obj1.pos_>=obj2.pos_?obj1.pos_:obj2.pos_;
	size0=pos0+(obj1.size_-obj1.pos_>=obj2.size_-obj2.pos_?obj1.size_-obj1.pos_:obj2.size_-obj2.pos_);
	obj1.num_.insert(obj1.num_.begin(),pos0-obj1.pos_,0);
	obj2.num_.insert(obj2.num_.begin(),pos0-obj2.pos_,0);
	obj1.num_.resize(size0);
	obj2.num_.resize(size0);
	int carry=0;
	obj0.num_.resize(0);
	for(int i = 0; i < size0; i++){
		if(carry){
			if (obj1.num_[i]==0) obj1.num_[i]=9;
			else obj1.num_[i]--,carry=0;
		}
		if(obj1.num_[i]<obj2.num_[i]){
			obj1.num_[i]+=10;
			carry=1;
		}
		obj0.num_.push_back(obj1.num_[i]-obj2.num_[i]);
	}
	while(obj0.num_[0]==0&&pos0>0) obj0.num_.erase(obj0.num_.begin()),size0--,pos0--;
	for(int i=size0-1;i>pos0&&obj0.num_[i]==0;i--) size0--;
	if(size0>obj0.digit_){
		obj0.num_.erase(obj0.num_.begin(),obj0.num_.begin()+size0-obj0.digit_);
		pos0-=size0-obj0.digit_;
		size0=obj0.digit_;
	}
	obj0.num_.resize(obj0.digit_);
	obj0.sign_=sign0;
	obj0.size_=size0;
	obj0.pos_=pos0;
	return obj0;
}

Number & Number::operator*(const Number &obj){
	Number obj0;
	obj0.overflow_=overflow_||obj.overflow_;
	Number round;
	bool judge=false;
	int m=size_,n=obj.size_;
	vector<vector<short> >vec(m,vector<short>(m+n));
	for(int i=0;i<m;i++){
		int carry=0;
		int j;
		for(j=0;j<n;j++){
			int sum=num_[i]*obj.num_[j]+carry;
			vec[i][i+j]=sum%10;
			carry=sum/10;
		}
		if(carry) vec[i][i+j]=carry;
	}
	vector<short>vec0;
	int carry=0;
	for(int j=0;j<m+n;j++){
		for(int i=0;i<m;i++)
			carry+=vec[i][j];
		vec0.push_back(carry%10);
		carry/=10;
	}
	while(carry) vec0.push_back(carry%10),carry/=10;

	obj0.sign_=(sign_==obj.sign_);
	round.sign_=obj0.sign_;
	obj0.pos_=pos_+obj.pos_;
	while(vec0.back()==0&&vec0.size()>obj0.pos_+1) vec0.pop_back();
	if(vec0.size()>digit_){
		judge=vec0[vec0.size()-digit_-1]>4;
		obj0.pos_-=vec0.size()-digit_;
		vec0.erase(vec0.begin(),vec0.begin()+vec0.size()-digit_);
		if(obj0.pos_<0) obj0.pos_=0,obj0.overflow_=1;
		if(judge) round.size_=vec0.size(),round.pos_=obj0.pos_,round.num_[0]=1;
	}
	while (vec0[0]==0&&obj0.pos_>0)vec0.erase(vec0.begin()),obj0.pos_--;
	obj0.size_=vec0.size();
	obj0.num_=vec0;
	return judge?obj0+round:obj0;
}

Number & Number::operator / (Number obj){
	if (obj<Number(1)&&obj>Number(-1)&&obj.is_divided_){
		obj.is_divided_=false;
		return *this * (Number(1)/obj);
	}
	Number obj0, obj1=*this, obj2=obj,obj3,round;
	bool judge=false;
	obj1.sign_=1,obj2.sign_=1;
	obj1.overflow_=0,obj1.overflow_=0;
	obj0.overflow_=(overflow_||obj.overflow_);
	if(size_==1&&num_[0]==0) return obj0;
	obj0.sign_=(sign_==obj.sign_);
	obj0.num_.clear();
	obj0.pos_=obj1.pos_>=obj2.pos_?obj1.pos_:obj2.pos_;
	if(obj0.pos_>=obj1.pos_) obj1.num_.insert(obj1.num_.begin(),obj0.pos_-obj1.pos_,0),obj1.size_+=obj0.pos_-obj1.pos_,obj1.pos_=0;
	if(obj0.pos_>=obj2.pos_) obj2.num_.insert(obj2.num_.begin(),obj0.pos_-obj2.pos_,0),obj2.size_+=obj0.pos_-obj2.pos_,obj2.pos_=0;
	while(obj1.num_[obj1.size_-1]==0) obj1.size_--;
	while(obj2.num_[obj2.size_-1]==0) obj2.size_--;
	obj1.num_.resize(obj1.size_);
	obj2.num_.resize(obj2.size_);
	if(obj2.size_>digit_-2){	//deal with'-'&'*'
		int val=abs(obj2.size_-digit_+2);
		obj1.num_.erase(obj1.num_.begin(),obj1.num_.begin()+val);
		obj1.size_-=val;
		obj2.num_.erase(obj2.num_.begin(),obj2.num_.begin()+val);
		obj2.size_-=val;
	}
	obj1.num_.insert(obj1.num_.begin(),digit_+obj2.size_-obj1.size_+1,0);
	bool p=false;
	int count=0;
	obj0.pos_=0;
	for(int i=obj1.num_.size()-1;i>=0;i--){	
		obj3=obj3*Number(10)+Number(obj1.num_[i]);
		int carry=0;
		for(int j=1;j<=10;j++)		
			if(Number(j)*obj2>=obj3){	
				carry=1;
				if(Number(j)*obj2>obj3){
					j--;
					obj3=obj3-Number(j)*obj2;				
				}
				else obj3=Number(0);
				if(j){
					obj0.num_.insert(obj0.num_.begin(),j);
					if(i>=obj1.num_.size()-obj1.size_) obj0.pos_++;
				}
				else carry=0;
				break;			
			}	
		if(!carry){
			if(i==obj1.num_.size()-obj1.size_) obj0.pos_++;
			if(obj0.pos_){
				if (i>obj1.num_.size()-obj1.size_) obj0.pos_++;
				obj0.num_.insert(obj0.num_.begin(), 0);
			}
		}
	}
	obj0.size_=obj0.num_.size();
	int real=obj0.pos_;
	obj0.pos_=obj0.size_-real;
	while(obj0.num_.back()==0&&obj0.size_>obj0.pos_+1) obj0.num_.pop_back(),obj0.size_--;
	if(obj0.size_>digit_){
		if(obj0.num_[obj0.size_-digit_-1]>4){
			judge=true;
		}
		obj0.num_.erase(obj0.num_.begin(),obj0.num_.begin()+obj0.size_-digit_);
		obj0.pos_-=obj0.size_-digit_,obj0.size_=digit_;
		if(obj0.pos_<0) obj0.pos_=0;
		round.size_=obj0.size_,round.pos_=obj0.pos_,round.num_[0]=1;
	}
	while(obj0.num_[0]==0&&obj0.pos_>0) obj0.num_.erase(obj0.num_.begin()), obj0.pos_--,obj0.size_--;
	obj0.num_.resize(digit_);
	return judge?obj0+round:obj0;
}

bool Number::operator<(const Number &obj){
	if(!sign_){
		if(!obj.sign_){
			int a=(size_-pos_)-(obj.size_-obj.pos_);
			if(a<0) return false;
			if(a>0) return true;
			if(a==0){
				int who,pos0;
				if(pos_<=obj.pos_) pos0=pos_,who=2;
				else pos0=obj.pos_,who=1;
				for(int i=size_-1,j=obj.size_-1;i>=pos_-pos0;i--,j--){
					if(num_[i]<obj.num_[j]) return false;
					if(num_[i]>obj.num_[j]) return true;
				}
				if(who==1) return true;
				else return false;
			}
		}
		else return true;	
	}
	else{
		if(!obj.sign_) return false;
		else{
			int a=(size_-pos_)-(obj.size_-obj.pos_);
			if(a<0) return true;
			if(a>0) return false;
			if(a==0){
				int who,pos0;
				if(pos_<obj.pos_) pos0=pos_,who=2;
				else pos0=obj.pos_,who=1;
				for(int i=size_-1,j=obj.size_-1;i>=pos_-pos0;i--,j--){
					if(num_[i]<obj.num_[j]) return true;
					if(num_[i]>obj.num_[j]) return false;
				}
				if(who==1) return false;
				return true;
			}
		}
	}
	return true;
}

bool Number::operator>(const Number &obj){
	return (!(*this<obj))&&(!(*this==obj));
}

bool Number::operator==(const Number &obj){
	return sign_==obj.sign_&&overflow_==obj.overflow_&&size_==obj.size_&&pos_==obj.pos_&&num_==obj.num_;
}

bool Number::operator<=(const Number &obj){
	return !(*this>obj);
}

bool Number::operator>=(const Number &obj){
	return !(*this<obj);
}

void Number::PrintArray(const vector<short> &vec){
	for (int i=vec.size()-1;i>=0;i--) std::cout<<vec[i];
	std::cout<<std::endl;
}

Number Number::BigPow(const Number &obj,const int &n){
	Number obj0(1);
	for (int i = 0; i < n; i++) obj0=obj0*obj;
	return obj0;
}