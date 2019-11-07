//
// Created by wcobalt on 13.09.19.
//

#include <memory>
#include <vector>
#include <cstddef>

#ifndef DENGINE_IMAGE_H
#define DENGINE_IMAGE_H

namespace dengine {
    class Texture {
    public:
        static const unsigned TYPE_RGB = 1;
        static const unsigned TYPE_RGBA = 2;

        virtual unsigned long getWidth() const = 0;

        virtual unsigned long getHeight() const = 0;

        virtual unsigned getImageType() const = 0;

        virtual std::byte ** getRawData() const = 0;
    };
}

#endif //DENGINE_IMAGE_H
