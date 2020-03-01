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
        Thing(const int& x, const int& y) : x(x), y(y) { std:: cout << "Constructed: " << x << ", " << y << " @ " << this << std::endl; }
        Thing(const Thing& T){ std::cout << "Copied" << std::endl; this->x = T.getX(); this->y = T.getY();}
        void operator=(const Thing& t){ std::cout << "Assigned" << std::endl; this->x = t.getX(); this->y = t.getY(); }
        void operator=(Thing&& t) { std::cout << "Moved\n"; this->x = t.getX(); this->y = t.getY();}
        friend Thing operator+(const Thing& t1, const Thing& t2){ return Thing(t1.x+t2.x, t1.y+t2.y); }
        virtual ~Thing(){ std::cout << "Destructed: " << x << ", " << y << " @ " << this << std::endl; }
};

class AnotherThing{
    private:
        int x;
    public:
        AnotherThing(int x = 0) : x(x) {}
};

class Num{
    private:
        short n;
        short q;
    public:
        Num(short n=0, short q=0) : n(n), q(q) {}
        ~Num(){std::cout << "DEST" << std::endl;}
        operator short(){return n;}
        Num operator+(Num other) { return Num(n+other.n); }
        Num& operator+=(Num other) {
            n += other.n;
            return (*this);
        }
};

void printThing(const char* name, const Thing& t){
    std::cout << name << ": " << t.getX() << ", " << t.getY() << std::endl;
}

AnotherThing thisThing(){
    AnotherThing t = 5;
    throw 1;
    std::cout << "Func: " << &t << std::endl;
    return t;
}

int main(int argv, char** argc){

    #if 0

    Thing t1(4,3);
    Thing t2(5, 4);
    Thing t3(1, 3);

    std::cout << "1\n";
    Thing t4 = t1+t2+t3;     // Nothing

    std::cout << "2\n";
    t3 = t1+t2;              // Move

    std::cout << "3\n";
    t2 = t1;                 // Assigned

    Num n(0);
    std::cout << &n << std::endl;
    
    {
        Num& q = n+=5;
        std::cout << &q << std::endl;
    }

    std::cout << (int)n << std::endl;
    #endif

    try {AnotherThing at = thisThing();}
    catch(int val){
        std::cout << val << std::endl;
    }
\

    return 0;
}
