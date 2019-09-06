//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_LESSTHANVECTOREXCEPTION_H
#define DENGINE_LESSTHANVECTOREXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class LessThanVectorException : public DengineException {
    private:
        unsigned short n;
    public:
        LessThanVectorException(unsigned short n);

        const char* what() const noexcept;
    };
}

#endif //DENGINE_LESSTHANVECTOREXCEPTION_H
