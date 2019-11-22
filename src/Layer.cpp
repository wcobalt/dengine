//
// Created by wcobalt on 11/21/19.
//

#include "Layer.h"

using namespace dengine;

Layer::Layer(const std::string &layerName) : layerName(layerName) {}

std::string Layer::toString() const {
    return "Layer: " + layerName;
}
