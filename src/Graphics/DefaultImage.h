//
// Created by wcobalt on 13.09.19.
//

#ifndef DENGINE_DEFAULTIMAGE_H
#define DENGINE_DEFAULTIMAGE_H

#include <cstddef>
#include "Image.h"

namespace dengine {
    class DefaultImage : public virtual Image {
    private:
        std::byte** data;
        unsigned long width, height;
        unsigned imageType;
    public:
        static const unsigned TYPE_RGB_SAMPLE_SIZE = 3;
        static const unsigned TYPE_RGBA_SAMPLE_SIZE = 4;

        DefaultImage(std::byte **rawData, unsigned imageType, unsigned long width, unsigned long height);

        unsigned long getWidth() const;

        unsigned long getHeight() const;

        unsigned int getImageType() const;

        unsigned int getSampleSize() const;

        std::byte ** getRawData() const;
    };
}

#endif //DENGINE_DEFAULTIMAGE_H
