#include "Functions.h"

bool containsOnlyLetters(std::string str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
        std::string::npos;
}

bool uniqueCharacters(std::string &str)
{ 
    for (uint i = 0; i < str.length()-1; i++) {
        if (str[i] == str[i + 1]) {
            return false;
        }
    }
    return true;
}

bool compare(const std::string &V1, const std::string &V2) {
    return strcmp(V1.data() + 2, V2.data() + 2) < 0;
}