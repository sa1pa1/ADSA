#include <iostream>
#include <string>
#include <sstream> 
#include <vector>
#include <math.h> 
#include <algorithm>
int counter =1;
//school method addition I1 and I2
int addition(vector<int> i1, vector<int> i2, int b){
    int carry=0;
    vector<int> sum;
    int temp;
    int length;
    if(number1.size()>number2.size()){
        int length_difference=number1.size()-number2.size();
        number2.insert(number2.begin(),length_difference,0);
        length = number1.size();
    } else {
        int length_difference=number2.size()-number1.size();
        number1.insert(number1.begin(),length_difference,0);
        length = number2.size();
    }

    for(int i=length-1; i>=0; i--){
        temp = number1.at(i)+number2.at(i)+carry;
        carry = temp/base;
        temp = temp%base;
        sum.insert(sum.begin(),temp);
    }
    if(carry>0){
        sum.insert(sum.begin(),carry);
    }

    return sum;
}

