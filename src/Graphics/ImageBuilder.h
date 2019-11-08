//
// Created by wcobalt on 10/27/19.
//
#include <memory>
#include <cstddef>

#ifndef DENGINE_IMAGEBUILDER_H
#define DENGINE_IMAGEBUILDER_H

namespace dengine {
    class Image;
}

namespace dengine {
    class ImageBuilder {
    public:
        virtual void setImageType(unsigned imageType) = 0;

        virtual void setWidth(unsigned long width) = 0;

        virtual void setHeight(unsigned long height) = 0;

        virtual void allocate() = 0;

        virtual void allocate(std::byte **rawData) = 0;

        virtual void setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b) = 0;

        virtual void setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a) = 0;

        virtual std::shared_ptr<Image> build() const = 0;

        virtual void clear() = 0;
    };
}

#endif //DENGINE_IMAGEBUILDER_H
