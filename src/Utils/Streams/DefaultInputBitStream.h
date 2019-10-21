//
// Created by wcobalt on 10/20/19.
//
#include <vector>
#include <memory>

#ifndef DENGINE_DEFAULTINPUTBITSTREAM_H
#define DENGINE_DEFAULTINPUTBITSTREAM_H

namespace dengine {
    class InputByteStream;
}

#include "InputBitStream.h"

namespace dengine {
    class DefaultInputBitStream : public InputBitStream {
    private:
        const char* stream;
        size_t pointer;
    public:
        DefaultInputBitStream(const InputByteStream &inputByteStream);

        DefaultInputBitStream(const char* stream);

        DefaultInputBitStream(const std::vector<char> &stream);

        bool read();

        size_t getReadBitsCount() const override;

        unsigned long readNumber(size_t size, bool isInverseOrder);

        void skipUntilByteBoundary();
    };
}

#endif //DENGINE_DEFAULTINPUTBITSTREAM_H
