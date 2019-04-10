//
// Created by wcobalt on 3/23/19.
//

#include <exception>

#ifndef DENGINE_DENGINEEXCEPTION_H
#define DENGINE_DENGINEEXCEPTION_H

#include "../DObject.h"

//@todo is exceptions need to extend DObject?
namespace dengine::exceptions {
    class DengineException : public std::exception, DObject {
        virtual const char* what() const noexcept = 0;
    };
}

#endif //DENGINE_DENGINEEXCEPTION_H
