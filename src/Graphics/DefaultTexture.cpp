//
// Created by wcobalt on 13.09.19.
//

#include "DefaultTexture.h"

using namespace dengine;

DefaultTexture::DefaultTexture(std::byte **rawData, unsigned imageType, unsigned long width, unsigned long height) {
    data = rawData;
    this->imageType = imageType;
    this->width = width;
    this->height = height;
}

unsigned long DefaultTexture::getWidth() const {
    return width;
}

unsigned long DefaultTexture::getHeight() const {
    return height;
}

std::byte ** DefaultTexture::getRawData() const {
    return data;
}

unsigned int DefaultTexture::getImageType() const {
    return imageType;
}
