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
        std::byte** data;

        void checkIfAllocable();

        unsigned getSampleDepth() const;
    public:
        DefaultImageBuilder();

        virtual void setImageType(unsigned imageType);

        virtual void setWidth(unsigned long width);

        virtual void setHeight(unsigned long height);

        void allocate();

        void allocate(std::byte **rawData);

        virtual void setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b);

        virtual void setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a);

        std::unique_ptr<Image> build() const;

        void clear();
    };
}

#endif //DENGINE_DEFAULTIMAGEBUILDER_H
