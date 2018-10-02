//
// Created by wcobalt on 30.09.18.
//

#include "ID.h"

ID::ID(std::string name) {
    this->name = name;
}

ID::ID(std::string name, std::string category):ID(name) {
    this->category = category;
};

std::string ID::getName() {
    return name;
}

std::string ID::getCategory() {
    return category;
}