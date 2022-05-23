#pragma once
#include <type_traits>
#include <iostream>
#include <time.h> 


#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::random;
using namespace boost::multiprecision;
typedef boost::multiprecision::cpp_int cpp_int;

static boost::random::mt19937 gen(clock());



template<typename T>
constexpr T fastExpMod(T g, T x, T p){
    //static_assert(std::is_arithmetic<T>::value, "[x] fastExpMod is only well defined for numeric-like types.");
    
    T ret;
    if(1 & x)
        ret = g;
    else
        ret = 1;

    while(x){
        x >>= 1;
        g = (g * g) % p;
        if(x & 1) // >> multiply only accumulated powers
            ret = (ret * g) % p;        
    }

    return ret;
}

template<typename T>
constexpr T _gcd(T a, T b){
    //static_assert(std::is_arithmetic<T>::value, "[x] fastExpMod is only well defined for numeric-like types.");
    
    if(a < 0) a = -a; // no re-asignment -->> is fast only 2 rax
    if(b < 0) b = -b;
    while(b != 0){
        a %= b;
        if(a == 0) return b;
        b %= a;
    }

    return a;
}

// solves ax + by = gcd(a,b)
template<typename T>
T extendedEuclid(T a, T b, T &x, T &y) {
    //static_assert(std::is_arithmetic<T>::value, "[x] fastExpMod is only well defined for numeric-like types.");

    x = 1;
    y = 0;

    if (0 == b) return a;

    T new_x = 0;
    T new_y = 1;
    T new_r = b;
    T r = a;
    T quotient, tmp;
    while (new_r) {
        quotient = r / new_r;

        tmp = r;
        r = new_r;
        new_r = tmp - quotient * new_r;

        tmp = x;
        x = new_x;
        new_x = tmp - quotient * new_x;

        tmp = y;
        y = new_y;
        new_y = tmp - quotient * new_y;
    }
    return r;
}

template<typename T>
T multiplicativeInverse(T a, T m){
    //static_assert(std::is_arithmetic<T>::value, "[x] fastExpMod is only well defined for numeric-like types.");
    T x, y;
    T r = extendedEuclid(a, m, x, y);
    if(r > 1){
        return -1;
    }

    return x < 0 ? x + m : x;
}


void seedRNG(){
    gen.seed(static_cast<unsigned int>(std::time(0)));
}


cpp_int getRN(cpp_int l, cpp_int u){
    boost::random::uniform_int_distribution<cpp_int> dist(l, u);
    return dist(gen);
}


cpp_int getPrime(){
    
    mt11213b base_gen(clock());
    independent_bits_engine<mt11213b, 512, cpp_int> gen(base_gen);

    cpp_int prime;

    do{
        prime = gen();
    } while( !miller_rabin_test(prime, 25));

    return prime;
}