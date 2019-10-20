//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_DEFAULTINPUTBITSTREAM_H
#define DENGINE_DEFAULTINPUTBITSTREAM_H

#include "InputBitStream.h"

namespace dengine {
    class DefaultInputBitStream : public InputBitStream {
    private:
        const char* stream;
        size_t pointer;
    public:
        DefaultInputBitStream(const char* stream);

        bool read();

        unsigned long readNumber(size_t size, bool isInverseOrder);

        void skipUntilByteBoundary();
    };
}

#endif //DENGINE_DEFAULTINPUTBITSTREAM_H
