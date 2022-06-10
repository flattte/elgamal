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
    public:
        Elgamal();
        ~Elgamal();

        static std::pair<lg_key, lg_key> keyGen();
        static void printHex(const cpp_int& num, size_t row);
        std::pair<cpp_int, cpp_int> encrypt(cpp_int M, const lg_key key) const;
        cpp_int decrypt(lg_key priv, std::pair<cpp_int, cpp_int> msg) const;
};
