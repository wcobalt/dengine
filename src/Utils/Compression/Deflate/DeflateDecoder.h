//
// Created by wcobalt on 10/15/19.
//
#include <vector>

#ifndef DENGINE_DEFLATEDECODER_H
#define DENGINE_DEFLATEDECODER_H

namespace dengine {
    class DeflateDecoder {
    public:
        virtual void decode(std::shared_ptr<InputBitStream> deflateStream) = 0;

        virtual char at(size_t index) const = 0;

        virtual size_t getSize() const = 0;

        virtual void clear() = 0;
    };
}

#endif //DENGINE_DEFLATEDECODER_H
