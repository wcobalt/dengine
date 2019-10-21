//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_DEFAULTADLER32_H
#define DENGINE_DEFAULTADLER32_H

#include "Adler32.h"

namespace dengine {
    class DefaultAdler32 : public Adler32 {
    public:
        uint32_t calculateAdler32(const char *data, size_t size) const;

        uint32_t calculateAdler32(std::vector<char> data) const;

        uint32_t calculateAdler32(const InputByteStream &inputStream, size_t size) const;
    };
}

#endif //DENGINE_DEFAULTADLER32_H
