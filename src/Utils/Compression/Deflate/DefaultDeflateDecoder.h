//
// Created by wcobalt on 10/15/19.
//
#include <memory>

#ifndef DENGINE_DEFAULTDEFLATEDECODER_H
#define DENGINE_DEFAULTDEFLATEDECODER_H

namespace dengine {
    class InputBitStream;
}

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
        static const unsigned constexpr FIXED_HUFFMAN_CODES_RANGES[4][4] = {{0b0000000, 0b0010111, 256, 7},
                                                                      {0b00110000, 0b10111111, 0, 8},
                                                                      {0b11000000, 0b11000111, 280, 8},
                                                                      {0b110010000, 0b111111111, 144, 9}};
        static const unsigned FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT = 3;
        static const unsigned constexpr FIXED_HUFFMAN_CODES_RANGES_SIZES[FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT] = {7, 8, 9};
        static const unsigned constexpr LENGTH_EXTRA_BITS[] =
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
        static const unsigned constexpr DISTANCES_EXTRA_BITS[] =
                {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
        static const unsigned LITERALS_START = 0;
        static const unsigned LITERALS_END = 255;
        static const unsigned END_OF_BLOCK = 256;
        static const unsigned LENGTH_START = 257;
        static const unsigned LENGTH_END = 287;
        static const unsigned DISTANCES_COUNT = 32;
        static const unsigned constexpr ERRONEOUS_LENGTHS[] = {286, 287};
        static const unsigned ERRONEOUS_LENGTHS_COUNT = 2;
        static const unsigned constexpr ERRONEOUS_DISTANCES[] = {30, 31};
        static const unsigned ERRONEOUS_DISTANCES_COUNT = 2;
        static const unsigned MINIMAL_LENGTH = 3;
        static const unsigned MINIMAL_DISTANCE = 1;
        static const unsigned FIXED_HUFFMAN_DISTANCE_SIZE = 5;
        static const unsigned NO_LENGTH = 0;

        static const unsigned DYNAMIC_HUFFMAN_HLIT_SIZE = 5;
        static const unsigned DYNAMIC_HUFFMAN_HLIT_START = 257;
        static const unsigned DYNAMIC_HUFFMAN_HDIST_SIZE = 5;
        static const unsigned DYNAMIC_HUFFMAN_HDIST_START = 1;
        static const unsigned DYNAMIC_HUFFMAN_HCLEN_SIZE = 4;
        static const unsigned DYNAMIC_HUFFMAN_HCLEN_START = 4;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTH_FOR_CODE_LENGTH_SIZE = 3;
        static const unsigned constexpr DYNAMIC_HUFFMAN_CODE_LENGTHS_FOR_CODE_LENGTH_ORDER[] =
                {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_SIZE = 19;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_LITERALS_START = 0;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_LITERALS_END = 15;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS = 16;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS_EXTRA_BITS = 2;
        static const unsigned DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS_OFFSET = 3;
        //0 - code, 1 - extra bits, 2 - offset
        static const unsigned constexpr DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_ZERO[][3] = {{17, 3, 3}, {18, 7, 11}};

        unsigned long* lengthOffsets;
        unsigned long* distancesOffsets;

        std::vector<char> decodedData;

        void decodeNoCompression(InputBitStream &deflateStream);

        void decodeFixed(InputBitStream &deflateStream);

        void decodeDynamic(InputBitStream &deflateStream);

        unsigned int processValue(InputBitStream &deflateStream, unsigned value);

        void exposeToLiterals(InputBitStream &deflateStream, unsigned length, unsigned distanceNumber);

        bool processValueOfCodeLengthAlphabet(InputBitStream &deflateStream, std::vector<char> &codeLengths,
                                              char value, char lastLength, size_t &addedCount);
    public:
        DefaultDeflateDecoder();

        size_t decode(InputByteStream &deflateStream);

        char at(size_t index) const;

        char operator[](size_t index) const;

        size_t getSize() const;

        void clear();

        std::shared_ptr<InputByteStream> getStream() const;

        std::vector<char> getDecodedData() const;

        virtual ~DefaultDeflateDecoder();
    };
}

#endif //DENGINE_DEFAULTDEFLATEDECODER_H
