#include <iostream>
#include <string>
#include <sstream> 
#include <vector>
#include <math.h> 
#include <algorithm>

using namespace std;

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
      vector<int> sub;
    int carry = 0;
    int temp=0;
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

    for(int i =length -1;i>=0;i--){
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

vector<int> MultiplySchool(vector<int> i1, vector<int> i2, int b){
	int temp=0;
	int carry=0;
    vector<int> mult;
	vector<int> result;

 	reverse(i1.begin(),i1.end());
    reverse(i2.begin(),i2.end());
    result.clear();
    //larger number in length on top
	if(i1.size()<i2.size()){
		i1.swap(i2);
	}
    int size1 = i1.size();
    int size2 = i2.size();
    
	for(int i=0; i<size2;i++){
		for(int j=0;j<size1;j++){
			temp=i1[j]*i2[i]+carry;
			if(temp>=b){
				mult.push_back(temp%b);
				carry=((temp-(temp)%b)/b);
			}
            
            else {
			mult.push_back(temp%b);
			carry=0;
			}
		}
		if(carry>0){
			mult.push_back(carry);
            carry =0;
		} 
        
		for(int k = 0; k<i;k++){
			mult.insert(mult.begin(),0);
		}
        reverse(mult.begin(),mult.end());
		result= AdditionSchool(mult, result, b);
		mult.clear();

	}
	return result;
}

vector<int> Karatsuba(vector<int> i1, vector<int> i2, int b){
//when reaches base case n=1;
if (i1.size()==1 || i2.size()==1){
    vector<int> results;
    unsigned long long mult, int1 = 0, int2 = 0;
    int size1 = i1.size();
    int size2 = i2.size();

        for(int i=0 ; i<size1;i++){
            int1 = b*int1 + i1.at(i);
        }
        for(int i=0 ; i<size2; i++){
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
if (i1.size()>i2.size()){
    int difference = i1.size()-i2.size();
    i2.insert(i2.begin(),difference,0);

} else {
    int difference = i2.size()-i1.size();
    i1.insert(i1.begin(),difference, 0);
}


//dividing into a0,a1,b0,b1
int n = max(i1.size(),i2.size());

if (n<4){
    vector<int> result;
    result = MultiplySchool(i1,i2,b);
    return result;

}else {
int k = (int)floor(n/2.0);
int subarr = (int)ceil(n/2.0);

vector<int> a1;
vector<int> a0;

for (int i =0; i<subarr;i++){
    a1.push_back(i1.at(i));
}
for (int i = subarr; i <i1.size();i++){
    a0.push_back(i1.at(i));
}

vector<int>b1;
vector<int>b0;

for (int i = 0; i<subarr; i++){
    b1.push_back(i2.at(i));
}
for (int i = subarr; i <i2.size(); i++){
    b0.push_back(i2.at(i));
}
    
vector<int> p0 = Karatsuba(a0,b0,b);
vector<int> p1 = Karatsuba(AdditionSchool(a1,a0,b),AdditionSchool(b1,b0,b),b);
vector<int> p2 = Karatsuba(a1,b1,b);

vector<int> p3 = SubtractSchool(p1,AdditionSchool(p2,p0,b),b);

for(int i =0; i <k*2;i++){
        p2.push_back(0);
    }
 for(int i=0 ; i<k ; i++){
        p3.push_back(0);
    }

vector<int> result = AdditionSchool(p0,AdditionSchool(p2,p3,b),b);
return result;
}}

//PRINT RESULT
void print(vector<int> number){
    int size = number.size();
    for(int i =0; i <size;i++){
        cout<<number.at(i);
    }
}

int main(){
        string str;
    getline(cin,str);
    vector<int> no1; //first vector to store number
    vector<int> no2; //second vector to store number
    int base=0;
    int counter=0;
    int size=str.size();

    //parsing input
    for(int i =0; i<size;i++){
        if(str.at(0)==' '){
            counter++;
            str.erase(0, 1);
        }
        if(counter==0){
            no1.push_back(str.at(0)-48);
            str.erase(0, 1);
        } else if (counter==1){
            no2.push_back(str.at(0)-48);
            str.erase(0, 1);
        } else{
            stringstream iss(str);
            iss >> base;
            break;
        }
    }
   
    vector<int> addition = AdditionSchool(no1,no2,base);
    vector<int> mult = Karatsuba(no1,no2,base);
    vector<int> multresult;
    auto it = std::find_if(mult.begin(), mult.end(), [](int nonzero){
        return nonzero !=0;
    });
    
    if (it!=mult.end()){
        int size = mult.size();
        int checkzero = distance(mult.begin(),it);
        for(int i =0; i <size-checkzero;i++){
        multresult.push_back(mult.at(i+checkzero));
    }
    }

    print(addition);
    std::cout<<" ";
    print(multresult); //karatsuba result 
    std::cout<<" "<<0; // division result 
    //printVector(simple);
    return 0;
}
