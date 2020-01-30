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
        //@todo default constructors to exceptions
        explicit DengineException(std::string message) : message(std::move(message)) {}

        virtual const char* what() const noexcept {
            return message.c_str();
        }
    private:
        std::string toString() const override {
            return message;
        }
    };
}

#endif //DENGINE_DENGINEEXCEPTION_H
