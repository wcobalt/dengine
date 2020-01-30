//
// Created by wcobalt on 11/7/19.
//
#include <memory>

#ifndef DENGINE_IMAGELOADER_H
#define DENGINE_IMAGELOADER_H

namespace dengine {
    class Image;
}

namespace dengine {
    class ImageIO {
    public:
        virtual std::unique_ptr<Image> load(const std::string &fileName) const = 0;
    };
}

#endif //DENGINE_IMAGELOADER_H
