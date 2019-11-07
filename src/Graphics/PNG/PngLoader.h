//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_DEFAULTPNG_H
#define DENGINE_DEFAULTPNG_H

namespace dengine {
    class Texture;
}

#include "../TextureLoader.h"

namespace dengine {
    class PngLoader : public TextureLoader {
    private:
        const unsigned SIGNATURE_SIZE = 8;

        bool hasPngSignature(FILE* stream) const;
    public:
        std::shared_ptr<Texture> load(const std::string &fileName) const;

        bool isCompatible(const std::string &fileName) const;
    };
}

#endif //DENGINE_DEFAULTPNG_H
