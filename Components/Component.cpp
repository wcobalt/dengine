//
// Created by wcobalt on 19.09.18.
//

#include "Component.h"

Component::Component(ID *id) {
    this->id = id;
}

ID *Component::getID() {
    return id;
}