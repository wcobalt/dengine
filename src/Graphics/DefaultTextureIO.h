//
// Created by wcobalt on 11/7/19.
//

#ifndef DENGINE_DEFAULTTEXTUREIO_H
#define DENGINE_DEFAULTTEXTUREIO_H

#include <vector>
#include "TextureIO.h"
#include "TextureLoader.h"

namespace dengine {
    class DefaultTextureIO : public TextureIO {
    private:
        std::vector<std::shared_ptr<TextureLoader>> loaders;
    public:
        DefaultTextureIO();

        std::shared_ptr<Texture> load(const std::string &fileName) const;
    };
}

#endif //DENGINE_DEFAULTTEXTUREIO_H
