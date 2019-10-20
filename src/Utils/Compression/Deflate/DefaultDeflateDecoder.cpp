//
// Created by wcobalt on 10/15/19.
//

#include <iostream>
#include <memory>
#include "DefaultDeflateDecoder.h"
#include "../../../Exceptions/InvalidArgumentException.h"
#include "Exceptions/DeflateException.h"
#include "../Huffman/DefaultHuffmanDecoder.h"
#include "../../Streams/InputBitStream.h"

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

void DefaultDeflateDecoder::decode(std::shared_ptr<InputBitStream> deflateStream) {
    size_t decompressedDataIndex = 0;
    bool lastBlock;

    do {
        //BFINAL
        lastBlock = deflateStream->read();

        //BTYPE
        unsigned btype = (unsigned)deflateStream->readNumber(BTYPE_SIZE, true);

        switch (btype) {
            case BTYPE_NO_COMPRESSION:
                decodeNoCompression(deflateStream);

                break;
            case BTYPE_FIXED_HUFFMAN:
                decodeFixed(deflateStream);

                break;
            case BTYPE_DYNAMIC_HUFFMAN:
                decodeDynamic(deflateStream);

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

void DefaultDeflateDecoder::decodeNoCompression(std::shared_ptr<InputBitStream> deflateStream) {
    //go up to next byte boundary
    deflateStream->skipUntilByteBoundary();

    unsigned len = (unsigned)deflateStream->readNumber(LEN_BYTES * BITS_IN_CHAR, true);
    unsigned nlen = (unsigned)deflateStream->readNumber(NLEN_BYTES * BITS_IN_CHAR, true);

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
        char data = (char)deflateStream->readNumber(BITS_IN_CHAR, true);

        decodedData.emplace_back(data);
    }
}

void DefaultDeflateDecoder::decodeFixed(std::shared_ptr<InputBitStream> deflateStream) {
    unsigned decodedValue = ~0u;

    do {
        //get next value
        for (unsigned i = 0, countOfBitsToGet = 0, currentCode = 0; i < FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT; i++) {
            //get delta between last bits count and current, with purpose to know how many bits we have to read
            countOfBitsToGet = FIXED_HUFFMAN_CODES_RANGES_SIZES[i] - countOfBitsToGet;

            //shift because new bits must be right aligned in code
            currentCode <<= countOfBitsToGet;
            currentCode |= (unsigned)deflateStream->readNumber(countOfBitsToGet, false);

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
                unsigned length = processValue(deflateStream, decodedValue);

                if (length != NO_LENGTH) {
                    //decoded value is length, so we need to find the distance and then expose both them to literals
                    unsigned distanceNumber = deflateStream->readNumber(FIXED_HUFFMAN_DISTANCE_SIZE, false);

                    exposeToLiterals(deflateStream, length, distanceNumber);
                }

                break;
            } else if (i == FIXED_HUFFMAN_CODES_RANGES_SIZES_COUNT - 1)
                throw DeflateException("Unrecognized Fixed Huffman Code: " + std::to_string(currentCode));
        }
    } while (decodedValue != END_OF_BLOCK);
}

void DefaultDeflateDecoder::decodeDynamic(std::shared_ptr<InputBitStream> deflateStream) {
    unsigned literalsCount = deflateStream->readNumber(DYNAMIC_HUFFMAN_HLIT_SIZE, true) + DYNAMIC_HUFFMAN_HLIT_START;
    unsigned distancesCount = deflateStream->readNumber(DYNAMIC_HUFFMAN_HDIST_SIZE, true) + DYNAMIC_HUFFMAN_HDIST_START;
    unsigned codeLengthsForCodeLengthsCount = deflateStream->readNumber(DYNAMIC_HUFFMAN_HCLEN_SIZE, true)
                                              + DYNAMIC_HUFFMAN_HCLEN_START;

    //we need to get code lengths for code lengths
    std::vector<char> codeLengthsForCodeLengths(DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_SIZE, 0);

    for (unsigned i = 0; i < codeLengthsForCodeLengthsCount; i++) {
        char length = deflateStream->readNumber(DYNAMIC_HUFFMAN_CODE_LENGTH_FOR_CODE_LENGTH_SIZE, true);

        codeLengthsForCodeLengths[DYNAMIC_HUFFMAN_CODE_LENGTHS_FOR_CODE_LENGTH_ORDER[i]] = length;
    }

    std::shared_ptr<HuffmanDecoder> codeLengths(new DefaultHuffmanDecoder());
    codeLengths->loadCodesByCodesLengths(codeLengthsForCodeLengths);

    //now we're getting literalsCount of literals code lengths
    std::vector<char> codeLengthsForLiterals(LENGTH_END - LITERALS_START + 1, 0);
    std::vector<char> codeLengthsForDistances(DISTANCES_COUNT, 0);

    unsigned lastLength = 0;
    unsigned sumOfLiteralsCountAnDistancesCount = literalsCount + distancesCount;

    //we process literals/lengths and distances in one loop (to avoid code duplication)
    size_t addedLiterals = 0, addedDistances = 0;

    while (addedLiterals + addedDistances < sumOfLiteralsCountAnDistancesCount) {
        while (!codeLengths->isResult()) {
            //get another bit
            bool bit = deflateStream->read();

            //navigate by it in the tree
            codeLengths->navigate(bit);
        }

        unsigned value = codeLengths->getResult();

        //process gotten value as it declared by code length value
        bool isLength;

        if (addedLiterals < literalsCount) {
            //if now we're processing literals/lengths

            isLength = processValueOfCodeLengthAlphabet(deflateStream, codeLengthsForLiterals, value,
                                                        lastLength, addedLiterals);
        } else {
            //if distances

            //if on the previous iteration we were processing literals/lengths, then reset state
            if (addedLiterals == literalsCount) lastLength = 0;

            isLength = processValueOfCodeLengthAlphabet(deflateStream, codeLengthsForDistances, value,
                                                        lastLength, addedDistances);
        }

        codeLengths->reset();

        //if gotten value is a real length, not copy code, then write lastLength
        if (isLength) lastLength = value;
    }

    //now, we have lengths for literals/lengths and distances, so let's grow some trees
    std::shared_ptr<HuffmanDecoder> literals(new DefaultHuffmanDecoder());
    std::shared_ptr<HuffmanDecoder> distances(new DefaultHuffmanDecoder());

    literals->loadCodesByCodesLengths(codeLengthsForLiterals);
    distances->loadCodesByCodesLengths(codeLengthsForDistances);

    //we have the trees, the next and actually final step is directly decoding
    unsigned decodedValue;

    do {
        //get bits til we haven't any result
        while (!literals->isResult()) {
            bool bit = deflateStream->read();

            literals->navigate(bit);
        }

        //now we have some result
        decodedValue = literals->getResult();

        //process value, and get real length if value is length marker
        unsigned length = processValue(deflateStream, decodedValue);

        if (length != NO_LENGTH) {
            //we need to get distance number
            //let's take a bit per iteration and navigate in the distances tree
            while (!distances->isResult()) {
                bool bit = deflateStream->read();

                distances->navigate(bit);
            }

            //now we have distance code
            exposeToLiterals(deflateStream, length, distances->getResult());
            distances->reset();
        }

        literals->reset();
    } while (decodedValue != END_OF_BLOCK);
}

unsigned int DefaultDeflateDecoder::processValue(std::shared_ptr<InputBitStream> deflateStream, unsigned value) {
    if (value >= LITERALS_START && value <= LITERALS_END) {
        decodedData.emplace_back(value); //literal
    } else if (value >= LENGTH_START && value <= LENGTH_END) {
        //pair <length, distance>
        //get the extra bits which describe length

        //number in table of lengths extra bits
        unsigned lengthNumber = value - LENGTH_START;

        //extra bits + length offset
        return deflateStream->readNumber(LENGTH_EXTRA_BITS[lengthNumber], true) + lengthOffsets[lengthNumber];
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

void DefaultDeflateDecoder::exposeToLiterals(std::shared_ptr<InputBitStream> deflateStream, unsigned length, unsigned distanceNumber) {
    //first of all we need to get a real distance from extra bits
    //then we need to add to them distance offset
    unsigned long distance = deflateStream->readNumber(DISTANCES_EXTRA_BITS[distanceNumber], true)
                             + distancesOffsets[distanceNumber];

    size_t currentSize = decodedData.size();

    for (unsigned l = 0; l < length; l++)
        decodedData.emplace_back(decodedData[currentSize++ - distance]);
}

bool DefaultDeflateDecoder::processValueOfCodeLengthAlphabet(std::shared_ptr<InputBitStream> deflateStream, std::vector<char> &codeLengths,
                                                             char value, char lastLength, size_t &addedCount) {
    if (value >= DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_LITERALS_START && value <= DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_LITERALS_END) {
        codeLengths[addedCount++] = value;

        //it's a length, so true
        return true;
    } else {
        //it's a copy code
        unsigned extraBitsToRead = 0, valueForRepeating = 0, offsetForSumWithExtraBits = 0;

        if (value == DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS) {
            //copy previous
            extraBitsToRead = DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS_EXTRA_BITS;
            valueForRepeating = lastLength;
            offsetForSumWithExtraBits = DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_PREVIOUS_OFFSET;
        } else {
            //copy zero
            for (auto copyZeroSet : DYNAMIC_HUFFMAN_CODE_LENGTHS_ALPHABET_COPY_ZERO) {
                if (copyZeroSet[0] == value) {
                    extraBitsToRead = copyZeroSet[1];
                    offsetForSumWithExtraBits = copyZeroSet[2];
                    valueForRepeating = 0;

                    break;
                }
            }
        }


        unsigned copiesCount = deflateStream->readNumber(extraBitsToRead, true) + offsetForSumWithExtraBits;

        for (unsigned i = 0; i < copiesCount; i++) codeLengths[addedCount++] = valueForRepeating;

        return false;
    }
}

DefaultDeflateDecoder::~DefaultDeflateDecoder() {
    delete[] lengthOffsets;
    delete[] distancesOffsets;
}
