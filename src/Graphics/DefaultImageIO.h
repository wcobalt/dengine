//
// Created by wcobalt on 11/7/19.
//

#ifndef DENGINE_DEFAULTTEXTUREIO_H
#define DENGINE_DEFAULTTEXTUREIO_H

#include <vector>
#include "ImageIO.h"
#include "ImageLoader.h"

namespace dengine {
    class DefaultImageIO : public ImageIO {
    private:
        std::vector<std::unique_ptr<ImageLoader>> loaders;
    public:
        DefaultImageIO();

        std::unique_ptr<Image> load(const std::string &fileName) const;
    };
}

#endif //DENGINE_DEFAULTTEXTUREIO_H
