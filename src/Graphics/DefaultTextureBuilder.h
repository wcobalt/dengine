//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_DEFAULTIMAGEBUILDER_H
#define DENGINE_DEFAULTIMAGEBUILDER_H

#include <vector>
#include <cstddef>
#include "TextureBuilder.h"

namespace dengine {
    class DefaultTextureBuilder : public TextureBuilder {
    private:
        unsigned imageType;
        unsigned long width, height;
        std::byte** data;

        static const unsigned TYPE_RGB_SIZE = 3;
        static const unsigned TYPE_RGBA_SIZE = 4;

        void checkIfAllocable();

        unsigned getSampleDepth() const;
    public:
        DefaultTextureBuilder();

        virtual void setImageType(unsigned imageType);

        virtual void setWidth(unsigned long width);

        virtual void setHeight(unsigned long height);

        void allocate();

        void allocate(std::byte **rawData);

        virtual void setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b);

        virtual void setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a);

        std::shared_ptr<Texture> build() const;

        void clear();
    };
}

#endif //DENGINE_DEFAULTIMAGEBUILDER_H
