//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_BYTESTREAM_H
#define DENGINE_BYTESTREAM_H

#include <cstdlib>

namespace dengine {
    class InputBitStream {
    public:
        static const unsigned BITS_IN_CHAR = 8;

        virtual bool read() = 0;

        virtual unsigned long readNumber(size_t size, bool isInverseOrder) = 0;

        virtual void skipUntilByteBoundary() = 0;

        virtual size_t getReadBitsCount() const = 0;
    };
}

#endif //DENGINE_BYTESTREAM_H
