//
// Created by wcobalt on 13.09.19.
//

#include "DefaultImage.h"

using namespace dengine;

DefaultImage::DefaultImage(const std::byte *rawData, unsigned imageType, unsigned long width, unsigned long offset) {

}

std::shared_ptr<const Pixel> DefaultImage::getPixel(unsigned long x, unsigned long y) const {
    return std::shared_ptr<const Pixel>();
}

unsigned int DefaultImage::getWidth() const {
    return 0;
}

unsigned int DefaultImage::getHeight() const {
    return 0;
}

std::shared_ptr<const std::vector<const Pixel>> DefaultImage::getRaw() const {
    return std::shared_ptr<const std::vector<const Pixel>>();
}
