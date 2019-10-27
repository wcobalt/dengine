//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_DEFAULTPNG_H
#define DENGINE_DEFAULTPNG_H

#include "Png.h"

namespace dengine {
    class DefaultPng : public Png {
    public:
        std::shared_ptr<Image> load(const std::string &fileName) const override;
    };
}

#endif //DENGINE_DEFAULTPNG_H
