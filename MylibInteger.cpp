#define NDEBUG
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
#include <cassert>

const int64_t powers10[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,10000000000000000,100000000000000000,1000000000000000000};
const int64_t& integerWordSize = powers10[9];
const int64_t& integerWordSize2 = powers10[18];
const int64_t zero = 0;
struct integer{
	integer(): size{0}, digit(0), exponent(64){}
	explicit integer(size_t&& d): size{static_cast<int64_t>(d)}, digit(d,0), exponent(64){}
	explicit integer(size_t& d): size{static_cast<int64_t>(d)}, digit(d,0), exponent(64){}
	// the next constructor shall be changed if integerWordSize is not powers10[9]
	integer(int64_t n){
		if( n >= integerWordSize2 || n <= -integerWordSize2 ){
			size=3;
			digit=decltype(digit)(3);
			digit[0]=(n%integerWordSize);
			n/=integerWordSize;
			digit[1]=(n%integerWordSize);
			n/=integerWordSize;
			digit[2]=n;
		} else if( n >= integerWordSize || n <= -integerWordSize ){
			size=2;
			digit=decltype(digit)(2);
			digit[0]=(n%integerWordSize);
			n/=integerWordSize;
			digit[1]=n;
		} else {
			size=1;
			digit=decltype(digit)(1);
			digit[0]=n;
		}
	}
	integer(integer&& a): size{0}, digit(0), exponent(64), countTrim{0}{
		std::swap(size, a.size);
		std::swap(digit, a.digit);
		std::swap(countTrim, a.countTrim);
	}
	integer(integer& a): size{a.size}, digit(a.digit), exponent(64), countTrim{a.countTrim} {}

	int64_t size;
	int64_t i,j;
	std::vector<int64_t> digit;
	void normalize(){
		//raw_print();
		if(!size) 
			return;
		// removing leading 0s
		for(i=size-1; digit[i]==zero && i; --i);
		if( digit[i]==zero ){
			digit.resize(0);
			size=0;
			countTrim=0;
			return;
		}
		//raw_print();
		size=++i;
		// trimming 1:
		for( i=0; i!=size-1; ++i )
			if( digit[i]>=integerWordSize || digit[i]<=-integerWordSize ){
				digit[i+1] += digit[i]/integerWordSize;
				digit[i] %= integerWordSize;
			}
		if( digit[size-1]>=integerWordSize || digit[size-1]<=-integerWordSize ){
			digit.resize(++size);
			digit[size-1]=digit[size-2]/integerWordSize;
			digit[size-2]%=integerWordSize;
		} else
			digit.resize(size);
		//raw_print();
		// uniformization of signs:
		if(digit[size-1]<zero){
			for(i=0; i!=size-1; ++i) 
				if(digit[i]>zero){
					digit[i]-=integerWordSize;
					++digit[i+1];
				}
		}
		else{
			for(i=0;i!=size-1;i++) 
				if(digit[i]<0){
					digit[i]+=integerWordSize;
					--digit[i+1];
				}
		}
		//raw_print();
		// removing leading 0s
		for(i=size-1;digit[i]==zero && i!=0; --i);
		digit.resize(i+1);
		size=i+1;
		countTrim = 0;
		//raw_print();
	}

	integer operator+(integer& b){
		if(this->size > b.size) 
			return integerSum(b,*this);
		else 
			return integerSum(*this,b);
	}

	integer operator+(integer&& b){
		if(this->size > b.size) 
			return integerSum(b,*this);
		else 
			return integerSum(*this,b);
	}

	integer& operator+=(integer& b){
		if(size < b.size) {
			digit.resize(b.size);
			for( i = 0; i != size; ++i)
				digit[i] += b.digit[i];
			for(; i != b.size; ++i )
				digit[i] = b.digit[i];
		}
		else{
			for( i = 0; i != b.size; ++i )
				digit[i] += b.digit[i];
		}
		countTrim = b.countTrim + countTrim + 2;
		size = digit.size();
		if(countTrim>oughtTrim) 
			normalize();
		return *this;
	}

	integer& operator+=(integer&& b){
		if(size < b.size) {
			digit.resize(b.size);
			for( i = 0; i != size; ++i)
				digit[i] += b.digit[i];
			for(; i != b.size; ++i )
				digit[i] = b.digit[i];
		}
		else{
			for( i = 0; i != b.size; ++i )
				digit[i] += b.digit[i];
		}
		countTrim = b.countTrim + countTrim + 2;
		size = digit.size();
		if(countTrim>oughtTrim) 
			normalize();
		return *this;
	}

	integer integerSum(integer& min, integer& max){
		integer sum(max.size);

		for(i = 0; i != min.size; ++i)
			sum.digit[i] = min.digit[i]+max.digit[i];
		for(; i != max.size; ++i)
			sum.digit[i] = max.digit[i];
		sum.countTrim = max.countTrim + min.countTrim + 2;
		if(sum.countTrim > sum.oughtTrim) 
			sum.normalize();
		return sum;
	} 

	integer operator-(integer& b){
		if(size < b.size) {
			integer dif(b.size);
			for(i = 0; i != size; ++i)
				dif.digit[i] = digit[i]-b.digit[i];
			for(; i != b.size; ++i)
				dif.digit[i] = -b.digit[i];
			dif.countTrim = countTrim + b.countTrim + 2;
			if(dif.countTrim > oughtTrim) 
				dif.normalize();
			return dif;
		}
		else{
			integer dif(size);
			for( i = 0; i != b.size; ++i )
				dif.digit[i] = digit[i]-b.digit[i];
			for( ; i != size; ++i)
				dif.digit[i] = digit[i];
			dif.countTrim = countTrim + b.countTrim + 2;
			if(dif.countTrim > oughtTrim) 
				dif.normalize();
			return dif;
		}
	}

	integer operator-(integer&& b){
		if(size < b.size) {
			integer dif(b.size);
			for(i = 0; i != size; ++i)
				dif.digit[i] = digit[i]-b.digit[i];
			for(; i != b.size; ++i)
				dif.digit[i] = -b.digit[i];
			dif.countTrim = countTrim + b.countTrim + 2;
			if(dif.countTrim > oughtTrim) 
				dif.normalize();
			return dif;
		}
		else{
			integer dif(size);
			for( i = 0; i != b.size; ++i )
				dif.digit[i] = digit[i]-b.digit[i];
			for( ; i != size; ++i)
				dif.digit[i] = digit[i];
			dif.countTrim = countTrim + b.countTrim + 2;
			if(dif.countTrim > oughtTrim) 
				dif.normalize();
			return dif;
		}
	}


	integer& operator-=(integer& b){
		if(size < b.size) {
			digit.resize(b.size);
			for( i = 0; i != size; ++i )
				digit[i] -= b.digit[i];
			for(;i != b.size; ++i)
				digit[i] = -b.digit[i];
		}
		else{
			for( i = 0; i != b.size; ++i)
				digit[i] -= b.digit[i];
		}
		countTrim = countTrim + b.countTrim + 2;
		size = digit.size();
		if(countTrim>oughtTrim) 
			normalize();
		return *this;
	}

	integer& operator-=(integer&& b){
		if(size < b.size) {
			digit.resize(b.size);
			for( i = 0; i != size; ++i )
				digit[i] -= b.digit[i];
			for(;i != b.size; ++i)
				digit[i] = -b.digit[i];
		}
		else{
			for( i = 0; i != b.size; ++i)
				digit[i] -= b.digit[i];
		}
		countTrim = countTrim + b.countTrim, + 2;
		size = digit.size();
		if(countTrim>oughtTrim) 
			normalize();
		return *this;
	}

	integer& operator=(integer& b){
		if(&b != this){
			digit=b.digit;
			size=b.size;
			countTrim=b.countTrim;
		}
		return *this;
	}

	integer& operator=(integer&& b){
		digit.resize(0);
		size=0;
		countTrim=0;
		std::swap(digit, b.digit);
		std::swap(size, b.size);
		std::swap(countTrim, b.countTrim);
		return *this;
	}

	integer& operator=(int64_t n){
		//std::cout << "=" << n << std::endl;
		if( n >= integerWordSize2 || n <= -integerWordSize2 ){
			size=3;
			digit.resize(3);
			digit[0]=(n%integerWordSize);
			n/=integerWordSize;
			digit[1]=(n%integerWordSize);
			n/=integerWordSize;
			digit[2]=n;
		} else if( n >= integerWordSize || n <= -integerWordSize ){
			size=2;
			digit.resize(2);
			digit[0]=(n%integerWordSize);
			n/=integerWordSize;
			digit[1]=n;
		} else {
			size=1;
			digit.resize(1);
			digit[0]=n;
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& in, integer& a){
		assert(a.size==a.digit.size());
		if(a.size==0){
			std::cout << 0;
			return in;
		}
		if(a.countTrim)
			a.normalize();
		if(a.size==0){
			std::cout << 0;
			return in;
		}
		auto old_settings = in.flags();
		
		in << a.digit[a.size-1];
		in << std::setfill('0');
		for( a.i = a.size-2; a.i>=zero; --a.i) 
			in  << std::setw(9) << (a.digit[a.i]<zero?-a.digit[a.i]:a.digit[a.i]);
		in.flags(old_settings);
		return in;
	}

	friend std::ostream& operator<<(std::ostream& in, integer&& a){
		assert(a.size==a.digit.size());
		if(a.size==0){
			std::cout << 0;
			return in;
		}
		if(a.countTrim)
			a.normalize();
		if(a.size==0){
			std::cout << 0;
			return in;
		}
		auto old_settings = in.flags();

		in << a.digit[a.size-1];
		in << std::setfill('0');
		for( a.i = a.size-2; a.i>=zero; --a.i) 
			in  << std::setw(9) << (a.digit[a.i]<zero?-a.digit[a.i]:a.digit[a.i]);
		in.flags(old_settings);
		a.countTrim = 0;
		return in;
	}

	void raw_print(){
		for( auto &cc: digit )
			std::cout << cc << '_';
		std::cout << std::endl;
	}

	~integer(){}

	std::vector<bool> exponent;
	int countTrim{0};
	static const int oughtTrim{999999998};
	int fastProduct{100};
};
