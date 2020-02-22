#include <iostream>

class Thing{
    private:
        int x, y;
    public:
        int getX() const {return x;}
        int getY() const {return y;}
        void setX(const int& x){this->x = x;}
        void setY(const int& y){this->y = y;}
        Thing(const int& x, const int& y) : x(x), y(y) { std:: cout << "Constructed" << std::endl; }
        Thing(const Thing& T){ std::cout << "Copied" << std::endl; }
        Thing(const Thing&& T){ std::cout << "Moved" << std::endl; }
        virtual ~Thing(){ std:: cout << "Destructed" << std::endl; }
};

Thing doSomething(){
    Thing t(4, 5);
    std::cout << "returning" << std::endl;
    return t;
}

int main(int argv, char** argc){
    std::cout << "Creating t1" << std::endl;
    Thing t1 = doSomething();
    std::cout << "Creating t2" << std::endl;
    Thing t2 = t1;
    return 0;
}
