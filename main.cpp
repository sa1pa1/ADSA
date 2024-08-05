#include <iostream>
#include <string>
#include <sstream> 
#include <vector>
#include <math.h> 
#include <algorithm>

using namespace std;
void printVector(vector<int> number){
    for(int i =0; i <number.size();i++){
        cout<<number.at(i);
    }
}
int counter =1;
//school method addition I1 and I2
 vector<int> AdditionSchool(vector<int> i1, vector<int> i2, int b){
    int carry=0;
    vector<int> sum;
    int temp;
    int length;
    if(i1.size()>i2.size()){
        int difference=i1.size()-i2.size();
        i2.insert(i2.begin(),difference,0);
        length = i1.size();
    } else {
        int difference=i2.size()-i1.size();
        i1.insert(i1.begin(),difference,0);
        length = i2.size();
    }

    for(int i=length-1; i>=0; i--){
        temp = i1.at(i)+i2.at(i)+carry;
        carry = temp/b;
        temp = temp%b;
        sum.insert(sum.begin(),temp);
    }
    if(carry>0){
        sum.insert(sum.begin(),carry);
    }
    return sum;
}
//SUBTRACTION IMPLEMENTATION FOR KARATSUBA
vector<int> SubtractSchool(vector<int> i1, vector<int> i2, int b){
    int carry = 0;
    vector<int> sub;
    int temp;
    int length;

   if(i1.size()>i2.size()){
        int difference=i1.size()-i2.size();
        i2.insert(i2.begin(),difference,0);
        length = i1.size();
    } else {
        int difference=i2.size()-i1.size();
        i1.insert(i1.begin(),difference,0);
        length = i2.size();
    }

    for(int i =length -1;i>0;i++){
        temp = i1.at(i) - i2.at(i) - carry;
        if(temp<0){
            sub.insert(sub.begin(), temp+b);
            carry=1;
        } else {
            sub.insert(sub.begin(),temp);
            carry=0;

        }
    }
return sub;
}

vector<int> Karatsuba(vector<int> i1, vector<int> i2, int b){
if (i1.size()<i2.size()){
    int difference = i2.size()-i1.size();
    i1.insert(i1.begin(),difference,0);

} else {
    int difference = i1.size()-i2.size();
    i2.insert(i2.begin(),difference, 0);
}

//when reaches base case n=1;
if (i1.size()==1 || i2.size()==1){
    vector<int> results;
    unsigned long mult, int1 = 0, int2 = 0;

        for(int i=0 ; i<i1.size();i++){
            int1 = b*int1 + i1.at(i);
        }
        for(int i=0 ; i<i2.size(); i++){
            int2 = b*int2+ i2.at(i);
        }
        mult = int1*int2;

        while (mult>0){
            results.push_back(mult%b);
            mult=mult/b;
        }

        reverse(results.begin(),results.end());
        return results;
}
//dividing into a0,a1,b0,b1
int n = max(i1.size(),i2.size());
int k = (int)floor(n/2);
int subarr = (int)ceil(n/2);


}
int main(){
        string str;
    getline(cin,str);
    vector<int> number1; //first vector to store number
    vector<int> number2; //second vector to store number
    int base;
    int counter;
    int stringSize=str.size();

    counter=0;
    //parsing input
    for(int i =0; i<stringSize;i++){
        if(str.at(0)==' '){
            counter++;
            str.erase(0, 1);
        }
        if(counter==0){
            number1.push_back(str.at(0)-48);
            str.erase(0, 1);
        } else if (counter==1){
            number2.push_back(str.at(0)-48);
            str.erase(0, 1);
        } else{
            stringstream iss(str);
            iss >> base;
        }
    }
   
    vector<int> addition = AdditionSchool(number1,number2,base);

    //printVector(sub);
    printVector(addition);
    //printVector(simple);
    return 0;
}