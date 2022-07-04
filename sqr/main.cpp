#include<iostream>
#include<limits>

using namespace std;
// 平方
double square(double input){
    return input * input;
}

// 开根号:按十进位
double my_squrt_1(double input, double precision=1e-15){
    double nowNum = input / 2;
    double nowPrecision = 1.;
    for(;;){
        if (square(nowNum) > input){
            nowNum = nowNum - nowPrecision;
            if (square(nowNum) < input){
                nowPrecision = nowPrecision * 0.1;
            } 
        }else{
            nowNum = nowNum + nowPrecision;
        }
        if(nowPrecision<precision || square(square(nowNum) - input) < square(precision)){
            break;
        }
    }
    return nowNum;
}

// 梯度下降
double my_squrt_2(double input, double precision=1e-15, double lr=0.01){
    double startNum = input / 2;
    for(;;){
        startNum = startNum - lr*4.*(startNum*startNum*startNum-input*startNum);
        if (square(square(startNum) - input) < square(precision)){  
            break;
        }
    }
    return startNum;
}

// 牛顿法
double nt_squrt(double input, double precision=1e-15){
    double startNum = input / 2;
    for(int i=0; i< 10; i++){
        startNum = startNum - (square(startNum)-input) / (2*startNum);
        // cout << startNum << endl;
        if (square(square(startNum) - input) < square(precision)){  
            break;
        }
    }
    return startNum;
}

int main(){
    cout.precision(numeric_limits<double>::digits10 + 1);
    cout << my_squrt_1(7.) << endl;
    cout << my_squrt_2(7.) << endl;
    cout << nt_squrt(7.)  << endl;
}