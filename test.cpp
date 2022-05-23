#include "crypto/algorithm.h"
#include "crypto/elgamal.h"
#include "crypto/elgamal.cpp"
#include <iostream>
#include <string>


typedef boost::multiprecision::cpp_int cpp_int;

int main(){

    // cpp_int b = 11;
    // cpp_int x = 1003122100;
    // cpp_int m = 907381273289330;
    // cpp_int res = fastExpMod(b, x, m);
    // std::cout << res << "\n";

    // int gcd = _gcd(100, 10);
    // std::cout << gcd << "\n";
    
    // gcd = _gcd(21, 15);
    // std::cout << gcd << "\n";

    // gcd = _gcd(91, 17);
    // std::cout << gcd << "\n";

    // cpp_int a, g;
    // cpp_int k = extendedEuclid(static_cast<cpp_int>(78), static_cast<cpp_int>(20), a ,g);
    // std::cout << a << ' ' << b; 

    cpp_int l = 100;
    cpp_int u = 100000;
    cpp_int a = getPrime();
    std::cout << std::hex << a <<std::endl;
    Elgamal::printHex(a, 16);
    
}