//
// Created by wcobalt on 1/27/20.
//
#include <set>
#include <memory>

#ifndef DENGINE_SPACE_H
#define DENGINE_SPACE_H

#include "DObject.h"
#include "Coreutils/ID.h"

namespace dengine {
    class GameObject;
}

namespace dengine {
    class Space : public DObject {
    private:
        std::set<GameObject*> gameObjects;
    public:
        using iterator = decltype(gameObjects)::iterator;
        using const_iterator = decltype(gameObjects)::const_iterator;
    private:
        iterator findGameObject(GameObject &gameObject);

        iterator remove(iterator gameObjectToRemove);

        ID id;
        std::string name;
    public:
        Space(ID id, std::string name);

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin();

        const_iterator cend();

        ID getId() const;

        //@todo think about return string_view
        const std::string& getName() const;

        void add(GameObject& gameObject);

        void remove(GameObject &gameObject);

        void removeAll();

        bool has(GameObject& gameObject) const;

        bool operator==(const Space& space) const;
    };
}

#endif //DENGINE_SPACE_H
