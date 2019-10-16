//
// Created by wcobalt on 10/15/19.
//

#include "DefaultDeflateDecoder.h"
#include "../../../Exceptions/InvalidArgumentException.h"

using namespace dengine;

DefaultDeflateDecoder::DefaultDeflateDecoder():decodedData(nullptr), size(0) {}

void DefaultDeflateDecoder::decode(const char *deflateStream) {

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

//it assumes that char has only 8 bits
bool DefaultDeflateDecoder::getBitFromStream(const char *stream, size_t index) {
    const unsigned BITS_IN_CHAR_COUNT = 8;

    size_t bitNumber = index % BITS_IN_CHAR_COUNT, byteNumber = index / BITS_IN_CHAR_COUNT;

    return stream[byteNumber] << bitNumber;
}

size_t DefaultDeflateDecoder::decodeStored(const char *deflateStream, size_t index, char *destination,
                                                    size_t offset) {
    return 0;
}

size_t DefaultDeflateDecoder::decodeStatic(const char *deflateStream, size_t index, char *destination,
                                                    size_t offset) {
    return 0;
}

size_t DefaultDeflateDecoder::decodeDynamic(const char *deflateStream, size_t index, char *destination,
                                                     size_t offset) {
    return 0;
}
