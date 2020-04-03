#include "Time.hpp"
#include <iostream>

Time::Time(const char* message, double bias) : message(message), bias(bias) {
    start = std::chrono::high_resolution_clock::now();
}

Time::~Time(){
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = end-start;
    std::cout << message << " lasted " << (dur.count()*1000 - bias) << " ms\n"; 
}