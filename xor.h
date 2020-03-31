#pragma once
#include <string>

std::string Decrypt(std::string toEncrypt) {
    char key = 'I';
    std::string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}