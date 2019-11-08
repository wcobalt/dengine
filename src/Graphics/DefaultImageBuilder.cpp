//
// Created by wcobalt on 10/27/19.
//

#include "DefaultImageBuilder.h"
#include "Image.h"
#include "../Exceptions/IllegalStateException.h"
#include "DefaultImage.h"
#include "../Exceptions/ImageException.h"

using namespace dengine;

DefaultImageBuilder::DefaultImageBuilder() : imageType(0), width(0), height(0), data(nullptr) {}

void DefaultImageBuilder::setWidth(unsigned long width) {
    this->width = width;
}

void DefaultImageBuilder::setHeight(unsigned long height) {
    this->height = height;
}

void DefaultImageBuilder::setImageType(unsigned imageType) {
    this->imageType = imageType;
}

void DefaultImageBuilder::setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b) {
    if (imageType != Image::TYPE_RGB) throw IllegalStateException("Type of the image is not RGB");

    unsigned sampleDepth = getSampleDepth();
    unsigned long xOffset = x * sampleDepth;

    data[y][xOffset] = r;
    data[y][xOffset + 1] = g;
    data[y][xOffset + 2] = b;
}

void DefaultImageBuilder::setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a) {
    if (imageType != Image::TYPE_RGBA) throw IllegalStateException("Type of the image is not RGBA");

    setRgbPixel(x, y, r, g, b);

    data[y][x * getSampleDepth() + 3] = a;
}

std::shared_ptr<Image> DefaultImageBuilder::build() const {
    return std::shared_ptr<Image>(new DefaultImage(data, imageType, width, height));
}

void DefaultImageBuilder::checkIfAllocable() {
    const std::string CANNOT_ALLOCATE = "Cannot allocate memory: ";

    if (width == 0) throw ImageException(CANNOT_ALLOCATE + "width is not initialized");
    if (height == 0) throw ImageException(CANNOT_ALLOCATE + "height is not initialized");
    if (imageType == 0) throw ImageException(CANNOT_ALLOCATE + "image type is not initialized");
}

unsigned DefaultImageBuilder::getSampleDepth() const {
    switch (imageType) {
        case Image::TYPE_RGB:
            return DefaultImage::TYPE_RGB_SAMPLE_SIZE;

        case Image::TYPE_RGBA:
            return DefaultImage::TYPE_RGBA_SAMPLE_SIZE;

        default:
            return 0;
    }
}

void DefaultImageBuilder::allocate() {
    checkIfAllocable();

    data = new std::byte*[height];

    for (unsigned i = 0; i < height; i++)
        data[i] = new std::byte[width];
}

void DefaultImageBuilder::allocate(std::byte **rawData) {
    checkIfAllocable();

    data = rawData;
}

void DefaultImageBuilder::clear() {
    imageType = 0;
    width = height = 0;
    data = nullptr;
}
