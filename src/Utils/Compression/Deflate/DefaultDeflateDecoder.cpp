//
// Created by wcobalt on 10/15/19.
//

#include <iostream>
#include "DefaultDeflateDecoder.h"
#include "../../../Exceptions/InvalidArgumentException.h"
#include "Exceptions/DeflateException.h"

using namespace dengine;

const unsigned DefaultDeflateDecoder::BTYPE_SIZE;
const unsigned DefaultDeflateDecoder::BTYPE_NO_COMPRESSION;
const unsigned DefaultDeflateDecoder::BTYPE_FIXED_HUFFMAN;
const unsigned DefaultDeflateDecoder::BTYPE_DYNAMIC_HUFFMAN;
const unsigned DefaultDeflateDecoder::BTYPE_ERROR;
const unsigned DefaultDeflateDecoder::BITS_IN_CHAR;

DefaultDeflateDecoder::DefaultDeflateDecoder():decodedData(nullptr), size(0) {}

void DefaultDeflateDecoder::decode(const char *deflateStream) {
    size_t bitIndex = 0;
    bool lastBlock;

    do {
        //BFINAL
        lastBlock = getBitFromBitStream(deflateStream, bitIndex++);

        //BTYPE
        unsigned btype = 0;

        for (unsigned i = 0; i < BTYPE_SIZE; i++) {
            btype <<= 1u;
            btype &= getBitFromBitStream(deflateStream, bitIndex++);
        }

        switch (btype) {
            case BTYPE_NO_COMPRESSION:

                break;
            case BTYPE_FIXED_HUFFMAN:

                break;
            case BTYPE_DYNAMIC_HUFFMAN:

                break;
            case BTYPE_ERROR:

                break;
            default:
                throw DeflateException("Undefined BTYPE=" + std::to_string(btype) + ". Something went wrong. Possible bug. Make a report.");
        }
    } while (!lastBlock);
}

char DefaultDeflateDecoder::at(size_t index) const {
    if (index >= size) throw InvalidArgumentException("Index is out of bounds");

    return decodedData[index];
}

char DefaultDeflateDecoder::operator[](size_t index) const {
    return at(index);
}

size_t DefaultDeflateDecoder::getSize() const {
    return size;
}

void DefaultDeflateDecoder::clear() {
    delete[] decodedData;

    decodedData = nullptr;
    size = 0;
}

DefaultDeflateDecoder::~DefaultDeflateDecoder() {
    delete[] decodedData;
}

bool DefaultDeflateDecoder::getBitFromBitStream(const char *stream, size_t index) const {
    size_t bitNumber = index % BITS_IN_CHAR, byteNumber = index / BITS_IN_CHAR;

    return ((stream[byteNumber] >> bitNumber) & 1) == 1;
}

size_t DefaultDeflateDecoder::decodeNoCompression(const char *deflateStream, size_t index, char *destination,
                                                  size_t offset) {
    return 0;
}

size_t DefaultDeflateDecoder::decodeFixed(const char *deflateStream, size_t index, char *destination,
                                          size_t offset) {
    return 0;
}

size_t DefaultDeflateDecoder::decodeDynamic(const char *deflateStream, size_t index, char *destination,
                                                     size_t offset) {
    return 0;
}

unsigned long DefaultDeflateDecoder::getNumberFromBitStream(const char *stream, size_t &index, unsigned size, bool isReverseOrder) const {
    unsigned long result = 0;

    for (size_t i = 0; i < size; i++) {
        bool bit = getBitFromBitStream(stream, index + i);

        if (isReverseOrder)
            result |= ((unsigned long)bit << i);
        else {
            result <<= 1u;
            result |= bit;
        }
    }

    return result;
}

unsigned long DefaultDeflateDecoder::reverse(unsigned long number) const {
    unsigned long result = 0;
    unsigned firstOneIndex = ~0u;
    unsigned size = sizeof(number) * BITS_IN_CHAR;
    unsigned currentIndex = size;

    while (currentIndex > 0) {
        unsigned long originalBit = (number >> (currentIndex - 1)) & 1;

        if (originalBit && firstOneIndex == ~0u) firstOneIndex = currentIndex;
        if (firstOneIndex != ~0u) result |= (originalBit << (firstOneIndex - currentIndex));

        currentIndex--;
    }

    return result;
}
