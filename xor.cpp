#include "xor.h"

std::string Decrypt(std::string toEncrypt) {
    char key = 'I';
    std::string output = toEncrypt;

    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}

unsigned char Decrypt2(unsigned char toEncrypt) {
    unsigned char key = 'A';
    unsigned char output = toEncrypt;
    output = toEncrypt ^ key;
    return output;
}