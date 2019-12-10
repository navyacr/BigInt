/*
*	GID: 11
*   Author: Navya Chennagiri Ravikumar	
*   ID: 014352130

*/

#ifndef HW8_H
#define HW8_H
#include<vector>
#include<fstream>

using namespace std;

class BigInt{
	public:
	
		BigInt();
		BigInt(vector<int> v1);
		BigInt(vector<char> v1);
		BigInt(char v1[], int len);

		BigInt operator +(const BigInt b);
		BigInt operator -(const BigInt b);
		BigInt operator *(const BigInt b);
		bool operator <(const BigInt b);
		bool operator >(const BigInt b);
		bool operator <=(const BigInt b);
		bool operator >=(const BigInt b);
		bool operator ==(const BigInt b);
		BigInt& operator++();
		BigInt operator++(int);
	    BigInt& operator--();
	    BigInt operator--(int);
		bool is_equal(BigInt b);
		bool operator!();
		BigInt add(BigInt b);
		BigInt subtract(BigInt b, bool reverse);
        bool is_greater_than(BigInt b);
        BigInt remove_padding(BigInt b);
		vector<int> get_value();
		vector<int> value;
		bool negative=false;
		friend ostream & operator << (ostream &out, const BigInt &b);
		friend istream & operator >> (istream &in, BigInt &b);
		
};

#endif
