//
// Created by wcobalt on 5/24/19.
//
#include <memory>
#include <string>

#ifndef DENGINE_PNG_H
#define DENGINE_PNG_H

#include "../Image.h"

namespace dengine {
    class Png {
    public:
        virtual std::shared_ptr<Image> load(const std::string& fileName) const = 0;
    };
}

#endif //DENGINE_PNG_H
