//
// Created by wcobalt on 23.05.19.
//

#include <cstring>

#include "LessThanVectorException.h"

using namespace dengine;

LessThanVectorException::LessThanVectorException(unsigned short n):n(n) {}

const char* LessThanVectorException::what() const noexcept {
    char number[2];

    number[0] = '0' + (char)n;
    number[1] = '\0';

    char* result = new char[128];

    strcat(result, "Unable to convert std::vector<T> to Vector");
    strcat(result, number);
    strcat(result, "<T>, when length of std::vector<T> is less than ");
    strcat(result, number);

    return result;
}