//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_ZLIB_H
#define DENGINE_ZLIB_H

#include <cstdlib>

namespace dengine {
    class ZlibDecoder {
    public:
        static const unsigned CM = 0;
        static const unsigned CINFO = 1;
        static const unsigned FDICT = 2;
        static const unsigned FLEVEL = 3;
        static const unsigned DICT = 4;
        static const unsigned ADLER32 = 5;

        virtual void decode(const char* encodedData) = 0;

        virtual char at(size_t index) const = 0;

        virtual size_t getSize() const = 0;

        virtual void clear() = 0;

        virtual unsigned long getProperty(unsigned property) const = 0;
    };
}

#endif //DENGINE_ZLIB_H
