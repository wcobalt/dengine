//
// Created by wcobalt on 10/25/19.
//

#ifndef DENGINE_DEFAULTZLIBDECODER_H
#define DENGINE_DEFAULTZLIBDECODER_H

#include <map>
#include "ZlibDecoder.h"

namespace dengine {
    class DefaultZlibDecoder : public ZlibDecoder {
    private:
        std::vector<char> decodedData;
        std::map<unsigned, unsigned long> metaData;
    public:
        static const unsigned CM_SIZE = 4;
        static const unsigned CINFO_SIZE = 4;
        static const unsigned FCHECK_SIZE = 5;
        static const unsigned FLEVEL_SIZE = 2;
        static const unsigned CHECK_SIZE = 2;
        static const unsigned DICTID_SIZE = 4;
        static const unsigned ADLER_SIZE = 4;
        static const unsigned BITS_IN_CHAR = 8;

        void decode(InputByteStream &inputStream);

        char operator[](size_t index);

        char at(size_t index) const;

        size_t getSize() const;

        void clear();

        unsigned long getProperty(unsigned property) const;
    };
}

#endif //DENGINE_DEFAULTZLIBDECODER_H
