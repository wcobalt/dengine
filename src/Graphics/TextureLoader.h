//
// Created by wcobalt on 5/24/19.
//
#include <memory>
#include <string>

#ifndef DENGINE_PNG_H
#define DENGINE_PNG_H

namespace dengine {
    class Texture;
}

namespace dengine {
    class TextureLoader {
    public:
        virtual std::shared_ptr<Texture> load(const std::string& fileName) const = 0;

        virtual bool isCompatible(const std::string& fileName) const = 0;
    };
}

#endif //DENGINE_PNG_H
