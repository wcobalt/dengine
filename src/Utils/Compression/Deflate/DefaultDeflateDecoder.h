//
// Created by wcobalt on 10/15/19.
//

#ifndef DENGINE_DEFAULTDEFLATEDECODER_H
#define DENGINE_DEFAULTDEFLATEDECODER_H

#include "DeflateDecoder.h"

namespace dengine {
    class DefaultDeflateDecoder : public DeflateDecoder {
    private:
        static const unsigned BTYPE_SIZE = 2;
        static const unsigned BTYPE_NO_COMPRESSION = 0b00;
        static const unsigned BTYPE_FIXED_HUFFMAN = 0b01;
        static const unsigned BTYPE_DYNAMIC_HUFFMAN = 0b10;
        static const unsigned BTYPE_ERROR = 0b11;
        static const unsigned LEN_BYTES = 2;
        static const unsigned NLEN_BYTES = 2;
        static const unsigned BITS_IN_CHAR = 8;

        std::vector<char> decodedData;

        bool getBitFromBitStream(const char *stream, size_t index) const;

        void decodeNoCompression(const char *deflateStream, size_t &index);

        void decodeFixed(const char *deflateStream, size_t &index);

        void decodeDynamic(const char *deflateStream, size_t &index);

        unsigned long
        getNumberFromBitStream(const char *stream, size_t &index, unsigned size, bool isReverseOrder) const;

        unsigned long reverse(unsigned long number) const;
    public:
        DefaultDeflateDecoder();

        void decode(const char *deflateStream);

        char at(size_t index) const;

        char operator[](size_t index) const;

        size_t getSize() const;

        void clear();

    };
}

#endif //DENGINE_DEFAULTDEFLATEDECODER_H
