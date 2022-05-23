#include "elgamal.h"
#include <iostream>
#include <sstream>
#include <string>

Elgamal::Elgamal(){}
Elgamal::~Elgamal(){}


std::pair<lg_key, lg_key> Elgamal::keyGen(){ 
    seedRNG();
    cpp_int p = getPrime(); // p
    cpp_int q = (p - 1)/2;
    cpp_int g = 0;

    while(true){
        g = getRN(2, p-1);
        if (_gcd(g, q) == 1){
            if(fastExpMod(g, q, p) == 1)
                break;
        }
    }

    cpp_int x= 0;
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


std::pair<cpp_int, cpp_int> Elgamal::encrypt(cpp_int M, const lg_key pub) const {
    cpp_int public_key = pub.x;

    cpp_int y = 0; // local random number to raise msg to
    do{
        y = getRN(static_cast<cpp_int>(2), pub.p - 1);
    }  while(_gcd(y, pub.p) != 1);

    cpp_int B = fastExpMod(pub.g, y, pub.p);
    cpp_int s = fastExpMod(public_key, y, pub.p);

    M = (M * s) % pub.p; //cipertext
    return std::make_pair(B, M);
}


cpp_int Elgamal::decrypt(lg_key priv, std::pair<cpp_int, cpp_int> msg) const {
    cpp_int private_key = priv.x;
    cpp_int B = msg.first;
    cpp_int M = msg.second;

    cpp_int shared_secret = fastExpMod(B, private_key, priv.p);
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