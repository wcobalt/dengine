//
// Created by wcobalt on 30.09.18.
//

#include "ID.h"

ID::ID(std::string name) {
    this->name = name;
}

ID::ID(std::string name, std::string group):ID(name) {
    this->group = group;
};

std::string ID::getName() {
    return name;
}

std::string ID::getGroup() {
    return group;
}