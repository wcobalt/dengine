//
// Created by wcobalt on 1/30/20.
//

#include <memory>

#ifndef DENGINE_PLATFORMBUILDER_H
#define DENGINE_PLATFORMBUILDER_H

namespace dengine {
    class Platform;
}

namespace dengine {
    class PlatformBuilder {
    public:
        virtual void clear() = 0;

        virtual std::unique_ptr<Platform> build() const = 0;
    };
}

#endif //DENGINE_PLATFORMBUILDER_H
