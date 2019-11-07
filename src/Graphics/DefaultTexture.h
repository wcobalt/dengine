//
// Created by wcobalt on 13.09.19.
//

#ifndef DENGINE_DEFAULTIMAGE_H
#define DENGINE_DEFAULTIMAGE_H

#include <cstddef>
#include "Texture.h"

namespace dengine {
    class DefaultTexture : public virtual Texture {
    private:
        std::byte** data;
        unsigned long width, height;
        unsigned imageType;
    public:
        DefaultTexture(std::byte **rawData, unsigned imageType, unsigned long width, unsigned long height);

        unsigned long getWidth() const;

        unsigned long getHeight() const;

        unsigned int getImageType() const;

        std::byte ** getRawData() const;
    };
}

#endif //DENGINE_DEFAULTIMAGE_H
