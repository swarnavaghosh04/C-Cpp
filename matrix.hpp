#pragma once

template<typename T>
class MATRIX{
    
    private:
        int rows;
        int columns;
        T* matrix;
    
    public:
        T get(int, int);
        void set(int, int, T);
        MATRIX(int, int);
        ~MATRIX();
};