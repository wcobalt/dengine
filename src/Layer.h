//
// Created by wcobalt on 11/21/19.
//
#include <string>

#ifndef DENGINE_LAYER_H
#define DENGINE_LAYER_H

#include "DObject.h"

namespace dengine {
    class Layer : public DObject {
    private:
        std::string layerName;
    public:
        Layer(const std::string& layerName);

        bool operator==(const Layer& layer) const {
            return layerName == layer.layerName;
        }

        const std::string& getName() const {
            return layerName;
        }

        std::string toString() const override;
    };
}

#endif //DENGINE_LAYER_H
