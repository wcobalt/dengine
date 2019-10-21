//
// Created by wcobalt on 10/20/19.
//
#include <vector>

#ifndef DENGINE_DEFAULTINPUTBYTESTREAM_H
#define DENGINE_DEFAULTINPUTBYTESTREAM_H

#include "InputByteStream.h"

namespace dengine {
    class DefaultInputByteStream : public InputByteStream {
    private:
        size_t pointer;
        const char* stream;
    public:
        DefaultInputByteStream(const char* data);

        DefaultInputByteStream(const std::vector<char> &data);

        char read();

        const char & peek() const override;

        size_t getReadBytesCount() const;
    };
}

#endif //DENGINE_DEFAULTINPUTBYTESTREAM_H
