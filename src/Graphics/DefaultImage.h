//
// Created by wcobalt on 13.09.19.
//

#ifndef DENGINE_DEFAULTIMAGE_H
#define DENGINE_DEFAULTIMAGE_H

#include <cstddef>
#include "Image.h"

namespace dengine {
    class Pixel;
}

namespace dengine {
    class DefaultImage : public virtual Image {
    public:
        DefaultImage(const std::byte *rawData, unsigned imageType, unsigned long width, unsigned long offset);

        std::shared_ptr<const Pixel> getPixel(unsigned long x, unsigned long y) const override;

        unsigned int getWidth() const override;

        unsigned int getHeight() const override;

        std::shared_ptr<const std::vector<const Pixel>> getRaw() const override;
    };
}

#endif //DENGINE_DEFAULTIMAGE_H
