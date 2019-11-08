//
// Created by wcobalt on 3/23/19.
//

#include <exception>
#include <string>

#ifndef DENGINE_DENGINEEXCEPTION_H
#define DENGINE_DENGINEEXCEPTION_H

#include "../DObject.h"

namespace dengine {
    class DengineException : public std::exception, DObject {
    private:
        std::string message;
    public:
        inline DengineException(const std::string& message) : message(message) {}

        inline virtual const char* what() const noexcept {
            return message.c_str();
        }
    };
}

#endif //DENGINE_DENGINEEXCEPTION_H
