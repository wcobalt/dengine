//
// Created by wcobalt on 13.09.19.
//

#include <memory>
#include <vector>

#ifndef DENGINE_IMAGE_H
#define DENGINE_IMAGE_H

namespace dengine {
    class Pixel;
}

namespace dengine {
    class Image {
    public:
        virtual std::shared_ptr<const Pixel> getPixel(unsigned x, unsigned y) const = 0;

        virtual unsigned getWidth() const = 0;

        virtual unsigned getHeight() const = 0;

        virtual std::shared_ptr<const std::vector<const Pixel>> getRaw() const = 0;
    };
}

#endif //DENGINE_IMAGE_H
