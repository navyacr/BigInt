#include "hw8.h"
#include<iostream>
#include<cstring>
#include<vector>
#include<assert.h>

using namespace std;

void print (BigInt b) {

    if (b.negative) {
        cout << "-";
    }
  	for (int i=0; i<b.value.size(); i++){
       	cout << b.value[i];
    }

    cout << endl;


}

int main(){

    //Test1
	vector<int> num1={1}, num2={3};
	BigInt b1(num1), b2(num2), ans1;
	ans1 = b1 + b2;

	cout << "ans1: " << ans1 << endl;
	
	//Test2
	vector<char> num3={'1'}, num4={'3'};
    BigInt b3(num3), b4(num4), ans2;
    ans2 = b3 + b4;

    cout << "ans2: " << ans2 << endl;
    cout << "++ans2: " << ++ans2 << endl;
    cout << "ans2--: " << ans2-- << endl;
    cout << "ans2: " << ans2 << endl;

    //Test3
    char num5[] = "-123", num6[] = {'-','1','2','3','\0'};
//    cout << strlen(num6);
    BigInt b5(num5, strlen(num5)), b6(num6, strlen(num6)), ans3;
//    ans3 = b6 - b5;
	if (b5 <= b6) {
	    cout << b5 << " is lesser than/equal to " << b6 << endl;
	}
	if (b5 == b6){
	    cout << b5 << " is equal to " << b6 << endl;
	}
	if (b5 > b6){
	    cout << b5 << " is greater than" << b6 << endl;
	}
	
	//Test4
	vector<int> num7={-1,2,4,5,6,7,3}, num8={5,1};
	BigInt b7(num7), b8(num8), ans4;
	
	ans4 = b7 * b8;
	cout << "Product: " << ans4 << endl;

	//Test5
	vector<char> num9={'+','1'};
    BigInt b9(num9);

    cout << "b9: " << b9 << endl;
    cout << "--b9: " << --b9 << endl;
    vector<int> z={0};
    BigInt zero(z);
    assert(b9==zero);

	//Test6
	vector<char> num10={'-', '1'};

    BigInt b10(num10);
	cout << b10 << endl;    
    cout << !b10 << endl;
    
    //Test7
     BigInt b11;
     cout << "Input valid BigInt: " ;
     cin >> b11;
     cout << b11 << endl;
     
     //Test8
     //vector<int> vec={};
     //BigInt b12(vec);
     //cout<<b12<<endl;
     
 	 //final test
 	 
 	/* vector<char> num11={'+','5','4','3','2','4'};//segmentation fault
 	 vector<char> num12={'+','5','4','3','2','4'};*/
 	 
 	 vector<int> num11={2,3};
 	 vector<int> num12={2,3};
 	 BigInt b13(num11);
 	 BigInt b14(num12);
 	 cout<<"Sum = "<<(b13+b14)<<endl;
 	 cout<<"difference = "<<(b13-b14)<<endl;
 	 cout<<"product = "<<(b13*b14)<<endl;
 	 cout<<"not = "<<(!b14)<<endl;
	 cout<<"equal = "<<(b13==b14)<<endl;
	 cout<<">= :"<<(b13>=b14)<<endl;
	 cout<<"> :"<<(b13>b14)<<endl;
	 cout<<"<= :"<<(b13<=b14)<<endl;
	 cout<<"< :"<<(b13<b14)<<endl;
	 cout<<"pre ++ :"<<(++b14)<<endl;
	 cout<<"post ++ :"<<(b14++)<<endl;
	 cout<<"pre -- :"<<(--b14)<<endl;
	 cout<<"post -- :"<<(b14--)<<endl;
     
    
    

}


