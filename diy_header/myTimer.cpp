#include"myTimer.h"

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
    start_ = std::chrono::system_clock::now();
}

inline void TimeMeter::Split()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto us = duration_cast<std::chrono::microseconds>(now - start_).count();
    printf("%ld µs ≈ %.3lf ms ≈ %.3lf s\n", us, us / 1000.0, us / 1000000.0);
}