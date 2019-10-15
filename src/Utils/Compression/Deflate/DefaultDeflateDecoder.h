//
// Created by wcobalt on 10/15/19.
//

#ifndef DENGINE_DEFAULTDEFLATEDECODER_H
#define DENGINE_DEFAULTDEFLATEDECODER_H

#include "DeflateDecoder.h"

namespace dengine {
    class DefaultDeflateDecoder : public DeflateDecoder {
    private:
        char* decodedData;
        size_t size;

        bool getBitFromStream(const char* stream, size_t index);

        size_t decodeStored(const char* deflateStream, size_t index, char* destination, size_t offset);

        size_t decodeStatic(const char* deflateStream, size_t index, char* destination, size_t offset);

        size_t decodeDynamic(const char* deflateStream, size_t index, char* destination, size_t offset);
    public:
        DefaultDeflateDecoder();

        void decode(const char *deflateStream);

        char at(size_t index) const;

        char operator[](size_t index) const;

        size_t getSize() const;

        void clear();

        virtual ~DefaultDeflateDecoder();
    };
}

#endif //DENGINE_DEFAULTDEFLATEDECODER_H
