//
// Created by wcobalt on 1/28/20.
//

#include <algorithm>
#include "SpacesManager.h"
#include "Space.h"

using namespace dengine;

ID SpacesManager::takeNextId() {
    return ++currentId;
}

Space &SpacesManager::create(const std::string &name) {
    std::unique_ptr<Space> space = std::make_unique<Space>(takeNextId(), name);
    Space& spaceReference = *space;

    spaces.emplace(std::move(space));

    return spaceReference;
}

Space &SpacesManager::get(const std::string &name) const {
    return **std::find_if(spaces.begin(), spaces.end(), [&name](const std::unique_ptr<Space>& space) {
        return space->getName() == name;
    });
}

Space &SpacesManager::get(ID id) const {
    return **std::find_if(spaces.begin(), spaces.end(), [id](const std::unique_ptr<Space>& space) {
        return space->getId() == id;
    });
}

void SpacesManager::clear() {
    spaces.clear();

    currentId = INIT_ID;
}

SpacesManager::iterator SpacesManager::begin() {
    return spaces.begin();
}

SpacesManager::iterator SpacesManager::end() {
    return spaces.end();
}

SpacesManager::const_iterator SpacesManager::begin() const {
    return spaces.cbegin();
}

SpacesManager::const_iterator SpacesManager::end() const {
    return spaces.cend();
}

SpacesManager::const_iterator SpacesManager::cbegin() {
    return spaces.cbegin();
}

SpacesManager::const_iterator SpacesManager::cend() {
    return spaces.cend();
}
