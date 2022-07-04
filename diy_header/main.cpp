#include<iostream>
#include<limits>
#include<math.h>
#include<chrono>
#include<cstdio>

// #include"myTimer.h"

using namespace std;
using namespace std::chrono;
// 平方
double square(double input){
    return input * input;
}

class TimeMeter
{
    using TimeType = high_resolution_clock::time_point;
public:
    TimeMeter(bool auto_split = false);
    ~TimeMeter();
	// 重置计时器
    void Reset();
    // 打印经过的时间
    void Split();

private:
    TimeType start_;
    bool auto_split_;
};

inline TimeMeter::TimeMeter(bool auto_split)
    : auto_split_(auto_split)
{
    Reset();
}

inline TimeMeter::~TimeMeter()
{
    if (auto_split_) Split();
}

inline void TimeMeter::Reset()
{
    start_ = high_resolution_clock::now();
}

inline void TimeMeter::Split()
{
    auto now = high_resolution_clock::now();
    auto us = duration_cast<std::chrono::microseconds>(now - start_);
    printf("%ld µs ≈ %.3lf ms ≈ %.3lf s\n", us, us / 1000.0, us / 1000000.0);
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

int main(){
    TimeMeter t;
    cout.precision(numeric_limits<double>::digits10 + 1);
    t.Reset();
    for(int i=0; i<10000; i++){
        my_squrt_1(7.);
    }
    // cout << my_squrt_1(7.) << endl;
    t.Split();
    t.Reset();
    for(int i=0; i<101000; i++){
        my_squrt_2(7.);
    }
    t.Split();
}