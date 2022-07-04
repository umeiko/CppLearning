#ifndef myTimer_H
#define myTimer_H

#include <chrono>
#include <cstdio>

class TimeMeter
{
    using TimeType = std::chrono::time_point<std::chrono::system_clock>;
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

#endif