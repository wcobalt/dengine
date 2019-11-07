//
// Created by wcobalt on 10/27/19.
//

#include "DefaultTextureBuilder.h"
#include "Texture.h"
#include "../Exceptions/InvalidStateException.h"
#include "DefaultTexture.h"
#include "../Exceptions/ImageException.h"

using namespace dengine;

DefaultTextureBuilder::DefaultTextureBuilder() : imageType(0), width(0), height(0), data(nullptr) {}

void DefaultTextureBuilder::setWidth(unsigned long width) {
    this->width = width;
}

void DefaultTextureBuilder::setHeight(unsigned long height) {
    this->height = height;
}

void DefaultTextureBuilder::setImageType(unsigned imageType) {
    this->imageType = imageType;
}

void DefaultTextureBuilder::setRgbPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b) {
    if (imageType != Texture::TYPE_RGB) throw InvalidStateException("Type of the image is not RGB");

    unsigned sampleDepth = getSampleDepth();
    unsigned long xOffset = x * sampleDepth;

    data[y][xOffset] = r;
    data[y][xOffset + 1] = g;
    data[y][xOffset + 2] = b;
}

void DefaultTextureBuilder::setRgbaPixel(size_t x, size_t y, std::byte r, std::byte g, std::byte b, std::byte a) {
    if (imageType != Texture::TYPE_RGBA) throw InvalidStateException("Type of the image is not RGBA");

    setRgbPixel(x, y, r, g, b);

    data[y][x * getSampleDepth() + 3] = a;
}

std::shared_ptr<Texture> DefaultTextureBuilder::build() const {
    return std::shared_ptr<Texture>(new DefaultTexture(data, imageType, width, height));
}

void DefaultTextureBuilder::checkIfAllocable() {
    const std::string CANNOT_ALLOCATE = "Cannot allocate memory: ";

    if (width == 0) throw ImageException(CANNOT_ALLOCATE + "width is not initialized");
    if (height == 0) throw ImageException(CANNOT_ALLOCATE + "height is not initialized");
    if (imageType == 0) throw ImageException(CANNOT_ALLOCATE + "image type is not initialized");
}

unsigned DefaultTextureBuilder::getSampleDepth() const {
    switch (imageType) {
        case Texture::TYPE_RGB:
            return TYPE_RGB_SIZE;

        case Texture::TYPE_RGBA:
            return TYPE_RGBA_SIZE;

        default:
            return 0;
    }
}

void DefaultTextureBuilder::allocate() {
    checkIfAllocable();

    data = new std::byte*[height];

    for (unsigned i = 0; i < height; i++)
        data[i] = new std::byte[width];
}

void DefaultTextureBuilder::allocate(std::byte **rawData) {
    checkIfAllocable();

    data = rawData;
}

void DefaultTextureBuilder::clear() {
    imageType = 0;
    width = height = 0;
    data = nullptr;
}
