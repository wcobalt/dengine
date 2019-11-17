//
// Created by wcobalt on 4/6/19.
//
#include <string>

#ifndef DENGINE_DOBJECT_H
#define DENGINE_DOBJECT_H

namespace dengine {
    class DObject {
    public:
        virtual std::string toString() const;
    };
}

#endif //DENGINE_DOBJECT_H
