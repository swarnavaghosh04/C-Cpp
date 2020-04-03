#include <chrono>

class Time{
    private:
        std::chrono::high_resolution_clock::time_point start, end;
        const char* message;
        double bias;
    public:
        Time(const char*, double=0);
        ~Time();
};