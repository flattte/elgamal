#pragma once 
#include <type_traits>
#include <stdlib.h>
#include "algorithm.h"


struct lg_key { 
    cpp_int g;
    cpp_int x;
    cpp_int p;
    lg_key(cpp_int g, cpp_int x, cpp_int p) : g(g), x(x), p(p) {};
};


class Elgamal {
    private:
        static std::pair<lg_key, lg_key> keyGen();
        cpp_int hold_M;
        cpp_int hold_C;

    public:
        Elgamal();
        ~Elgamal();

        static void printHex(const cpp_int& num, size_t row);
        void setM(const cpp_int m);
        void setC(const cpp_int c);
        cpp_int getM() const;
        cpp_int getC() const; 
    
        std::pair<cpp_int, cpp_int> encrypt(cpp_int M, const lg_key key) const;
        cpp_int decrypt(lg_key priv, std::pair<cpp_int, cpp_int> msg) const;
};