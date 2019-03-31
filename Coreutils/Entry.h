//
// Created by wcobalt on 3/23/19.
//

#include <memory>

#ifndef DENGINE_ENTRY_H
#define DENGINE_ENTRY_H

#include "../Dengine.h"

namespace dengine::coreutils {
    using namespace dengine;

    template <class K, class V>
    class Entry {
    private:
        std::shared_ptr<V> object;//may be get out shared_ptr?
        K id;
    public:
        Entry(K id, std::shared_ptr<V> object);

        std::shared_ptr<V> getObject() const;

        K getID() const;
    };
}

#endif //DENGINE_ENTRY_H
