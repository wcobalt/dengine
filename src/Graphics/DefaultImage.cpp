//
// Created by wcobalt on 13.09.19.
//

#include "DefaultImage.h"

using namespace dengine;

DefaultImage::DefaultImage(std::byte **rawData, unsigned imageType, unsigned long width, unsigned long height) {
    data = rawData;
    this->imageType = imageType;
    this->width = width;
    this->height = height;
}

unsigned long DefaultImage::getWidth() const {
    return width;
}

unsigned long DefaultImage::getHeight() const {
    return height;
}

std::byte ** DefaultImage::getRawData() const {
    return data;
}

unsigned int DefaultImage::getSampleSize() const {
    switch (imageType) {
        case Image::TYPE_RGB:
            return TYPE_RGB_SAMPLE_SIZE;
        case Image::TYPE_RGBA:
            return TYPE_RGBA_SAMPLE_SIZE;
        default:
            return 0;
    }
}

unsigned int DefaultImage::getImageType() const {
    return imageType;
}
