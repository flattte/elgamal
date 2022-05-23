#include "crypto/algorithm.h"
#include "crypto/elgamal.h"
#include "crypto/elgamal.cpp"
#include <iostream>
#include <string>


typedef boost::multiprecision::cpp_int cpp_int;

int main(){
    
    std::pair<lg_key, lg_key> keys = Elgamal::keyGen();

    // std::cout << "pub ";
    // Elgamal::printHex(keys.first.g);
    // Elgamal::printHex(keys.first.x);
    // Elgamal::printHex(keys.first.p);

    // std::cout << "priv ";
    // Elgamal::printHex(keys.second.g);
    // Elgamal::printHex(keys.second.x);
    // Elgamal::printHex(keys.second.p);


    cpp_int msg =278362135621361736218;
    std::cout << "true plaintext :: "; 
    Elgamal::printHex(msg, 16);
    std::cout << "\n\n";

    Elgamal engine;
    std::pair<cpp_int, cpp_int> cipher = engine.encrypt(msg, keys.first);

    std::cout << "ciphertext :: ";
    Elgamal::printHex(cipher.second, 16);
    std::cout << "\n\n";
    std::cout << cipher.first;

    cpp_int plaintext = engine.decrypt(keys.second, cipher);
    std::cout << "plaintext ::";
    Elgamal::printHex(plaintext, 16);
    std::cout << "\n\n";

}