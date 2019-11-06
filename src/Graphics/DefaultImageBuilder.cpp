//
// Created by wcobalt on 10/27/19.
//

#include "DefaultImageBuilder.h"
#include "Image.h"
#include "../Exceptions/InvalidStateException.h"
#include "DefaultImage.h"

using namespace dengine;

DefaultImageBuilder::DefaultImageBuilder() : imageType(TYPE_NONE), width(0), height(0), data(nullptr) {}

void DefaultImageBuilder::setWidth(unsigned long width) {
    this->width = width;
    
    initialize();
}

void DefaultImageBuilder::setHeight(unsigned long height) {
    this->height = height;
    
    initialize();
}

void DefaultImageBuilder::setImageType(unsigned imageType) {
    this->imageType = imageType;
    
    initialize();
}

void DefaultImageBuilder::setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b) {
    if (imageType != Image::TYPE_RGB) throw InvalidStateException("Type of the image is not RGB");

    size_t index = y * getPixelSize() + x;

    setRgbPixel(index, r, g, b);
}

void DefaultImageBuilder::setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b,
                                       std::byte a) {
    if (imageType != Image::TYPE_RGBA) throw InvalidStateException("Type of the image is not RGBA");

    size_t index = y * getPixelSize() + x;
    
    setRgbPixel(index, r, g, b);

    data[index + 3] = a;
}

std::shared_ptr<Image> DefaultImageBuilder::build() const {
    std::shared_ptr<Image> image(new DefaultImage(data, imageType, width, 0));

    return image;
}

void DefaultImageBuilder::initialize() {
    if (width != 0 && height != 0 && imageType != TYPE_NONE && !data) {
        data = new std::byte[width * height * getPixelSize()];
    }
}

unsigned DefaultImageBuilder::getPixelSize() const {
    switch (imageType) {
        case Image::TYPE_RGB:
            return TYPE_RGB_SIZE;

        case Image::TYPE_RGBA:
            return TYPE_RGBA_SIZE;

        default:
            return 0;
    }
}

void DefaultImageBuilder::setRgbPixel(size_t index, std::byte r, std::byte g, std::byte b) {
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}
