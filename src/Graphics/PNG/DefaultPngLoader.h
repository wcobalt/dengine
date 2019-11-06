//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_DEFAULTPNG_H
#define DENGINE_DEFAULTPNG_H

namespace dengine {
    class Image;
}

#include "PngLoader.h"

namespace dengine {
    class DefaultPngLoader : public PngLoader {
    public:
        std::shared_ptr<Image> load(const std::string &fileName) const;
    };
}

#endif //DENGINE_DEFAULTPNG_H
