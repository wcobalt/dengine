//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_DEFAULTIMAGEBUILDER_H
#define DENGINE_DEFAULTIMAGEBUILDER_H

#include <vector>
#include <cstddef>
#include "ImageBuilder.h"

namespace dengine {
    class DefaultImageBuilder : public ImageBuilder {
    private:
        unsigned imageType;
        unsigned long width, height;
        std::byte* data;

        static const unsigned TYPE_NONE = ~0u;
        static const unsigned TYPE_RGB_SIZE = 3;
        static const unsigned TYPE_RGBA_SIZE = 4;

        void initialize();

        unsigned getPixelSize() const;
        
        void setRgbPixel(size_t index, std::byte r, std::byte g, std::byte b);
    public:
        DefaultImageBuilder();

        virtual void setImageType(unsigned imageType);

        virtual void setWidth(unsigned long width);

        virtual void setHeight(unsigned long height);

        virtual void setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b);

        virtual void setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a);

        std::shared_ptr<Image> build() const;
    };
}

#endif //DENGINE_DEFAULTIMAGEBUILDER_H
