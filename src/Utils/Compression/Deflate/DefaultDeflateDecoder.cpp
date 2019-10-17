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

DefaultDeflateDecoder::DefaultDeflateDecoder() {}

void DefaultDeflateDecoder::decode(const char *deflateStream) {
    size_t bitIndex = 0, decompressedDataIndex = 0;
    bool lastBlock;

    do {
        //BFINAL
        lastBlock = getBitFromBitStream(deflateStream, bitIndex++);

        //BTYPE
        unsigned btype = (unsigned)getNumberFromBitStream(deflateStream, bitIndex, BTYPE_SIZE, true);

        switch (btype) {
            case BTYPE_NO_COMPRESSION:
                decodeNoCompression(deflateStream, bitIndex);

                break;
            case BTYPE_FIXED_HUFFMAN:
                decodeFixed(deflateStream, bitIndex);

                break;
            case BTYPE_DYNAMIC_HUFFMAN:
                decodeDynamic(deflateStream, bitIndex);

                break;
            case BTYPE_ERROR:
                throw DeflateException("BTYPE=3. Possible encoder error");
            default:
                throw DeflateException("Undefined BTYPE=" + std::to_string(btype) + ". Something went wrong. Possible bug. Make a report.");
        }
    } while (!lastBlock);
}

char DefaultDeflateDecoder::at(size_t index) const {
    if (index >= decodedData.size()) throw InvalidArgumentException("Index is out of bounds");

    return decodedData[index];
}

char DefaultDeflateDecoder::operator[](size_t index) const {
    return at(index);
}

size_t DefaultDeflateDecoder::getSize() const {
    return decodedData.size();
}

void DefaultDeflateDecoder::clear() {
    decodedData.clear();
}

bool DefaultDeflateDecoder::getBitFromBitStream(const char *stream, size_t index) const {
    size_t bitNumber = index % BITS_IN_CHAR, byteNumber = index / BITS_IN_CHAR;

    return ((stream[byteNumber] >> bitNumber) & 1) == 1;
}

void DefaultDeflateDecoder::decodeNoCompression(const char *deflateStream, size_t &index) {
    //go up to next byte boundary
    while (index % BITS_IN_CHAR != 0) index++;

    unsigned len = (unsigned)getNumberFromBitStream(deflateStream, index, LEN_BYTES * BITS_IN_CHAR, true);
    unsigned nlen = (unsigned)getNumberFromBitStream(deflateStream, index, NLEN_BYTES * BITS_IN_CHAR, true);

    //check whether nlen is 1's complement of len
    unsigned lenOnesComplement = len;

    //if len is negative (sign bit is 1)
    if (((len >> (BITS_IN_CHAR * LEN_BYTES - 1u)) & 1) == 1) {
        //len is negative

        //invert
        lenOnesComplement = ~len;

        //get all not first LEN_BYTES * BITS_IN_CHAR bits as 0
        unsigned mask = 1u << (LEN_BYTES * BITS_IN_CHAR); //mask = 00...0100000...0
        mask -= 1; //mask = 000...01111111...1

        //set remain bits as 0
        lenOnesComplement &= mask;

        //set sign bit as 1
        lenOnesComplement |= (1u << (LEN_BYTES * BITS_IN_CHAR - 1u));
    }

    if (lenOnesComplement != nlen) throw DeflateException("1's complement of LEN is not equals NLEN");

    for (size_t i = 0; i < len; i++) {
        char data = (char)getNumberFromBitStream(deflateStream, index, BITS_IN_CHAR, true);

        decodedData.emplace_back(data);
    }
}

void DefaultDeflateDecoder::decodeFixed(const char *deflateStream, size_t &index) {

}

void DefaultDeflateDecoder::decodeDynamic(const char *deflateStream, size_t &index) {

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

    index += size;

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
