#include <iostream>

class Thing{
    private:
        int x, y;
    public:
        int getX() const {return x;}
        int getY() const {return y;}
        void setX(const int& x){this->x = x;}
        void setY(const int& y){this->y = y;}
        Thing(){}
        Thing(const int& x, const int& y) : x(x), y(y) { std:: cout << "Constructed: " << x << ", " << y << std::endl; }
        Thing(const Thing& T){ std::cout << "Copied" << std::endl; this->x = T.getX(); this->y = T.getY();}
        void operator=(const Thing& t){ std::cout << "Assigned" << std::endl; this->x = t.getX(); this->y = t.getY(); }
        void operator=(const Thing&& t) { std::cout << "Moved\n"; this->x = t.getX(); this->y = t.getY();}
        friend Thing operator+(const Thing& t1, const Thing& t2){ return Thing(t1.x+t2.x, t1.y+t2.y); }
        virtual ~Thing(){ std:: cout << "Destructed: " << x << ", " << y << std::endl; }
};

int doSomething(){
    int x = 9;
    std::cout << &x << std::endl;
    return x;
}

void printThing(const char* name, const Thing& t){
    std::cout << name << ": " << t.getX() << ", " << t.getY() << std::endl;
}

int main(int argv, char** argc){
    Thing t1(4,3);
    Thing t2(5, 4);
    Thing t3(1, 3);
    Thing t4 = t1+t2+t3;
    Thing t5 = t4;

    short y = 5;
    std::cout << y << "\n";

    std::cout << sizeof(short) << "\n";

    std::cout << "<=== END ===>" << std::endl;
    return 0;
}
