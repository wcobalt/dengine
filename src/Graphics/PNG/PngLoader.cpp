//
// Created by wcobalt on 10/27/19.
//

#include <fstream>
#include <iostream>
#include "PngLoader.h"
#include "../Image.h"
#include "../../Exceptions/IOException.h"
#include "Exceptions/PngException.h"
#include "../ImageBuilder.h"
#include "../DefaultImageBuilder.h"
#include "png.h"
#include "../DefaultImage.h"

using namespace dengine;

void png_error_handler(png_structp png_struct, png_const_charp message) {
    throw PngException("Cannot read PNG file: " + std::string(message));
}

std::shared_ptr<Image> PngLoader::load(const std::string &fileName) const {
    FILE* fileDescriptor = fopen(fileName.c_str(), "rb");
    if (!fileDescriptor)
        throw IOException("Unable to open " + fileName + " file");

    bool pngTest = hasPngSignature(fileDescriptor);
    if (!pngTest)
        throw PngException(fileName + " file is not a png image");

    png_structp pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, png_error_handler, nullptr);
    if (!pngStruct)
        throw PngException("Cannot allocate png struct");

    png_infop infoStruct = png_create_info_struct(pngStruct);
    if (!infoStruct) {
        png_destroy_read_struct(&pngStruct, nullptr, nullptr);

        throw PngException("Cannot allocate info struct");
    }

    png_init_io(pngStruct, fileDescriptor);
    png_set_sig_bytes(pngStruct, SIGNATURE_SIZE);
    png_read_png(pngStruct, infoStruct, PNG_TRANSFORM_GRAY_TO_RGB | PNG_TRANSFORM_PACKING, nullptr);

    png_bytep *data = png_get_rows(pngStruct, infoStruct);
    std::shared_ptr<ImageBuilder> builder(new DefaultImageBuilder());

    builder->setWidth(png_get_image_width(pngStruct, infoStruct));
    builder->setHeight(png_get_image_height(pngStruct, infoStruct));

    unsigned imageType = 0;
    unsigned pngImageType = png_get_color_type(pngStruct, infoStruct);

    switch (pngImageType) {
        case PNG_COLOR_TYPE_RGB:
            imageType = Image::TYPE_RGB;

            break;
        case PNG_COLOR_TYPE_RGBA:
            imageType = Image::TYPE_RGBA;

            break;
        default:
            throw PngException("Unsupported by Dengine color type is used in " + fileName);
    }

    builder->setImageType(imageType);
    builder->allocate(reinterpret_cast<std::byte**>(data));

    return builder->build();
}

bool PngLoader::isCompatible(const std::string &fileName) const {
    FILE* stream = fopen(fileName.c_str(), "rb");

    return hasPngSignature(stream);
}

bool PngLoader::hasPngSignature(FILE *stream) const {
    png_byte signature[SIGNATURE_SIZE];

    fread(signature, 1, SIGNATURE_SIZE, stream);

    return !png_sig_cmp(signature, 0, SIGNATURE_SIZE);
}
