//
// Created by wcobalt on 1/28/20.
//
#include <memory>
#include <set>

#ifndef DENGINE_SPACESMANAGER_H
#define DENGINE_SPACESMANAGER_H

namespace dengine {
    class Space;
}

#include "DObject.h"
#include "Coreutils/ID.h"

namespace dengine {
    class SpacesManager : public DObject {
    private:
        std::set<std::unique_ptr<Space>> spaces;

        ID takeNextId();

        const ID INIT_ID = IDUtils::NO_ID;
        ID currentId = INIT_ID;

        using iterator = decltype(spaces)::iterator;
        using const_iterator = decltype(spaces)::const_iterator;
    public:
        Space& create(const std::string& name);

        Space& get(const std::string& name) const;

        Space& get(ID id) const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin();

        const_iterator cend();

        void reset();
    };
}

#endif //DENGINE_SPACESMANAGER_H
