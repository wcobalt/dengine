//
// Created by wcobalt on 10/20/19.
//

#include "DefaultInputByteStream.h"

using namespace dengine;

DefaultInputByteStream::DefaultInputByteStream(const char *data):stream(data), pointer(0) {}

DefaultInputByteStream::DefaultInputByteStream(const std::vector<char> &data): DefaultInputByteStream(&data[0]) {}

char DefaultInputByteStream::read() {
    return stream[pointer++];
}

size_t DefaultInputByteStream::getReadBytesCount() const {
    return pointer;
}

const char & DefaultInputByteStream::peek() const {
    return stream[pointer];
}
