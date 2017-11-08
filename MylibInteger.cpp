#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

const int64_t powers10[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000};
const int64_t& integerWordSize = powers10[9];
struct integer{
	integer(): size{2}, digit(2), exponent(64){}
	integer(int64_t&& d): size{d}, digit(d), exponent(64){}
	integer(int64_t& d): size{d}, digit(d), exponent(64){}
	integer(int64_t&& d,int64_t &&v): size{d}, digit(d,v), exponent(64){}
	integer(int64_t& d,int64_t &v): size{d}, digit(d,v), exponent(64){}
	integer(integer&& a): size{a.size}, digit{a.digit}, exponent(64){}
	integer(integer& a): size{a.size}, digit{a.digit}, exponent(64){}

	int64_t size;
	int64_t i,j;
	std::vector<int64_t> digit;
	void normalize(){
		for(i=size-1;digit[i]==0 && i;i--);
		digit.resize(i+1);
		size=i+1;
		if(digit[size-1]<0){
			for(i=0;i!=size-1;i++) 
				if(digit[i]>0){
					digit[i]-=integerWordSize;
					digit[i+1]++;
					if(digit[i+1]>=integerWordSize){
						digit[i+2]+=digit[i+1]/integerWordSize;
						digit[i+1]%=integerWordSize;
					}
				}
		}
		else{
			for(i=0;i!=size-1;i++) 
				if(digit[i]<0){
					digit[i]+=integerWordSize;
					digit[i+1]--;
					if(digit[i+1]<=-integerWordSize){
						digit[i+2]+=digit[i+1]/integerWordSize;
						digit[i+1]%=integerWordSize;
					}
				}
		}
		for(i=size-1;digit[i]==0 && i;i--);
		digit.resize(i+1);
		size=i+1;
		countTrim = 0;
	}

	integer operator+(integer& b){
		if(this->size > b.size) return integerSum(b,*this);
		else return integerSum(*this,b);
	}

	integer operator+(integer&& b){
		if(this->size > b.size) return integerSum(b,*this);
		else return integerSum(*this,b);
	}

	integer& operator+=(integer& b){
		if(size < b.size) {
			digit.resize(b.size+1);
			for(digit[size] = i = 0; i != size; i++){
				digit[i] += b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				digit[i] += b.digit[i];
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim += b.countTrim+1;
		}
		else{
			digit.resize(size+1);
			for(digit[size] = i = 0; i != b.size; i++){
				digit[i] += b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim++;
		}
		size = digit.size();
		if(countTrim>=oughtTrim) normalize();
		return *this;
	}

	integer& operator+=(integer&& b){
		if(size < b.size) {
			digit.resize(b.size+1);
			for(digit[size] = i = 0; i != size; i++){
				digit[i] += b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				digit[i] += b.digit[i];
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim += b.countTrim+1;
		}
		else{
			digit.resize(size+1);
			for(digit[size] = i = 0; i != b.size; i++){
				digit[i] += b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim++;
		}
		size = digit.size();
		if(countTrim>=oughtTrim) normalize();
		return *this;
	}

	integer integerSum(integer& min, integer& max){
		integer sum(max.size+1);

		for(sum.digit[0] = i = 0; i != min.size; i++){
			sum.digit[i] += min.digit[i]+max.digit[i];
			sum.digit[i+1] = sum.digit[i]/integerWordSize;
			sum.digit[i] %= integerWordSize;
		}
		for(;i != max.size; i++){
			sum.digit[i] += max.digit[i];
			sum.digit[i+1] = sum.digit[i]/integerWordSize;
			sum.digit[i] %= integerWordSize;
		}
		sum.countTrim = max.countTrim+1;
		if(sum.countTrim>=sum.oughtTrim) sum.normalize();
		return sum;
	} 

	integer operator-(integer& b){
		if(size < b.size) {
			integer dif(b.size+1);
			for(dif.digit[0] = i = 0; i != size; i++){
				dif.digit[i] += digit[i]-b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				dif.digit[i] -= b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			if((countTrim+=b.countTrim+1) >= oughtTrim) normalize();
			return dif;
		}
		else{
			integer dif(size+1);
			for(dif.digit[0] = i = 0; i != b.size; i++){
				dif.digit[i] += digit[i]-b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			if(++countTrim>=oughtTrim) normalize();
			return dif;
		}
	}

	integer operator-(integer&& b){
		if(size < b.size) {
			integer dif(b.size+1);
			for(dif.digit[0] = i = 0; i != size; i++){
				dif.digit[i] += digit[i]-b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				dif.digit[i] -= b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			if((countTrim+=b.countTrim+1)>=oughtTrim) normalize();
			return dif;
		}
		else{
			integer dif(size+1);
			for(dif.digit[0] = i = 0; i != b.size; i++){
				dif.digit[i] += digit[i]-b.digit[i];
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				dif.digit[i+1] = dif.digit[i]/integerWordSize;
				dif.digit[i] %= integerWordSize;
			}
			if(++countTrim>=oughtTrim) normalize();
			return dif;
		}
	}

	integer& operator-=(integer& b){
		if(size < b.size) {
			digit.resize(b.size+1);
			for(digit[size] = i = 0; i != size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim+=b.countTrim+1;
		}
		else{
			digit.resize(size+1);
			for(digit[size] = i = 0; i != b.size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim++;
		}
		size = digit.size();
		if(countTrim>=oughtTrim) normalize();
		return *this;
	}

	integer& operator-=(integer&& b){
		if(size < b.size) {
			digit.resize(b.size+1);
			for(digit[size] = i = 0; i != size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != b.size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim += b.countTrim+1;
		}
		else{
			digit.resize(size+1);
			for(digit[size] = i = 0; i != b.size; i++){
				digit[i] -= b.digit[i];
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			for(;i != size; i++){
				digit[i+1] = digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
			countTrim++;
		}
		size = digit.size();
		if(countTrim>=oughtTrim) normalize();
		return *this;
	}

	integer operator*(integer& b){
//		if(size*b.size>fastProduct) return fastMul(*this,b);
		integer pro(size+b.size, 0);
		for( i=0; i!=b.size; i++)
			for( j=0; j!=size; j++){
				pro.digit[i+j] += digit[j]*b.digit[i];
				pro.digit[i+j+1] += pro.digit[i+j]/integerWordSize;
				pro.digit[i+j] %= integerWordSize;
			}
		pro.countTrim = countTrim*b.countTrim;
		if(pro.countTrim > pro.oughtTrim) pro.normalize();
		return pro;
	}
	integer operator*(integer&& b){
//		if(size*b.size>fastProduct) return fastMul(*this,b);
		integer pro(size+b.size, 0);
		for( i=0; i!=b.size; i++)
			for( j=0; j!=size; j++){
				pro.digit[i+j] += digit[j]*b.digit[i];
				pro.digit[i+j+1] += pro.digit[i+j]/integerWordSize;
				pro.digit[i+j] %= integerWordSize;
			}
		pro.countTrim = countTrim*b.countTrim;
		if(pro.countTrim > pro.oughtTrim) pro.normalize();
		return pro;
	}

	integer& operator*=(integer&& b){
//		if(size*b.size>fastProduct) return fastMul(*this,b);
		integer pro(size+b.size, 0);
		for( i=0; i!=b.size; i++)
			for( j=0; j!=size; j++){
				pro.digit[i+j] += digit[j]*b.digit[i];
				pro.digit[i+j+1] += pro.digit[i+j]/integerWordSize;
				pro.digit[i+j] %= integerWordSize;
			}
		pro.countTrim = countTrim*b.countTrim;
		if(pro.countTrim > pro.oughtTrim) pro.normalize();
		*this = pro;
		return *this;
	}

	integer& operator*=(integer& b){
//		if(size*b.size>fastProduct) return fastMul(*this,b);
		integer pro(size+b.size, 0);
		for( i=0; i!=b.size; i++)
			for( j=0; j!=size; j++){
				pro.digit[i+j] += digit[j]*b.digit[i];
				pro.digit[i+j+1] += pro.digit[i+j]/integerWordSize;
				pro.digit[i+j] %= integerWordSize;
			}
		pro.countTrim = countTrim*b.countTrim;
		if(pro.countTrim > pro.oughtTrim) pro.normalize();
		*this = pro;
		return *this;
	}

	integer& toPow(int64_t e){
		if(e<0) return *this=0;
		else if(e==0) return *this=1;
		else if(e==1) return *this;
		else{
			integer power(1,1);
			i=0;
			while(e){
				exponent[i++] = e%2;
				e >>= 1;
			}
			for(j=i-1;j!=-1;j--){
				power *= power;
				if(exponent[j]) power *= *this;
			}
			if(power.countTrim > power.oughtTrim) power.normalize();
			*this = power;
			return *this;
		}
	}

	inline integer& operator/(integer& b){}

	integer& operator=(integer& b){
		if(&b != this){
			this->digit=b.digit;
			this->size=b.size;
			this->countTrim=b.countTrim;
		}
		return *this;
	}

	integer& operator=(integer&& b){
		this->digit=b.digit;
		this->size=b.size;
		this->countTrim=b.countTrim;
		return *this;
	}

	integer& operator=(int64_t& b){
		integer& a = *this;
		if(b>=integerWordSize || b<=-integerWordSize) {
			a.size=2;
			a.digit.resize(2);
			a.digit[0] = b%integerWordSize;
			a.digit[1] = b/integerWordSize;
		}
		else {
			a.size=1;
			a.digit.resize(1);
			a.digit[0] = b;
		}
		return a;
	}

	integer& operator=(int64_t&& b){
		integer& a = *this;
		if(b>=integerWordSize || b<=-integerWordSize) {
			a.digit.resize(2);
			a.size=2;
			a.digit[0] = b%integerWordSize;
			a.digit[1] = b/integerWordSize;
		}
		else {
			a.size=1;
			a.digit.resize(1);
			a.digit[0] = b;
		}
		return a;
	}

	friend std::ostream& operator<<(std::ostream& in, integer& a){
		a.normalize();
		auto old_settings = in.flags();

		in << a.digit[a.size-1];
		in << std::setfill('0');
		for( a.i = a.size-2; a.i!=-1; a.i--) in  << std::setw(9) << (a.digit[a.i]<0?-a.digit[a.i]:a.digit[a.i]);
		in.flags(old_settings);
		return in;
	}

	friend std::ostream& operator<<(std::ostream& in, integer&& a){
		a.normalize();
		auto old_settings = in.flags();

		in << a.digit[a.size-1];
		in << std::setfill('0');
		for( a.i = a.size-2; a.i!=-1; a.i--) in  << std::setw(9) << (a.digit[a.i]<0?-a.digit[a.i]:a.digit[a.i]);
		in.flags(old_settings);
		a.countTrim = 0;
		return in;
	}

	~integer(){}

	std::vector<bool> exponent;
	int countTrim{0}, oughtTrim{30};
	int fastProduct{100};
};
