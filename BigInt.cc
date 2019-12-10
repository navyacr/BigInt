/*
*	GID: 11
*   Author: Navya Chennagiri Ravikumar	
*   ID: 014352130

*/

#include "hw8.h"
#include<algorithm>
#include<fstream>
#include<iostream>
#include <sstream>

using namespace std;

// Function to validate if this is valid
// Exit the program if not valid
void validate(vector<int> vec) {
	
	int i = 0;
	while (i < vec.size()) {
		//cout << "Checking " << vec[i] << endl;
		if (vec[i] > 9 || vec[i] < 0){
			throw "Vector digit invalid";
		}
		i++;
	}

}

BigInt:: BigInt(){

}


//Constructor for int vector
BigInt::BigInt(vector<int> v1){


	int i = 0;
	//while(i<v1.size()){
			
	//}
    for(int i=0; i<v1.size(); i++){
        if (i == 0 && v1[i] < 0){
            negative = true;
            value.push_back(abs(v1[i]));
        } else {
            value.push_back(v1[i]);
        }
    }

    *this = remove_padding(*this);
    
    if (this->value.size() == 1 && this->value[0] == 0) {
    	this->negative = false;	
    }
    validate(this->value);
        
}

//Constructor for char array
BigInt::BigInt(char v1[], int len){

    int i = 0;
    if ( i < len) {
        if (i == 0 && v1[i] == '-') {
            negative = true;
        } else if (i == 0 && v1[i] == '+') {
                negative = false;
        } else {
            int digit = v1[i]-'0';
            value.push_back(digit);
        }
    }

    for(int i=1; i<len; i++){
        int digit = v1[i]-'0';
        value.push_back(digit);
    }
        
    *this = remove_padding(*this);
    
    if (this->value.size() == 1 && this->value[0] == 0) {
    	this->negative = false;	
    }
    
    validate(this->value);
    
}

//Constructor for char vector
BigInt::BigInt(vector<char> v1){

    int i = 0;
    if ( i < v1.size()) {
        if (v1[i] == '-') {
            negative = true;
        } else if (v1[i] == '+') {
                negative = false;
        } else {
        	int digit = v1[i]-'0';
            value.push_back(digit);
        }
    }

    for(int i=1; i<v1.size(); i++){
        value.push_back(v1[i]-'0');
    }
    
    *this = remove_padding(*this);
    
    if (this->value.size() == 1 && this->value[0] == 0) {
    	this->negative = false;	
    }
    
    validate(this->value);
    
}


// which BigInt is bigger ignoring the sign
bool BigInt::is_greater_than(BigInt b) {

    if (this->value.size() > b.value.size()){
        return true;
    } else if (this->value.size() < b.value.size()) {
        return false;
    } else {
        int i = 0;
        while (i < this->value.size()) {
            if (this->value[i] > b.value[i]) {
                return true;
            } else if (this->value[i] < b.value[i]) {
                return false;
            } else {
                i++;
            }
        }
        return false;
    }
}

// checking equality ignoring the sign
bool BigInt::is_equal(BigInt b) {


	//cout << this->value.size() << b.value.size() << endl;
    if (this->value.size() != b.value.size()){
        return false;
    } else {
        int i = 0;
        while (i < this->value.size()) {
            if (this->value[i] != b.value[i]) {
                return false;
            } else {
                i++;
            }
        }
        return true;
    }
}


//Ignoring the signs, just add two vectors
BigInt BigInt::add(BigInt b){

	BigInt res;
	int i = this->value.size()-1;
	int j = b.value.size()-1;
	int carry = 0;
	while(i >=0 && j >= 0){
	
		int result = this->value[i] + b.value[j] + carry;
		carry = result/10;
		
		res.value.insert(res.value.begin(), result%10);
		i--;
		j--;	
	}
	while(i>=0){
		int result = this->value[i] + carry;
		carry = result/10;
		
		res.value.insert(res.value.begin(), result%10);
		i--;
			
	}	
	while(j>=0){
		int result = b.value[j] + carry;
		carry = result/10;
		
		res.value.insert(res.value.begin(), result%10);
		j--;
			
	}	


	if(carry!=0){
	res.value.insert(res.value.begin(), carry);
	}
	
	return res;

}

// Ignoring the signs, just subtract two bigInts
// For a.subtract(b), if reverse, perform b - a, else a - b
// This function assumes you are always doing x - y, 
// where x is a bigger number ignoring the sign
BigInt BigInt::subtract(BigInt b, bool reverse){

	BigInt res;
	int i = this->value.size()-1;
	int j = b.value.size()-1;
	
	while(i >=0 && j >= 0){
	
        if (! reverse ) {
    		if (this->value[i] < b.value[j]) {
    			int k = i-1;
    			while (k >= 0){
    				if (this->value[k] > 0 ){
    					this->value[k]--;
    					this->value[i] += 10;
    					break;
    				} else {
    					this->value[k] = 9;
    				}
    			}
            } 
			res.value.insert(res.value.begin(), this->value[i]-b.value[j]);
		} else {
    		if (b.value[j] < this->value[i]) {
    			int k = j-1;
    			while (k >= 0){
    				if (b.value[k] > 0 ){
    					b.value[k]--;
    					b.value[j] += 10;
    					break;
    				} else {
    					b.value[k] = 9;
    				}
    			}
            } 
			res.value.insert(res.value.begin(), b.value[j]-this->value[i]);
		}
		
		i--;
		j--;	
	}
	while(i>=0){
		int result = this->value[i];
		
		res.value.insert(res.value.begin(), result);
		i--;
			
	}	
	while(j>=0){
		int result = b.value[j];
		res.value.insert(res.value.begin(), result);
		j--;
			
	}	

	
	return remove_padding(res);

}

// Overloading + operator
BigInt BigInt::operator +(const BigInt b){
	BigInt res;
	
	if (this->negative && ! b.negative) {
        if (this->is_greater_than(b) == true){
            res = this->subtract(b, false);
            res.negative = true;
        } else {
            res = this->subtract(b, true);
            res.negative = false;
        }
	} else if (! this->negative && b.negative) {
        if (this->is_greater_than(b) == true){
            res = this->subtract(b, false);
            res.negative = false;
        } else if (this->is_equal(b)) {
            res = this->subtract(b, true);
            res.negative = false;        
        } else {
            res = this->subtract(b, true);
            res.negative = true;
        }
	} else if (this->negative && b.negative) {
		res = this->add(b);
		res.negative = true;
	} else {
		res = this->add(b);
        res.negative = false;
	}
	
	return res;

}


// Overloading - operator
BigInt BigInt::operator -(const BigInt b){
	BigInt res;

	
	if (this->negative && ! b.negative) {
		res = this->add(b);
        res.negative = true;
	} else if (! this->negative && b.negative) {
		res = this->add(b);
        res.negative = false;
	} else if (this->negative && b.negative) {
        if (this->is_greater_than(b)){
		    res = this->subtract(b, false);
            res.negative = true;
        } else {
		    res = this->subtract(b, true);
            res.negative = false;
        }
	} else {
        if (this->is_greater_than(b)){
		    res = this->subtract(b, false);
            res.negative = false;
        } else if (this->is_equal(b)){
        	res = this->subtract(b,true); 
        	res.negative = false;
        } else {
		    res = this->subtract(b, true);
            res.negative = true;
        }
	}
	
	return res;


}
		

// Overloading > operator
bool BigInt::operator>(const BigInt b){

    if(this->negative && !b.negative){
        return false;
    } else if(!this->negative && b.negative){
        return true;

    } else {
        // Both are negative or both are positive here
        if(this->negative) {
        	if (this->is_equal(b)){
        		return false;
        	}
            else if(! this->is_greater_than(b)){
                return true;
            } else {
                return false;
            }
        } else {
            if(this->is_greater_than(b)){
                return true;
            } else {
                return false;
            }

        }
    }
}

// Overloading == operator
bool BigInt::operator==(const BigInt b){
    if ((this->negative != b.negative) || (this->value.size() != b.value.size())){
        return false;
    }

	if (this->is_equal(b)){
    	return true;
	}
	return false;
}

// Overloading ! operator
bool BigInt::operator!(){

    vector<int> a;
    a.push_back(0);
    BigInt zero(a);

    if(*this == zero){
        return true;

    }
    return false;


}

// Overloading >= operator
bool BigInt::operator>=(const BigInt b){
    if((*this > b) || (*this == b)){
        return true;
    }

    return false;

}

// Overloading <= operator
bool BigInt::operator<=(const BigInt b){
    if((*this < b) || (*this == b)){
        return true;
    }

    return false;

}

// Overloading < operator
bool BigInt::operator<(const BigInt b){
    if(this->negative && !b.negative){
        return true;
    } else if(!this->negative && b.negative){
        return false;
    } else {
        // Both are negative or both are positive here
        if(this->negative) {
            if(this->is_greater_than(b)){
                return true;
            } else {
                return false;
            }
        } else {
            if(this->is_greater_than(b)){
                return false;
            } else if(this->is_equal(b)) {
                return false;
            } else {
                return true;
            }

        }
    }
}


// Overloading * operator
BigInt BigInt::operator *(const BigInt b){

    vector<int> z={0};
    BigInt zero(z);
    BigInt ans(z);
    BigInt count = b;
    count.negative = false;
    
    for(;count > zero; --count ){
        ans = *this  + ans;
    }
    if(this->negative != b.negative){
        ans.negative = true;
    }else{
        ans.negative = false;
    }
	
	return ans;
	
}


// Overloading << operator
ostream& operator << (ostream &out, const BigInt &b){

    if(b.negative){
        out << "-";
    }
    for(int i=0; i<b.value.size(); i++){
        out << b.value[i];
    }
    
    if (b.value.size() < 1) {
    	out << 0;
    }

    return out;

}

// Overloading ++ (pre) operator
BigInt& BigInt::operator++() {
    vector<int> o = {1};
    BigInt one(o);
    *this = *this + one;
    return *this;
}

// Overloading ++(post) operator
BigInt BigInt::operator++(int) {
   BigInt temp = *this;
   ++*this;
   return temp;
}

// Overloading --(pre) operator
BigInt& BigInt::operator--() {
    vector<int> o = {1};
    BigInt one(o);
    *this = *this - one;
    return *this;
}

// Overloading --(post) operator
BigInt BigInt::operator--(int) {
   BigInt temp = *this;
   --*this;
   return temp;
}

// Remove any zeroes if there are any: like 0000765
BigInt BigInt::remove_padding(BigInt b){

	int i = 0;
	while(b.value[i] == 0 && b.value.size() > 1){
		b.value.erase(b.value.begin());
	} 
	return b;	
}

// Overloading >> operator
istream& operator >> (istream& in, BigInt &b){
  
  	char c;
  	vector<char> vec;
  	bool negative = false;
  	string line;
    getline(in, line);
    istringstream iss(line);
	int i = 0;
  	while(iss >> c) {
  		if (i == 0) {
  			if (c == '-'){
  				negative = true;
  				continue;
  			}
  			if (c == '+') {
  				continue;
  			}
  		}
  		vec.push_back(c);
  		i++;
  	}

  	b = BigInt(vec);
  	if (b.value.size() < 2 && b.value[0] == 0) {
  		b.negative = false;
    } else {
    	b.negative = negative;
    }
    return in;

}
