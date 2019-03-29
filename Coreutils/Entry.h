//
// Created by wcobalt on 3/23/19.
//

#include <memory>

#ifndef DENGINE_ENTRY_H
#define DENGINE_ENTRY_H

#include "../Dengine.h"

namespace dengine::coreutils {
    using namespace dengine;
    template <class T>
    class Entry {
    private:
        std::shared_ptr<T> object;//may be get out shared_ptr?
        ID id;
    public:
        Entry(std::shared_ptr<T> object, ID id);

        std::shared_ptr<T> getObject();

        ID getID();
    };
}

#endif //DENGINE_ENTRY_H
