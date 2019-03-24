//
// Created by wcobalt on 3/23/19.
//

#include <memory>

#ifndef DENGINE_ENTRY_H
#define DENGINE_ENTRY_H

namespace dengine::coreutils {
    template<class T>
    class Entry {
    private:
        std::shared_ptr<T> object;
        ulong id;
    public:
        Entry(std::shared_ptr<T> object, ulong id);

        std::shared_ptr<T> getObject();

        ulong getId();
    };
}

#endif //DENGINE_ENTRY_H
