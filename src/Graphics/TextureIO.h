//
// Created by wcobalt on 11/7/19.
//
#include <memory>

#ifndef DENGINE_IMAGELOADER_H
#define DENGINE_IMAGELOADER_H

namespace dengine {
    class Texture;
}

namespace dengine {
    class TextureIO {
    public:
        virtual std::shared_ptr<Texture> load(const std::string &fileName) const = 0;
    };
}

#endif //DENGINE_IMAGELOADER_H
