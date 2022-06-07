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


cpp_int getPrime(){
    mt11213b base_gen(clock());
    independent_bits_engine<mt11213b, 512, cpp_int> gen(base_gen);

    cpp_int prime;
    cpp_int q;
    do{
        prime = gen();
        q = (prime - 1)/2;
    } while(!miller_rabin_test(prime, 25) && !miller_rabin_test(q, 25));

    return prime;
}


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

    T x1 = 0;
    T y1 = 1;
    T r1 = b;
    T r = a;
    T quotient, tmp;
    while (r1) {
        quotient = r / r1;

        tmp = r;
        r = r1;
        r1 = tmp - quotient * r1;

        tmp = x;
        x = x1;
        x1 = tmp - quotient * x1;

        tmp = y;
        y = y1;
        new_y = tmp - quotient * y1;
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
