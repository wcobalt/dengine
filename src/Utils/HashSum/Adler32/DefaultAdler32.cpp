//
// Created by wcobalt on 10/20/19.
//

#include "DefaultAdler32.h"
#include "../../../Exceptions/InvalidArgumentException.h"

using namespace dengine;

uint32_t DefaultAdler32::calculateAdler32(const char *data, size_t size) const {
    if (size == 0) throw InvalidArgumentException("Size of data must be greater than zero");

    uint16_t a = 1, b = 0;

    for (size_t i = 0; i < size; i++) {
        a += data[i];
        b += a;
    }

    uint32_t result = 0;

    result |= b;
    result <<= 16u;
    result |= a;

    return result;
}

uint32_t DefaultAdler32::calculateAdler32(std::vector<char> data) const {
    return calculateAdler32(&data[0], data.size());
}

uint32_t DefaultAdler32::calculateAdler32(const InputByteStream &inputStream, size_t size) const {
    return calculateAdler32(&inputStream.peek(), size);
}
