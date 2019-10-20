//
// Created by wcobalt on 10/20/19.
//

#include "DefaultInputBitStream.h"

using namespace dengine;

DefaultInputBitStream::DefaultInputBitStream(const char *stream):stream(stream), pointer(0) {}

bool DefaultInputBitStream::read() {
    size_t bitNumber = pointer % BITS_IN_CHAR, byteNumber = pointer / BITS_IN_CHAR;
    pointer++;

    return ((stream[byteNumber] >> bitNumber) & 1) == 1;
}

unsigned long DefaultInputBitStream::readNumber(size_t size, bool isInverseOrder) {
    unsigned long result = 0;

    for (size_t i = 0; i < size; i++) {
        bool bit = read();

        if (isInverseOrder)
            result |= ((unsigned long)bit << i);
        else {
            result <<= 1u;
            result |= bit;
        }
    }

    return result;
}

void DefaultInputBitStream::skipUntilByteBoundary() {
    while (pointer % BITS_IN_CHAR != 0) pointer++;
}
