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

    cpp_int b= 0;
    while(true){ 
        b = getRN(2, p -1);
        if(_gcd(b, p) == 1)
            break;
    }

    cpp_int B = fastExpMod(g, b, p);
    lg_key pub(g, B, p);
    lg_key priv(g, b, p);

    return std::make_pair(pub, priv);
}


std::pair<cpp_int, cpp_int> Elgamal::encrypt(cpp_int m, const lg_key pub) const {
    cpp_int public_key = pub.x;

    cpp_int a = 0; // local random number to raise msg to
    do{
        a = getRN(static_cast<cpp_int>(2), pub.p - 1);
    }  while(_gcd(a, pub.p) != 1);

    cpp_int A = fastExpMod(pub.g, a, pub.p);
    cpp_int s = fastExpMod(public_key, a, pub.p);

    m = (m * s) % pub.p; //cipertext
    return std::make_pair(A, m);
}


cpp_int Elgamal::decrypt(lg_key priv, std::pair<cpp_int, cpp_int> msg) const {
    cpp_int private_key = priv.x;
    cpp_int A = msg.first;
    cpp_int m = msg.second;

    cpp_int shared_secret = fastExpMod(A, private_key, priv.p);
    cpp_int s_multiplicative_inverse = multiplicativeInverse(shared_secret, priv.p);
    
    m = (m * s_multiplicative_inverse) % priv.p;
    return m;
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
