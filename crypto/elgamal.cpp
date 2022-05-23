#include "elgamal.h"
#include <iostream>
#include <sstream>
#include <string>



std::pair<lg_key, lg_key> Elgamal::keyGen(){ 
    seedRNG();
    cpp_int p = getPrime(); // p
    cpp_int q = (p - 1)/2;
    cpp_int g = 0;

    // g
    while(true){
        g = getRN(2, p-1);
        if (_gcd(g, q) == 1){
            if(fastExpMod(g, q, p) == 1)
                break;
        }
    }
    // x
    cpp_int x;
    x = 0;
    while(true){ 
        x = getRN(2, p -1);
        if(_gcd(x, p) == 1)
            break;
    }

    cpp_int a = fastExpMod(g, x, p);
    lg_key pub(g, a, p);

    lg_key priv(g, x, p);

    return std::make_pair(pub, priv);
}



std::pair<cpp_int, cpp_int> Elgamal::encrypt(cpp_int M, const lg_key key) const {

    cpp_int y = 0;
    do{
        y = getRN(static_cast<cpp_int>(2), key.p - 1);
    }  while(_gcd(y, key.p) != 1);

    cpp_int B = fastExpMod(key.g, key.x, key.p);

    cpp_int s = fastExpMod(B, y, key.p);
    cpp_int A = fastExpMod(key.g, y, key.p);

    M = M * s;
    return std::make_pair(A, M);
}




cpp_int Elgamal::decrypt(lg_key priv, std::pair<cpp_int, cpp_int> msg) const {
    cpp_int A = msg.first;
    cpp_int M = msg.second;

    cpp_int shared_secret = fastExpMod(A, priv.x, priv.p);
    cpp_int s_multiplicative_inverse = multiplicativeInverse(shared_secret, priv.p);
    
    M = (M * s_multiplicative_inverse) % priv.p;

    return M;
}



void Elgamal::printHex(const cpp_int& num, size_t row=8){
    std::string ctx;
    std::stringstream s;
    s << std::hex << num;
    ctx = s.str();
    
    for(size_t i = 0; i < ctx.size(); ++i){
        if(i%2 == 0) 
            std::cout << " ";
        if(i%row == 0)
            std::cout << "\n";

        std::cout <<ctx[i];
    }
    std::cout << std::endl;
}



void Elgamal::setM(cpp_int m){
    hold_M = m;
}



void Elgamal::setC(cpp_int c){
    hold_C = c;
}



cpp_int Elgamal::getM() const {
    return hold_M;
}



cpp_int Elgamal::getC() const {
    return hold_C;
}