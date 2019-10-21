//
// Created by wcobalt on 10/20/19.
//
#include <cstdint>
#include <vector>
#include <memory>
#include "../../Streams/InputByteStream.h"

#ifndef DENGINE_ADLER32_H
#define DENGINE_ADLER32_H

namespace dengine {
    class Adler32 {
    public:
        static const unsigned long MODULO_BY = 65521;

        virtual uint32_t calculateAdler32(const char *data, size_t size) const = 0;

        virtual uint32_t calculateAdler32(std::vector<char> data) const = 0;

        virtual uint32_t calculateAdler32(const InputByteStream &inputStream, size_t size) const = 0;
    };
}

#endif //DENGINE_ADLER32_H
