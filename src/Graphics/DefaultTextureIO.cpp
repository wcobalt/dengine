//
// Created by wcobalt on 11/7/19.
//

#include "DefaultTextureIO.h"
#include "PNG/PngLoader.h"
#include "../Exceptions/ImageException.h"

using namespace dengine;

DefaultTextureIO::DefaultTextureIO() {
    loaders.emplace_back(std::shared_ptr<TextureLoader>(new PngLoader())); //png
}

std::shared_ptr<Texture> DefaultTextureIO::load(const std::string &fileName) const {
    //heavy check (reads signatures from file several times)
    for (const auto& loader : loaders) {
        if (loader->isCompatible(fileName)) {
            return loader->load(fileName);
        }
    }

    throw ImageException("Format of image file is not supported. Texture cannot be loaded");
}
