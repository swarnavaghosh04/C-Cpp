#define SOMETHING "hello"
#include <iostream>

class Hello{
    int a, b;
    public:
        Hello(int a=0, int b=0) : a(a), b(b){}
        Hello& operator+=(int v){
            a+=v;
            b+=v;
            return (*this);
        }

}

int main(int argc, const char** argv){

    std::cout << "This is SOMETHING" << std::endl;
    return 0;
}