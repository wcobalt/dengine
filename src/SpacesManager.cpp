//
// Created by wcobalt on 1/28/20.
//

#include <algorithm>
#include "SpacesManager.h"
#include "Space.h"
#include "Exceptions/SpaceException.h"

using namespace dengine;

ID SpacesManager::takeNextId() {
    return ++currentId;
}

Space &SpacesManager::create(std::string name) {
    if (findSpaceByAlias(name) == spaces.end()) {
        std::unique_ptr<Space> space = std::make_unique<Space>(takeNextId(), std::move(name));
        Space &spaceReference = *space;

        spaces.emplace(std::move(space));

        return spaceReference;
    } else
        throw SpaceException("Unable to create new space: there's a space with name '" + name + "' already");
}

Space &SpacesManager::get(std::string_view name) const {
    auto it = findSpaceByAlias(name);

    if (it != spaces.end())
        return **findSpaceByAlias(name);
    else
        throw SpaceException("Unable to find space: there's no space with name '" + std::string(name) + "'");
}

Space &SpacesManager::get(ID id) const {
    auto it = findSpaceById(id);

    if (it != spaces.end())
        return **findSpaceById(id);
    else
        throw SpaceException("Unable to find space: there's no space with id " + std::to_string(id));
}

void SpacesManager::remove(std::string_view name) {
    auto it = findSpaceByAlias(name);

    if (it != spaces.end())
        removeSpace(it);
    else
        throw SpaceException("Unable to remove space: there's no space with name '" + std::string(name) + "'");
}

void SpacesManager::remove(ID id) {
    auto it = findSpaceById(id);

    if (it != spaces.end())
        removeSpace(it);
    else
        throw SpaceException("Unable to remove space: there's no space with id " + std::to_string(id));
}

void SpacesManager::remove(Space &space) {
    remove(space.getId());
}

void SpacesManager::reset() {
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

SpacesManager::iterator SpacesManager::findSpaceById(ID id) const {
    return std::find_if(spaces.begin(), spaces.end(), [id](const std::unique_ptr<Space>& space) {
        return space->getId() == id;
    });
}

SpacesManager::iterator SpacesManager::findSpaceByAlias(std::string_view name) const {
    return std::find_if(spaces.begin(), spaces.end(), [&name](const std::unique_ptr<Space>& space) {
        return space->getName() == name;
    });
}

void SpacesManager::removeSpace(SpacesManager::iterator iterator) {
    (*iterator)->removeAll();

    spaces.erase(iterator);
}
