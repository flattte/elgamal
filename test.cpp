#include "crypto/algorithm.h"
#include "crypto/elgamal.h"
#include "crypto/elgamal.cpp"
#include <iostream>
#include <string>


typedef boost::multiprecision::cpp_int cpp_int;

int main(int argc, char **argv){

    std::pair<lg_key, lg_key> keys = Elgamal::keyGen();

    std::cout << "pub ";
    std::cout << "generator: :: ";  Elgamal::printHex(keys.first.g, 32);
    std::cout << "private key :: "; Elgamal::printHex(keys.first.x, 32);
    std::cout << "p prime :: ";     Elgamal::printHex(keys.first.p, 32);
    std::cout << "public :: ";        Elgamal::printHex(keys.second.x, 32);
    std::cout << std::endl;

    std::string m = argv[1];
    cpp_int msg(m);


    std::cout << "true plaintext :: ";
    Elgamal::printHex(msg, 16);
    std::cout << "\n\n";

    Elgamal engine;
    std::pair<cpp_int, cpp_int> cipher = engine.encrypt(msg, keys.first);

    std::cout << "ciphertext :: ";
    Elgamal::printHex(cipher.second, 16);
    std::cout << "\n\n";

    cpp_int plaintext = engine.decrypt(keys.second, cipher);
    std::cout << "plaintext ::";
    Elgamal::printHex(plaintext, 16);
    std::cout << "\n\n";

}
