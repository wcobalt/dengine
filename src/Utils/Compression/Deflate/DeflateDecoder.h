//
// Created by wcobalt on 10/15/19.
//
#include <vector>

#ifndef DENGINE_DEFLATEDECODER_H
#define DENGINE_DEFLATEDECODER_H

namespace dengine {
    class InputByteStream;
}

namespace dengine {
    class DeflateDecoder {
    public:
        virtual size_t decode(InputByteStream &deflateStream) = 0;

        virtual char at(size_t index) const = 0;

        virtual size_t getSize() const = 0;

        virtual void clear() = 0;

        virtual std::shared_ptr<InputByteStream> getStream() const = 0;

        virtual std::vector<char> getDecodedData() const = 0;
    };
}

#endif //DENGINE_DEFLATEDECODER_H
