//
// Created by wcobalt on 10/20/19.
//
#include <cstdlib>
#include <chrono>
#ifndef DENGINE_INPUTBYTESTREAM_H
#define DENGINE_INPUTBYTESTREAM_H

namespace dengine {
    class InputByteStream {
    public:
        virtual char read() = 0;

        virtual const char & peek() const = 0;

        virtual size_t getReadBytesCount() const = 0;
    };
}

#endif //DENGINE_INPUTBYTESTREAM_H
