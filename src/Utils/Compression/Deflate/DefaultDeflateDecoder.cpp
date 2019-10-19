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

DefaultDeflateDecoder::DefaultDeflateDecoder() {
    //calculate the offsets
    unsigned lengthCount = LENGTH_END - LENGTH_START + 1 - ERRONEOUS_LENGTHS_COUNT;
    unsigned distancesCount = DISTANCES_COUNT - ERRONEOUS_DISTANCES_COUNT;

    lengthOffsets = new unsigned long[lengthCount];
    distancesOffsets = new unsigned long[distancesCount];

    unsigned long currentLength = MINIMAL_LENGTH - 1;

    for (unsigned i = 0; i < lengthCount; i++) {
        //what range the extra bits add = (extra_bits == 0 ? 0 : pow(2, extra_bits))
        unsigned extraBits = LENGTH_EXTRA_BITS[i];
        unsigned long range = (extraBits == 0 ? 0 : (1u << extraBits) - 1);

        lengthOffsets[i] = ++currentLength;

        currentLength += range;

        if (i == lengthCount - 1) lengthOffsets[i]--; //exception, see 258 in rfc1951
    }

    unsigned long currentDistance = MINIMAL_DISTANCE - 1;

    for (unsigned i = 0; i < distancesCount; i++) {
        //what range the extra bits add = (extra_bits == 0 ? 0 : pow(2, extra_bits))
        unsigned extraBits = DISTANCES_EXTRA_BITS[i];
        unsigned long range = (extraBits == 0 ? 0 : (1u << extraBits) - 1);

        distancesOffsets[i] = ++currentDistance;

        currentDistance += range;

    }
}

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
    unsigned decodedValue = ~0u;

    do {
        //get next value
        for (unsigned i = 0, countOfBitsToGet = 0, currentCode = 0; i < FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT; i++) {
            //get delta between last bits count and current, with purpose to know how many bits we have to read
            countOfBitsToGet = FIXED_HUFFMAN_CODES_RANGES_SIZES[i] - countOfBitsToGet;

            //shift because new bits must be right aligned in code
            currentCode <<= countOfBitsToGet;
            currentCode |= (unsigned)getNumberFromBitStream(deflateStream, index, countOfBitsToGet, false);

            //get value of this code
            bool found = false;

            for (auto range : FIXED_HUFFMAN_CODES_RANGES) {
                ///if our code is between two boundaries of codes and length of the code equals to that range's length
                if (range[3] == FIXED_HUFFMAN_CODES_RANGES_SIZES[i] && currentCode >= range[0] && currentCode <= range[1]) {
                    decodedValue = currentCode - range[0] + range[2];

                    found = true;

                    break;
                }
            }

            if (found) {
                unsigned length = processValue(deflateStream, index, decodedValue);

                if (length != NO_LENGTH) {
                    //decoded value is length, so we need to find the distance and then expose both them to literals
                    unsigned distanceNumber = getNumberFromBitStream(deflateStream, index, FIXED_HUFFMAN_DISTANCE_SIZE, false);

                    exposeToLiterals(deflateStream, index, length, distanceNumber);
                }

                break;
            } else if (i == FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT - 1)
                throw DeflateException("Unrecognized Fixed Huffman Code: " + std::to_string(currentCode));
        }
    } while (decodedValue != END_OF_BLOCK);
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

unsigned int DefaultDeflateDecoder::processValue(const char *deflateStream, size_t &index, unsigned value) {
    if (value >= LITERALS_START && value <= LITERALS_END) {
        decodedData.emplace_back(value); //literal
    } else if (value >= LENGTH_START && value <= LENGTH_END) {
        //pair <length, distance>
        //get the extra bits which describe length

        //number in table of lengths extra bits
        unsigned lengthNumber = value - LENGTH_START;

        //extra bits + length offset
        return getNumberFromBitStream(deflateStream, index, LENGTH_EXTRA_BITS[lengthNumber], true) + lengthOffsets[lengthNumber];
    } else if (value != END_OF_BLOCK) {
        bool found = false;

        for (unsigned erroneousLength : ERRONEOUS_LENGTHS)
            if (value == erroneousLength) found = true;

        //if value is one of err lengths
        if (found) throw DeflateException("Erroneous length " + std::to_string(value) + " was found");

        found = false;

        for (unsigned erroneousDistance : ERRONEOUS_DISTANCES)
            if (value == erroneousDistance) found = true;

        //if value is one of err distances
        if (found) throw DeflateException("Erroneous distance " + std::to_string(value) + " was found");

        //otherwise
        throw DeflateException("Unrecognized value " + std::to_string(value) + " was found");
    }

    return NO_LENGTH;
}

void DefaultDeflateDecoder::exposeToLiterals(const char *deflateStream, size_t &index, unsigned length,
                                             unsigned distanceNumber) {
    //first of all we need to get a real distance from extra bits
    //then we need to add to them distance offset
    unsigned long distance = getNumberFromBitStream(deflateStream, index, DISTANCES_EXTRA_BITS[distanceNumber], true)
            + distancesOffsets[distanceNumber];

    size_t currentSize = decodedData.size();

    for (unsigned l = 0; l < length; l++)
        decodedData.emplace_back(decodedData[currentSize++ - distance]);
}
