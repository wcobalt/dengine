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
        using spaces_type = std::set<std::unique_ptr<Space>>;
        static std::unique_ptr<spaces_type> spaces;

        iterator findGameObject(GameObject &gameObject);

        static ID takeNextId();

        static ID currentId;

        Space(ID id, const std::string& name);

        ID id;
        std::string name;
    public:
        static void reset();

        static Space& create(const std::string& name);

        static Space& get(const std::string& name);

        static Space& get(ID id);

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin();

        const_iterator cend();

        ID getId() const;

        const std::string& getName() const;

        void add(GameObject& gameObject);

        void remove(GameObject &gameObject);

        bool has(GameObject& gameObject) const;
    };
}

#endif //DENGINE_SPACE_H
